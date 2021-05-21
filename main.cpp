//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "collision.h"
#include "map_generator.h"
#include "menu.h"
#include "road.h"
#include "server_player.h"
#include "texture.h"
#include "texture_manager.h"
#include "tile_graph.h"
#include "wall.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( /* Tile* tiles[]  */);

//Frees media and shuts down SDL
void close( /* Tile* tiles[]  */);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Map of all Textures
TextureManager gTextureManager;

// List of all objects
std::vector<GameObject*> gGameObjectList;

// List of all tiles
// TileGraph gTileGraph(20, 20);
TileGraph gTileGraph; // empty TileGraph object

// Generates a map
// MapGenerator gMapGenerator(&gTileGraph, &gTextureManager);
MapGenerator gMapGenerator(&gTileGraph, &gTextureManager);

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Mais-Spill", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				// Create software renderer if we couldn't create hardware accelerated one
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
				if(gRenderer == NULL)
				{
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;	
				}
			}
			if( success )
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}
	Texture::Renderer=gRenderer;
	return success;
}

bool loadMenuMedia()
{

	//Load menu texture
	TTF_Font* menuFont = TTF_OpenFont( "Fonts/lazy.ttf", 28);
	if(menuFont == NULL){
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;	
	}
	
	//render text
	SDL_Color textColor = {0,0,0};
	Texture* menuTexture = new Texture();
	if(!menuTexture->LoadFromRenderedText(menuFont,"menu",textColor)) {
		printf( "Failed to render text texture!\n" );
		return false;
	}

	gTextureManager.Add("menu", menuTexture); // provide texture manager to the menu class. Now only single loading of texture reqd compared to the UDP game

	return true;
}

bool loadMedia(int tileGraphWidth, int tileGraphHeight, std::string mapFile)
{

	//Load menu texture
	TTF_Font* menuFont = TTF_OpenFont( "Fonts/lazy.ttf", 28);
	if(menuFont == NULL){
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;	
	}
	// Load wall texture
	Texture* wallTexture = new Texture();
	if (!wallTexture->LoadFromPNGImage("Sprites/bg.png"))
		return false;
	
	// Load road texture
	Texture* roadTexture = new Texture();
	if (!roadTexture->LoadFromPNGImage("Sprites/bg.png"))
		return false;

	//render text
	SDL_Color textColor = {0,0,0};
	Texture* menuTexture = new Texture();
	if(!menuTexture->LoadFromRenderedText(menuFont,"menu",textColor)) {
		printf( "Failed to render text texture!\n" );
		return false;
	}

	// Add loaded textures to a TextureManager
	gTextureManager.Add("menu", menuTexture);
	gTextureManager.Add("wall", wallTexture);
	gTextureManager.Add("road", roadTexture);

	// TileGraph Setup
	gTileGraph.Setup(tileGraphWidth,tileGraphHeight);
	printf("%d\n",gTileGraph.width);
	printf("%d\n",gMapGenerator.pTileGraph->width);

	// Set static variables for objects
	GameObject::tileGraph = &gTileGraph;

	Wall::CreateClips();
	Road::CreateClips();

	// Load Map
	if (!gMapGenerator.Load(mapFile)){
		printf("Failed to load map");
		return false;
	}

	gMapGenerator.Populate(gGameObjectList);



/* 	//Load dot texture
	if( !gDotTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "tiles.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	} */

	return true;
}

void close()
{
	/* //Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	} */

	/* //Free loaded images
	gDotTexture.free();
	gTileTexture.free(); */

	// Free all objects
	for (unsigned int i = 0; i < gGameObjectList.size(); i++)
		delete gGameObjectList[i];

	// Free all textures
	gTextureManager.Free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		/* //The level tiles
		Tile* tileSet[ TOTAL_TILES ]; */

		// Load menu media
		if(!loadMenuMedia()){
			printf("Failed to load menu media\n");
		}
		else{
			
			bool quit = false; // this bool decides if game is quit from inside Menu Functions

			// default values of width and height of TileMap modified in Menu Funcs
			int width = 20, height = 20;

			// file containing map. Generated in menu functions
			std::string mapFile="maze.txt"; 
			// MenuFunction(width, height);



			while(!quit){

				// Menu Functions -> handle events there only
				// MenuFunction(width, height);
				
				//Load game media
				if( !loadMedia((width+1)*2-1, (height+1)*2-1, mapFile) ){
					printf( "Failed to load media!\n" );
					break;
				}
				else{	
					// //Main loop flag
					// bool quit = false;

					//Event handler
					SDL_Event e;

					/* //The dot that will be moving around on the screen
					Dot dot; */

					//Level camera
					SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

					//While application is running
					while( !quit ){
						//Handle events on queue
						while( SDL_PollEvent( &e ) != 0 ){
							//User requests quit
							if( e.type == SDL_QUIT )
							{
								quit = true;
							}

							/* //Handle input for the dot
							dot.handleEvent( e ); */
						}

						/* //Move the dot
						dot.move( tileSet );
						dot.setCamera( camera ); */

						//Clear screen
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderClear( gRenderer );
						Texture* menuTexture = gTextureManager.Get("menu");
						menuTexture->Render( ( SCREEN_WIDTH - menuTexture->GetWidth() ) / 2, ( SCREEN_HEIGHT - menuTexture->GetHeight() ) / 2 );
						for (unsigned int i = 0; i < gGameObjectList.size(); i++)
						gGameObjectList[i]->Render();
		/* 				//Render level
						for( int i = 0; i < TOTAL_TILES; ++i )
						{
							tileSet[ i ]->render( camera );
						} */

		/* 				//Render dot
						dot.render( camera ); */

						//Update screen
						SDL_RenderPresent( gRenderer );
					}
				}
			}
		}
		//Free resources and close SDL
		close(/*  tileSet  */);
	}

	return 0;
}