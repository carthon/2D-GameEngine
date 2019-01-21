#include "Engine.h"
#include "Components.h"
#include "Map.h"
#include "Collision.h"
#include "Vector2D.h"
#include "AssetManager.h"
#include <string>

using namespace std;

Map* levelMap;
SDL_Renderer* Engine::renderer = nullptr;
Manager manager;
SDL_Event Engine::event;
bool Engine::running = false;
bool Engine::restart = false;

AssetManager* Engine::assets = new AssetManager(&manager);

SDL_Rect Engine::camera = { 0, 0, 800, 640 };

auto& player(manager.AddEntity());
auto& label(manager.AddEntity());


Engine::Engine() {
	window = nullptr;
	renderer = nullptr;
	running = false;
	restart = false;
}

Engine::~Engine() {

}

void Engine::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == NULL) {
		cout << "Subsystems initialized..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window){
			cout << "Window created..." << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created..." << endl;
		}
		if (TTF_Init() == -1) {
			cout << "Error : SDL_TTF" << endl;
		}

		assets->AddTexture("terrain", "data/map/outworld.png");
		assets->AddTexture("player", "data/images/walkcycle/BODY_male.png");
		assets->AddTexture("projectile", "data/images/projectile.png");
		assets->AddFont("arial", "data/fonts/arial.ttf", 16);
		SDL_Color white = { 255, 255, 255, 255 };
		label.AddComponent<UILabel>(10, 10, "TestString", "arial", white);

		levelMap = new Map("terrain", 2, 32);

		levelMap->LoadMap("data/map/outworld.map");

		player.AddComponent<Transform>(64, 64, 2);
		player.GetComponent<Transform>().position.x = 200;
		player.GetComponent<Transform>().position.y = 200;
		player.AddComponent<Sprite>("player", true);
		player.AddComponent<KeyboardController>();
		player.AddComponent<Collider>("player", 32, 32, 64, 96);
		player.AddGroup(groupPlayers);

		assets->CreateProjectile(Vector2D(600, 300), Vector2D(-1,0), 200, 2, "projectile");

		running = true;
	}
	else {
		running = false;
	}
}
auto& tiles(manager.GetGroup(Engine::groupMap));
auto& players(manager.GetGroup(Engine::groupPlayers));
auto& colliders(manager.GetGroup(Engine::groupColliders));
auto& projectiles(manager.GetGroup(Engine::groupProjectiles));

void Engine::Update() {
	Collider playerCol = player.GetComponent<Collider>();
	Vector2D playerPos = player.GetComponent<Transform>().position;
	Vector2D velocity;

	manager.Update();
	manager.Refresh();
	camera.x = player.GetComponent<Transform>().position.x - 400;
	camera.y = player.GetComponent<Transform>().position.y - 320;


	for (auto& c : colliders) {
		Collider otherCollider = c->GetComponent<Collider>();
		if (Collision::AABB(otherCollider, playerCol, 0.5f)) {
			Vector2D velocity = player.GetComponent<Transform>().velocity;
			player.GetComponent<Transform>().position = playerPos - velocity;
			label.GetComponent<UILabel>().SetLabelText("X: " + to_string(velocity.x) + " Y: " + to_string(velocity.y) , "arial");
		}
	}
	for (auto& p : projectiles) {
		Collider otherCollider = p->GetComponent<Collider>();
		if (Collision::AABB(otherCollider, playerCol, 0.5f)) {
			cout << "Hit!" << endl;
			p->Destroy();
		}
	}

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > (levelMap->GetSizeX() - camera.w)) {
		camera.x = levelMap->GetSizeX() - camera.w;
	}
	if (camera.y > (levelMap->GetSizeY() - camera.h)) {
		camera.y = levelMap->GetSizeY() - camera.h;
	}
}

void Engine::Render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) t->Draw();
	for (auto& c : colliders) c->Draw();
	for (auto& p : players) p->Draw();
	for (auto& p : projectiles) p->Draw();
	label.Draw();
	SDL_RenderPresent(renderer);
}



void Engine::HandleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;

	case SDL_USEREVENT:
		restart = true;
		running = false;
		break;
	default:
		break;
	}
}

void Engine::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
	cout << "Game cleanned..." << endl;
}

bool Engine::IsRunning() { return running; }