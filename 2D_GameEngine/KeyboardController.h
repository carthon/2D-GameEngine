#pragma once
#include "Engine.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	Transform *transform;
	Sprite* sprite;
	SDL_Event userEvent;

	void Init() override {
		transform = &entity->GetComponent<Transform>();
		sprite = &entity->GetComponent<Sprite>();
		userEvent.type = SDL_USEREVENT;
		userEvent.user.code = 0;
		userEvent.user.data1 = NULL;
		userEvent.user.data2 = NULL;

	}
	void Update() override {
		if (Engine::event.type == SDL_KEYDOWN) {
			switch (Engine::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_s:
				transform->velocity.y = +1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = +1;
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_ESCAPE:
				Engine::running = false;
			case SDLK_F5:
				std::cout << "Restart event disabled." << std::endl;
				//SDL_PushEvent(&userEvent);
				break;
			default:
				break;
			}
		}
		if (Engine::event.type == SDL_KEYUP) {
			switch (Engine::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}

		}
	}

private:

};