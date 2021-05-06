#pragma once

#include <SDL2/SDL.h>>

class ServerPlayer;
class Wall;
class Road;

enum TileType {
    TILE_GRASS,
    TILE_FIRE,
    TILE_BOMB,
    TILE_WOOD,
};

class Tile {
    public:

        const static int WIDTH = 25;
        const static int HEIGHT = 25;

        Tile();

        // initializes position and type
        Tile( int x, int y, TileType tileType );

        // // shows the tile
        // void Render( SDL_Rect& camera );

        // get the tile type
        TileType GetType();

        // get x position
        int GetX();

        // get y position
        int GetY();

        // get position
        SDL_Point GetPosition();

        // get the collision box
        SDL_Rect GetBox();

        // Sets pointer to ServerPlayer in the tile
        void SetServerPlayer(ServerPlayer* ServerPlayer);

        // Sets pointer to wall in the tile
        void SetWall(Wall* wall);

        // Sets pointer to wall in the tile
        void SetRoad(Road* road);

        // Sets position of the tile
        void SetPos(int x, int y);

        // Sets type of the tile
        void SetType(int t); // should I go with type or wall and road?-> if static property then no need to create an object

        // Returns pointer to ServerPlayer in the tile
        ServerPlayer* GetServerPlayer();
        
        // Returns pointer to wall in the tile
        Wall* GetWall();

        // Returns pointer to wall in the tile
        Road* GetRoad();
    
    private:

        // the attributes of the tile
        SDL_Rect box;

        // tile type
        TileType type;

        SDL_Point position;

        Wall* wall;
        Road* road;
};