#include "gameEngine.h"

gameEngine *game = nullptr;
float* deltaTime = new float( 1 / 60);


int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime; // frame rate in ms

	game = new gameEngine(deltaTime);
	game->init("GameWindow", 0, 0, 800, 600, false);

	while (game->running())
	{
//	while (game->)
		//game->setDeltaTime(*deltaTime);
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		*deltaTime = ((float)frameTime) / 1000;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		
	}
	delete (deltaTime);
	game->clean();

	return 0;
}

