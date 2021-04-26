#include "tile.h"

enum TileType {
    TILE_GRASS,
    TILE_FIRE,
    TILE_BOMB,
    TILE_WOOD,
}

Tile::Tile(int x, int y, TileType tileType ){
    position = {x,y};
    box.x = x;
    box.y = y;
    box.w = WIDTH;
    box.h = HEIGHT;
    type = tileType;
}

void Tile::Render(SDL_Rect& camera){
    // if the tile is on screen
    if(checkCollision(camera,box)){
        // show the tile
        // gTileTexture.render( box.x - camera.x, box.y - camera.y, &gTileClips[ type ] );
    }
}

TileType Tile::GetType(){
    return type;  
}

int Tile::GetX(){
    return x;
}

int Tile::GetY(){
    return y;
}

SDL_Point Tile::GetPosition(){
    return position;
}

SDL_Rect Tile::GetBox(){
    return box;
}