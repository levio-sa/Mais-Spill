#pragma once

#include "game_object.h"
#include "texture.h"
#include "tile_graph.h"
#include "world_direction.h"

class Road : public GameObject
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of a Road
	static const int Width = 25;
	static const int Height = 25;

	// Creates connection clips
	static void CreateClips();

	// Road();

	Road(Tile* tile, Texture* texture);
	~Road();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the Road
	void SetTile(Tile* newTile);

	// Updates the texture of the Road to match connections
	void UpdateConnections();

	// Handles key presses
	// void HandleEvents(SDL_Event* event);

	// Updates the posititon and check collision
	// void Update();

	// Mark the object to be deleted
	void Delete();

	// Renders the Road
	void Render(SDL_Rect &camera);

	// Releases texture memory
	// void Free();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns Road's tile
	Tile* GetTile();

private:
	// Checks if the tile is valid and if there's a Road in it
	bool CheckForRoad(Tile* tile);

	Texture* RoadTexture;
	int connections;
	static SDL_Rect textureClips[16];

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

