#include "TextureManager.h"

using namespace std;
SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface *temp = nullptr; 
	temp = IMG_Load(fileName);
	if (temp == nullptr) {
		cout << "Unable to load image. Error: " << IMG_GetError() << endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::renderer, temp);
	SDL_FreeSurface(temp);

	if (!texture) {
		cout << "Unable to load texture. Error: " << SDL_GetError() << endl;
	}

	return texture;
}


void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Engine::renderer, texture, &src, &dest, NULL, NULL, flip);
}