#include "gameManager.h"

int main(int argc, char* argv[]) {

    gameManager* gameMngr = nullptr;
    const int frameRate = 10;
    const int frameDelay = 1000 / frameRate;

    Uint32 frameTime;
    int frameElapsedTime;

    gameMngr = new gameManager();
    gameMngr->start("Snake in C++ with SDL2 help", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize, windowSize);
    while (gameMngr->isRunning()) {
        frameTime = SDL_GetTicks();

        gameMngr->eventHandler();
        gameMngr->update();
        gameMngr->render();

        frameElapsedTime = SDL_GetTicks() - frameTime;
        if (frameDelay > frameElapsedTime)
            SDL_Delay(frameDelay - frameElapsedTime);
    }
    return 0;
}
