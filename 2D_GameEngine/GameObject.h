#pragma once
#include "Engine.h"

class GameObject {
public:
	GameObject(const char* texturesheet, int xpos, int ypos);
	~GameObject();
	
	void Update();
	void Render();

private:
	int x, y;

	SDL_Texture* objTexture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

};