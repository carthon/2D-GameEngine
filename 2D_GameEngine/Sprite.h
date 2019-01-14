#pragma once
#include <map>
#include <SDL.h>
#include "TextureManager.h"
#include "Animation.h"
#include "Components.h"
#include "AssetManager.h"

class Sprite : public Component {
private:
	Transform * transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	std::string animationPlaying;
	bool playing = false;

public:

	int animIndex = 0;

	std::map<std::string, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	Sprite() = default;
	Sprite(std::string id) {
		texture = nullptr;
		SetTexture(id);
		if (!texture) {
			std::cout << "Error al cargar la textura " << id << ". Error:" << SDL_GetError() << std::endl;
		}
	}
	Sprite(std::string id, bool isAnimated) {
		animated = isAnimated;
		if (animated) {
			//Animation idle_u = Animation(0, 1, 100);
			//Animation idle_r = Animation(3, 1, 200);
			//Animation idle_d = Animation(2, 1, 100);
			Animation walk_u = Animation(0, 9, 100);
			Animation walk_r = Animation(3, 9, 100);
			Animation walk_d = Animation(2, 9, 100);

			//animations.emplace("idle_u", idle_u);
			//animations.emplace("idle_d", idle_d);
			//animations.emplace("idle_r", idle_r);
			animations.emplace("walk_u", walk_u);
			animations.emplace("walk_d", walk_d);
			animations.emplace("walk_r", walk_r);
		}
		animationPlaying = "walk_r";
		Play(animationPlaying);
		SetTexture(id);
	}
	~Sprite() {
	}

	std::string GetAnimPlaying() {
		return animationPlaying;
	}

	void SetTexture(std::string id) {
		texture = Engine::assets->GetTexture(id);
	}
	void Init() override {
		transform = &entity->GetComponent<Transform>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void Update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Engine::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Engine::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

		if (transform->velocity.x == 1 || transform->velocity.x == -1) {
			animationPlaying = "walk_r";
			playing = true;
		}		
		if (transform->velocity.y == 1) {
			animationPlaying = "walk_d";
			playing = true;
		}		
		if (transform->velocity.y == -1) {
			animationPlaying = "walk_u";
			playing = true;
		}
		if (transform->velocity.x == 0 && transform->velocity.y == 0)
			playing = false;

		Play(animationPlaying.c_str());

		if (!playing)
			frames = 1;
	}
	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(std::string animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};