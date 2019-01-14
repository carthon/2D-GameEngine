#pragma once
#include "ECS.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "Engine.h"

class Tile : public Component{
public:
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;
	Vector2D position;

	Tile() = default;

	~Tile() {
		SDL_DestroyTexture(texture);
	}

	Tile(int srcX, int srcY, int xpos, int ypos, int tileSize, int tileScale, std::string id) {		
		texture = Engine::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tileSize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tileSize * tileScale;
		
	}
	void Update() override {
		destRect.x = position.x - Engine::camera.x;
		destRect.y = position.y - Engine::camera.y;
	}
	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};