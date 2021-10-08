#ifndef KJELEDYR_OBJECT_H
#define KJELEDYR_OBJECT_H

#include <list>

    namespace sf {
        class RenderWindow;

        class Texture;
    }

    namespace Kjeledyr {

// Small helper struct that contains tile size information
    struct TileSize {
        int x; // Width
        int y; // Height
        int s; // Spacing
    };

// Class representing any game object
    class Object {
        // map needs to access protected/private data
        friend class Map;

    public:
        Object(TileSize tileSize) : tileSize(tileSize) {}

        virtual ~Object();

        virtual void process(float deltaTime) {}

        virtual void draw(sf::RenderWindow &window) {}

        // Calculate x and y position of given tile in the texture
        void GetTileCoords(int tile, int &x, int &y);

        const TileSize tileSize;

    protected:
        sf::Texture *texture;
    };
}

#endif
