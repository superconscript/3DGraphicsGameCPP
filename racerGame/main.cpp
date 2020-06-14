#include "gameEngine.h"

gameEngine *game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new gameEngine();
	game->init("GameWindow", 0, 0, 800, 600, false);

	while (game->running())
	{
//	while (game->)
		frameStart = SDL_GetTicks();
	
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
}

