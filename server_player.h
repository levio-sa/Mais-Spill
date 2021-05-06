#pragma once

#include <algorithm>

#include <SDL2/SDL.h>
#include "texture.h"
#include "game_object.h"
#include "tile.h"
#include "tile_graph.h"
// #include "Point.h"
#include "move_direction.h"

// Just a temporary solution
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

class ServerPlayer : public GameObject
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of Player
	static const int Width = 25;
	static const int Height = 25;

	// Number of frames in movment animation
	static const int MoveFrames = 2;

	// Movement per frame
	static const int Velocity = 3;

	// ServerPlayer();

	ServerPlayer(Tile* tile, Texture* texture);
	~ServerPlayer();

	// Loads texture and sets up animation clips
	bool LoadMedia();

	// Sets postiton of ServerPlayer
	// void SetPos(int x, int y);

	// Sets the tile of the ServerPlayer
	void SetTile(Tile* newTile);

	// Sets the next tile (to which ServerPlayer will go)
	void SetNextTile(Tile* newNextTile);

	// Handles key presses
	void HandleEvents(SDL_Event* event);

	// Updates the posititon and check collision
	void Update();

	// Renders ServerPlayer
	void Render();

	// Mark the object to be deleted
	void Delete();

	// Releases texture memory
	// void Free();

	// Returns current direction of movement
	MoveDirection GetMoveDirection();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns ServerPlayer's tile
	Tile* GetTile();

	// Returns the tile which ServerPlayer is going to
	Tile* GetNextTile();

	// Returns true if ServerPlayer is moving
	bool IsMoving();

private:
	// Trys to move the ServerPlayer in desired direction
	// Returns true if successful, false otherwise
	bool TryToMove(MoveDirection direction);

	// Check if ServerPlayer is colliding with other collider
	bool CheckForCollision(const SDL_Rect &otherCollider);

	// Check if given collider is colliding with another collider
	bool CheckForCollision(const SDL_Rect &collider, const SDL_Rect &otherCollider);

	Texture* ServerPlayerTexture;

	SDL_Rect upAnimClips[2];
	SDL_Rect downAnimClips[2];
	SDL_Rect leftAnimClips[2];
	SDL_Rect rightAnimClips[2];

	int frame, frameCount;

	MoveDirection moveDir;
	MoveDirection nextDir;
	bool moving;
	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	SDL_Rect collider;
};
