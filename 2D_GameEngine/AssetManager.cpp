#pragma once
#include "AssetManager.h"
#include "Components.h"
#include "ECS.h"
AssetManager::AssetManager(Manager* manager) : manager(manager)
{}

AssetManager::~AssetManager()
{
}

void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}
SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

void AssetManager::AddFont(std::string id, const char * path, int fontsize)
{
	fonts.emplace(id, TTF_OpenFont(path, fontsize));
}

TTF_Font * AssetManager::GetFont(std::string id)
{
	return fonts[id];
}

void AssetManager::CreateProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string id)
{
	auto& projectile(manager->AddEntity());
	projectile.AddComponent<Transform>(position.x, position.y, 32, 32, 1);
	projectile.AddComponent<Sprite>(id, false);
	projectile.AddComponent<Projectile>(range, speed, velocity);
	projectile.AddComponent<Collider>("projectile");
	projectile.AddGroup(Engine::groupProjectiles);

}
