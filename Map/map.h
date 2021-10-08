#ifndef KJELEDYR_MAP_H
#define KJELEDYR_MAP_H

#include <string>
#include <list>

#include "object.h"
#include "sprite.h"
#include "layer.h"
#include <Game Engine/game.h>


namespace Json {
    class Value;
}


namespace Kjeledyr {

    struct Tile {
        int data;
        int row;
        int col;
        int left;
        int right;
        int top;
        int bottom;
        sf::RectangleShape tileBounds;
    };

// Class with a single public static function that loads a map into an object list
    class Map {
    public:
        // Load map from Tiled JSON file
        static bool Load(std::string filename, std::list<Object *> &objects, std::list<Object *> &collisionLayer,
                         std::map<std::pair<int, int>, Tile *> &collisionTiles,
                         std::vector<std::pair<int, int>> &powerUpSpawns,
                         std::vector<std::pair<std::pair<int, int>, int>> &triggerPoints,
                         std::vector<std::pair<int, int>> &spawnPoints);

    private:
        // Handles regular layers
        static void LoadLayer(Json::Value &layer, std::list<Object *> &objects, std::list<Object *> &collisionLayer,
                              std::map<std::pair<int, int>, Tile *> &collisionTiles, TileSize tileSize,
                              std::vector<std::pair<int, int>> &powerUpSpawns);

        // Handles object layers
        static void LoadObjects(Json::Value &root, Json::Value &layer, std::list<Object *> &objects, TileSize tileSize);

        // Handles trigger points
        static void LoadTriggerPoints(Json::Value &layer, TileSize tileSize,
                                      std::vector<std::pair<std::pair<int, int>, int>> &triggerPoints);

        static void LoadSpawnPoints(Json::Value &layer, TileSize tileSize,
                                    std::vector<std::pair<int, int>> &spawnPoints);
    };
}

#endif

