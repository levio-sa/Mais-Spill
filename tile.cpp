#include "tile.h"

Tile::Tile()
{
    position = {0,0};
    box.x=0;
    box.y=0;
    box.w=WIDTH;
    box.h=HEIGHT;
    type=(TileType)0;
}

Tile::Tile(int x, int y, TileType tileType ){
    position = {x,y};
    box.x = x;
    box.y = y;
    box.w = WIDTH;
    box.h = HEIGHT;
    type = tileType;
}

// void Tile::Render(SDL_Rect& camera){
//     // if the tile is on screen
//     if(checkCollision(camera,box)){
//         // show the tile
//         // gTileTexture.render( box.x - camera.x, box.y - camera.y, &gTileClips[ type ] );
//     }
// }

TileType Tile::GetType(){
    return type;  
}

int Tile::GetX(){
    return position.x;
}

int Tile::GetY(){
    return position.y;
}

SDL_Point Tile::GetPosition(){
    return position;
}

SDL_Rect Tile::GetBox(){
    return box;
}

void Tile::SetPos(int xcor, int ycor){
    position.x = xcor;
    position.y = ycor;
    box.x = xcor;
    box.y = ycor;
}

void Tile::SetType(int t){
    type = (TileType)t;
}