#include <SFML/Graphics.hpp>
#include <plog/Log.h>

#include "object.h"


namespace Kjeledyr {
    Object::~Object() {
        delete texture;
        texture = nullptr;
    }

    void Object::GetTileCoords(int tile, int &x, int &y) {
        // Tileid 0 means no tile, so the ids actually start from 1
        tile--;

        int tileXcount = texture->getSize().x / (tileSize.x + tileSize.s);

        x = (tile % tileXcount) * (tileSize.x + tileSize.s);
        y = (tile / tileXcount) * (tileSize.x + tileSize.s);
    }


}