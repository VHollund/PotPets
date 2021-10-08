
#ifndef KJELEDYR_LAYER_H
#define KJELEDYR_LAYER_H

#include "object.h"

namespace Kjeledyr {

// Class representing a tile layer
    class Layer : public Object {
        // map needs to access protected/private data
        friend class Map;

    public:
        Layer(TileSize tileSize) : Object(tileSize) {}
        void draw(sf::RenderWindow &window);

    protected:
        // Size in tiles
        int width, height;
        int tilemap[100][100];
    };
}

#endif
