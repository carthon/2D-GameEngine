#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"

class Collider : public Component {
public:
	SDL_Rect collider;
	SDL_Texture* texture;

	Vector2D position;

	bool fixedSize;
	std::string tag;
	SDL_Rect destRect, srcRect;

	Transform* transform;

	Collider(std::string t) {
		tag = t;
	}

	Collider(std::string t, int xpos, int ypos, int size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	Collider(std::string t, int xpos, int ypos, int sizeW, int sizeH) {
		tag = t;
		position.x = xpos;
		position.y = ypos;
		collider.h = sizeH;
		collider.w = sizeW;
	}

	void Init() override {
		if (!entity->hasComponent<Transform>()) {
			entity->AddComponent<Transform>();
		}
		transform = &entity->GetComponent<Transform>();
		fixedSize = true;
		texture = TextureManager::LoadTexture("data/map/collider.png");
		srcRect = { 0, 0, 32, 32 };
		destRect = { collider.x + static_cast<int> (position.x), collider.y + static_cast<int>(position.y), collider.w, collider.h };
	}

	void Update() override {
		if (tag != "terrain") {
			collider.x = static_cast<int> (transform->position.x) + static_cast<int> (position.x);
			collider.y = static_cast<int> (transform->position.y) + static_cast<int> (position.y);
			if (!fixedSize){
				collider.w = transform->width * transform->scale;
				collider.h = transform->height * transform->scale;
			}
		}

		destRect.x = collider.x - Engine::camera.x;
		destRect.y = collider.y - Engine::camera.y;
	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};