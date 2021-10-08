
#include <fstream>
#include <cstring>

#include <json/json.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <plog/Log.h>

#include "map.h"
#include "DEFINITIONS.h"

namespace Kjeledyr {

    bool Map::Load(std::string filename, std::list<Object *> &objects, std::list<Object *> &collisionLayer,
                   std::map<std::pair<int, int>, Tile *> &collisionTiles,
                   std::vector<std::pair<int, int>> &powerUpSpawns,
                   std::vector<std::pair<std::pair<int, int>, int>> &triggerPoints,
                   std::vector<std::pair<int, int>> &spawnPoints) {
        // Will contain the data we read in
        Json::Value root;
        Json::Value tilesets;

        // Parses the file
        Json::Reader reader;

        // Stream used for reading the data file. The data file has been saved as JSON in Tiled
        std::ifstream file(filename);

        // Read data from file into root object
        bool parsingSuccessful = reader.parse(file, root);

        // Check for success
        if (!parsingSuccessful){
            return false;
            LOGF << "Failed to parse the map data!";
        }

        LOGI << "Parsing map data successful.";

        // Get tile size information
        TileSize tileSize;
        tileSize.x = root["tilesets"][0u]["tilewidth"].asInt();
        tileSize.y = root["tilesets"][0u]["tileheight"].asInt();
        tileSize.s = root["tilesets"][0u]["spacing"].asInt();

        // Read in each layer
        for (Json::Value &layer: root["layers"]) {
            if (layer["name"].asString() == "objects") {
                LoadObjects(root, layer, objects, tileSize);
            }
            else if( layer["name"].asString() == "triggerpoints"){
                LoadTriggerPoints(layer, tileSize, triggerPoints);
            }
            else if(layer["name"].asString() == "spawnpoints"){
                LoadSpawnPoints(layer, tileSize, spawnPoints);
            }
            else {
                LoadLayer(layer, objects, collisionLayer, collisionTiles, tileSize, powerUpSpawns);
            }
        }

        // Read in tileset (Should be handled by a resource handler)
        sf::Texture *tileset = new sf::Texture();
        tileset->loadFromFile("Map/data/" + root["tilesets"][0u]["image"].asString());

        // Assign tileset to every object
        for (Object *object: objects)
            object->texture = tileset;

        LOGI << "Loading map successful";
        return true;
    }



    void Map::LoadLayer(Json::Value &layer, std::list<Object *> &objects, std::list<Object *> &collisionLayer,
                        std::map<std::pair<int, int>, Tile *> &collisionTiles, TileSize tileSize,
                        std::vector<std::pair<int, int>> &powerUpSpawns) {
        Layer *tmp = new Layer(tileSize);

        // Store info on layer
        tmp->width = layer["width"].asInt();
        tmp->height = layer["height"].asInt();

        // Clear tilemap
        memset(tmp->tilemap, 0, sizeof(tmp->tilemap));

        // Read in tilemap
        for (size_t i = 0; i < layer["data"].size(); i++) {
            tmp->tilemap[i % tmp->width][i / tmp->width] = layer["data"][(int) i].asInt();
        }

        Json::Value root;
        Json::Value &tileInfo = root["tilesets"][0u]["tiles"];

        // Save all collision tiles in map
        if (layer["name"] == "collision") {
            for (size_t i = 0; i < layer["data"].size(); i++) { // Iterate through collision layer
                if (tmp->tilemap[i % tmp->width][i / tmp->width] != 0) { // If tile is not 0
                    Tile *tile = new Tile();

                    tile->data = layer["data"][(int) i].asInt() - 1;
                    tile->row = (int) i / tmp->width;
                    tile->col = (int) i % tmp->width;
                    tile->left = tile->col * TILE_SIZE;
                    tile->right = tile->left + TILE_SIZE;
                    tile->top = tile->row * TILE_SIZE;
                    tile->bottom = tile->top + TILE_SIZE;
                    tile->tileBounds.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    tile->tileBounds.setPosition(tile->left, tile->top);

                    collisionTiles.emplace(std::pair<int, int>(tile->col, tile->row), tile);
                }
            }
            collisionLayer.push_back(tmp);
        }
        if (layer["name"] == "powerup") {
            for (size_t i = 0; i < layer["data"].size(); i++) { // Iterate through collision layer
                if (tmp->tilemap[i % tmp->width][i / tmp->width] != 0) { // If tile is not 0
                    Tile *tile = new Tile();
                    tile->row = (int) i / tmp->width;
                    tile->col = (int) i % tmp->width;
                    powerUpSpawns.emplace_back(tile->row, tile->col);
                }
            }
        }
        if (layer["name"] != "powerup") objects.push_back(tmp);
    }

    void Map::LoadObjects(Json::Value &root, Json::Value &layer, std::list<Object *> &objects, TileSize tileSize) {
        // Get all objects from layer
        for (Json::Value &object: layer["objects"]) {
            Sprite *sprite = new Sprite(tileSize);

            // Load basic object info
            sprite->x = object["x"].asInt();
            sprite->y = object["y"].asInt() - sprite->tileSize.y;
            sprite->id = object["gid"].asInt();

            // Load animation data
            Json::Value &tileInfo = root["tilesets"][0u]["tiles"][std::to_string(sprite->id - 1)];
            sprite->frame = 0;
            sprite->frameCount = tileInfo["animation"].size();
            sprite->frameDuration = tileInfo["animation"][0u]["duration"].asInt();

            objects.push_back(sprite);
        }
        LOGI << "Objects loaded.";

    }

    void Map::LoadTriggerPoints(Json::Value &layer, TileSize tileSize,
                                std::vector<std::pair<std::pair<int, int>, int>> &triggerPoints) {
        for (Json::Value &object: layer["objects"]) {
            int x = object["x"].asInt();
            int y = object["y"].asInt() - tileSize.y;
            int gid = object["gid"].asInt();
            triggerPoints.emplace_back(std::make_pair(x, y), gid);
        }
        LOGI << "Triggerpoints loaded.";
    }

    void Map::LoadSpawnPoints(Json::Value &layer, TileSize tileSize, std::vector<std::pair<int, int>> &spawnPoints) {
        for (Json::Value &object: layer["objects"]) {
            int x = object["x"].asInt();
            int y = object["y"].asInt() - tileSize.y;
            spawnPoints.emplace_back(x, y);
        }
        LOGI << "Spawnpoints loaded.";
    }
}