#include "gameManager.h"

int main(int argc, char* argv[]) {

    gameManager* gameMngr = nullptr;
    const int fps = 10;
    const int fDelay = 1000 / fps;

    Uint32 fTime;
    int fTimePassed;

    gameMngr = new gameManager();
    gameMngr->start("Eksamen Snake | Score: 0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize, windowSize);
    while (gameMngr->isRunning()) {
        fTime = SDL_GetTicks();

        gameMngr->eventHandler();
        gameMngr->update();
        gameMngr->render();

        fTimePassed = SDL_GetTicks() - fTime;
        if (fDelay > fTimePassed)
            SDL_Delay(fDelay - fTimePassed);
    }
    return 0;
}
