#pragma once

#include <SDL2/SDL.h>>

class Tile {
    public:

        const static int WIDTH = 25;
        const static int HEIGHT = 25;

        // initializes position and type
        Tile( int x, int y, TileType tileType );

        // shows the tile
        void Render( SDL_Rect& camera );

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

        // Sets pointer to Pacman in the tile
        void SetPacman(Pacman* pacman);

        // Sets pointer to wall in the tile
        void SetWall(Wall* wall);

        // Sets pointer to point in the tile
        void SetPoint(Point* wall);

        // Sets pointer to Blinky in the tile
        void SetBlinky(Blinky* blinky);

        // Sets position of the tile
        void SetPos(int x, int y);

        // Returns pointer to Pacman in the tile
        Pacman* GetPacman();
        
        // Returns pointer to wall in the tile
        Wall* GetWall();

        // Returns pointer to wall in the tile
        Point* GetPoint();

        // Returns pointer to wall in the tile
        Blinky* GetBlinky();

        // Returns position of the tile
        SDL_Point GetPosition();
    
    private:

        // the attributes of the tile
        SDL_Rect box;

        // tile type
        TileType type;

        SDL_Point position;
}