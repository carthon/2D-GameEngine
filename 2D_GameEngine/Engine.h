#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Collider;
class AssetManager;

class Engine {
private:
	SDL_Window* window;

public:
	Engine();
	~Engine();
	static bool running;
	static bool restart;

	void Init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void Update();
	void Render();
	void Clean();
	void HandleEvents();

	bool IsRunning();
	static SDL_Renderer* renderer;
	static AssetManager* assets;
	static SDL_Event event;
	static SDL_Rect camera;

	enum GroupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemys,
		groupColliders,
		groupProjectiles
	};
};