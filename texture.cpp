#include "texture.h"

//doubt
SDL_Renderer* Texture::Renderer = NULL;

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	Free();
}

bool Texture::LoadFromBitMapImage(std::string path, Uint8 r, Uint8 g, Uint8 b)
{
	// Free the previous texture
	Free();

    //doubt
	// Return if the renderer was not set
	if (Renderer == NULL)
		return false;

	// Load image to a surface
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	// Set color key
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));

	// Create texture from the surface
	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL) {
		printf("Unable to create texture from surface %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	// Set width and height of the texture
	width = loadedSurface->w;
	height = loadedSurface->h;

	// Free the surface
	SDL_FreeSurface(loadedSurface);

	return true;
}

bool Texture::LoadFromPNGImage( std::string path, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0 )
{
	//Get rid of preexisting texture
	free();

    //doubt
	// Return if the renderer was not set
	if (Renderer == NULL)
		return false;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
	}

    //Color key image
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, r, g, b ) );

    //Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface( Texture::Renderer, loadedSurface );
    if( texture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return false;
    }

    //Get image dimensions
    width = loadedSurface->w;
    height = loadedSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

	return true;
}

bool Texture::LoadFromRenderedText(TTF_Font* font, std::string text, SDL_Color textColor)
{
	// Free the previous texture
	Free();

    //doubt
	// Return if the renderer was not set
	if (Renderer == NULL)
		return false;

	// Render the text using SDL_ttf library
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (loadedSurface == NULL) {
		printf("Unable to render text! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// Create a texture from generated surface
	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL) {
		printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Set width and height of the texture
	width = loadedSurface->w;
	height = loadedSurface->h;

	// Free the surface
	SDL_FreeSurface(loadedSurface);

	return true;
}

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip renderFlip)
{
	// Return if the renderer was not set
	if (Renderer == NULL)
		return;

    //Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, GetWidth(), GetHeight() };

    //Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(Renderer, texture, clip, &renderQuad, angle, center, renderFlip);
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(texture, blendMode);
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::Free()
{
	if (texture != NULL) {
		// Free the texture and set its pointer to NULL
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}