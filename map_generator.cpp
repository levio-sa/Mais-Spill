#include "map_generator.h"
#include <iostream>

MapGenerator::MapGenerator(TileGraph* tileGraph, TextureManager* textureManager)
{
	pTileGraph = tileGraph;
	pTextureManager = textureManager;
}

bool MapGenerator::Load(std::string path)
{
	// std::fstream file;

    // file.open(path.c_str(),std::ios::in);
    // if(file.is_open() == false){
    //     std::cout<<"Bad day\n";
	// 	return false;
    // }
    // else{
    //     std::cout<<"Good day\n";
    // }
	// file.close();

	//Create a file stream
	std::fstream file;

	// Open the file and check if successful
	file.open("maze.txt"/* .c_str() */, std::ios::in);
	printf("16\n");
	std::cout<<path;
	// Return false if we failed to open the file
	if (file.is_open() == false){
		printf("Failed to load map\n");
		printf("h\n");
		return false;
	}
	
	printf("22\n");
	std::string line;

	int x = 0;
	int y = 0;

	// Read the file line by line
	while (std::getline(file, line)) {
		// Break the line into chars vector
		std::vector<char> chars(line.begin(), line.end());

		for (unsigned int x = 0; x < chars.size(); x++) {
			std::cout<<"x and y"<<x<<" "<<y<<"\n";
			GameObject* newObject = NULL;
			Tile* tile = pTileGraph->GetTileAt(x, y);

			// Create diffrent object depending on the char
			switch (chars[x])
			{
				// case 'x':
				// 	newObject = new Wall(tile, pTextureManager->Get("wall"));
				// 	break;
				// case '.':
				// 	newObject = new Point(tile, pTextureManager->Get("point"));
				// 	break;
				// case 'p':
				// 	newObject = new Pacman(tile, pTextureManager->Get("pacman"));
				// 	break;
				// case 'b':
				// 	newObject = new Blinky(tile, pTextureManager->Get("blinky"));
				// 	break;
                case '1':
                    newObject = new Wall(tile, pTextureManager->Get("wall"));
					break;
                case '0':
                    newObject = new Road(tile, pTextureManager->Get("road"));
					break;
			}
			printf("59");

			// If the object was created, add it to the vector
			if (newObject != NULL)
				objectVector.push_back(newObject);
		}

		y++;
	}

	// Close the file
	file.close();

	return true;
}

void MapGenerator::Populate(std::vector<GameObject*>& vector)
{
	for (unsigned int i = 0; i < objectVector.size(); i++) {
		vector.push_back(objectVector[i]);
	}
}
