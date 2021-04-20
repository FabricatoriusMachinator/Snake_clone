#include "gameManager.h"

gameManager* game = nullptr;

int main(int argc, char* argv[]) {
    //srand(time(NULL));
    const int frameRate = 10;
    const int frameDelay = 1000 / frameRate;

    Uint32 frameTime;
    int frameElapsedTime;

    game = new gameManager();
    game->init("Snake in C++ with SDL2 help", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize, windowSize);
    while (game->isRunning()) {
        frameTime = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameElapsedTime = SDL_GetTicks() - frameTime;
        if (frameDelay > frameElapsedTime)
            SDL_Delay(frameDelay - frameElapsedTime);
    }
    game->clean();
    return 0;
}
