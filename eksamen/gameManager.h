#pragma once

#include "globalConstants.h"
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Snake.h"

class gameManager {

public:
    gameManager();
    ~gameManager();
    void init(const char* title, int posx, int posy, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning() { return running; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Snake* snake;

};

