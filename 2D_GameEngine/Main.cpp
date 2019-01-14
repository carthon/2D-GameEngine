#include "Engine.h" 

using namespace std;

int main(int argc, char *argv[]) {
	Engine *game = nullptr;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Engine();
	game->Init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->IsRunning()) {
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
			//cout << "Delay: " << frameDelay - frameTime << endl;
		}
	}

	game->Clean();

	return 0;
}