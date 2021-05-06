#include "road.h"

SDL_Rect Road::textureClips[16];

//Road::Road()
//{
//	currTile = NULL;
//
//	position.x = 0;
//	position.y = 0;
//
//	collider.w = Width;
//	collider.h = Height;
//}

void Road::CreateClips()
{
	// 0000 - standalone
	// 1000 - N
	// 0100 - E
	// 0010 - S
	// 0001 - W

	textureClips[0] = { 0, 0, 25, 25 };
	textureClips[DIR_N] = { 25, 0, 25, 25 };
	textureClips[DIR_E] = { 50, 0, 25, 25 };
	textureClips[DIR_S] = { 75, 0, 25, 25 };
	textureClips[DIR_W] = { 0, 25, 25, 25 };
	textureClips[DIR_N | DIR_E] = { 25, 25, 25, 25 };
	textureClips[DIR_S | DIR_E] = { 50, 25, 25, 25 };
	textureClips[DIR_S | DIR_W] = { 75, 25, 25, 25 };
	textureClips[DIR_N | DIR_W] = { 0, 50, 25, 25 };
	textureClips[DIR_N | DIR_S] = { 50, 100, 25, 25 };
	textureClips[DIR_E | DIR_W] = { 75, 100, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_W] = { 25, 50, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_S] = { 50, 50, 25, 25 };
	textureClips[DIR_E | DIR_S | DIR_W] = { 75, 50, 25, 25 };
	textureClips[DIR_N | DIR_S | DIR_W] = { 0, 75, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_S | DIR_W] = { 25, 75, 25, 25 };
}

Road::Road(Tile* tile, Texture* texture)
{
	currTile = tile;

	RoadTexture = texture;

	if (currTile != NULL) {
		// currTile->SetRoad(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	UpdateConnections();

	std::array<Tile*, 4> neighbours = tileGraph->GetNeighbours(this->currTile);
	// for (int i = 0; i < 4; i++) {
	// 	if (CheckForRoad(neighbours[i]))
	// 		// neighbours[i]->GetRoad()->UpdateConnections();
	// }
}

Road::~Road()
{
	Free();
}

void Road::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		// currTile->SetRoad(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		// currTile->SetRoad(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
}

void Road::UpdateConnections()
{
	std::array<Tile*, 4> neighbours = tileGraph->GetNeighbours(this->currTile);

	connections = 0;

	if (CheckForRoad(neighbours[0]))
		connections |= DIR_S;
	if (CheckForRoad(neighbours[1]))
		connections |= DIR_E;
	if (CheckForRoad(neighbours[2]))
		connections |= DIR_N;
	if (CheckForRoad(neighbours[3]))
		connections |= DIR_W;
}

void Road::Delete()
{
	// Calling base function
	GameObject::Delete();

	// currTile->SetRoad(NULL);
}

void Road::Render()
{
	RoadTexture->Render(position.x, position.y, &textureClips[connections]);
}

SDL_Rect Road::GetCollider()
{
	return collider;
}

SDL_Point Road::GetPosition()
{
	return position;
}

Tile* Road::GetTile()
{
	return currTile;
}

bool Road::CheckForRoad(Tile* tile)
{
	// if (tile != NULL && tile->GetRoad() != NULL)
	// 	return true;

	return false;
}
