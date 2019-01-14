#pragma once
#include "ECS.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
private:
	SDL_Rect position;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
	std::string labelText;

public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color): 
	labelText(text), labelFont(font), textColor(color) {
		position.x = xpos;
		position.y = ypos;
		SetLabelText(text, font);
	}
	~UILabel(){}

	void SetLabelText(std::string text, std::string font) {
		SDL_Surface* surf = TTF_RenderText_Blended(Engine::assets->GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Engine::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}
	void Draw() override {
		SDL_RenderCopy(Engine::renderer, labelTexture, nullptr, &position);
	}
};