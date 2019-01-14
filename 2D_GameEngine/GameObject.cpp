#include "GameObject.h"
#include "TextureManager.h"

using namespace std;

GameObject::GameObject(const char* textureSheet, int xpos, int ypos) {
	x = xpos;
	y = ypos;
	objTexture = nullptr;
	objTexture = TextureManager::LoadTexture(textureSheet);

	if (!objTexture) {
		cout << "Unable to load image " << textureSheet << "! Error: " << IMG_GetError() << endl;
	}
}

void GameObject::Update() {
	x++;
	y++;
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
	SDL_RenderCopy(Engine::renderer, objTexture, &srcRect, &destRect);
}