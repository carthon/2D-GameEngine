#pragma once
#include <map>
#include <string>
#include "Vector2D.h"
#include "TextureManager.h"
#include "ECS.h"
#include "SDL_ttf.h"

class AssetManager {
private:
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	Manager *manager;
public:
	AssetManager(Manager* manager);
	~AssetManager();
	//Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture *GetTexture(std::string id);

	void AddFont(std::string id, const char* path, int fontsize);
	TTF_Font* GetFont(std::string id);
	//GameObject
	void CreateProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string id);

};