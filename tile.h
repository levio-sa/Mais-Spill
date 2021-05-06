#pragma once

#include <SDL2/SDL.h>>

class ServerPlayer;
class Wall;
class Point;
class Blinky;

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

        // // Sets pointer to point in the tile
        // void SetPoint(Point* wall);

        // // Sets pointer to Blinky in the tile
        // void SetBlinky(Blinky* blinky);

        // Sets position of the tile
        void SetPos(int x, int y);

        // Sets type of the tile
        void SetType(int t); // should I go with type or wall and road?

        // Returns pointer to ServerPlayer in the tile
        ServerPlayer* GetServerPlayer();
        
        // Returns pointer to wall in the tile
        Wall* GetWall();

        // Returns pointer to wall in the tile
        Point* GetPoint();

        // Returns pointer to wall in the tile
        Blinky* GetBlinky();
    
    private:

        // the attributes of the tile
        SDL_Rect box;

        // tile type
        TileType type;

        SDL_Point position;
};