#include "gameManager.h"

gameManager::gameManager() {
    window = nullptr;
    renderer = nullptr;
    running = false;
    snake = nullptr;
}

gameManager::~gameManager() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    delete snake;
}

void gameManager::start(const char* title, int x, int y, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL2 initialisation failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, NULL);
    if (renderer == NULL) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
    running = true;
    snake = new Snake(map / 2, map / 2, 2, renderer);
}

void gameManager::eventHandler() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                snake->setDir(Snake::UP);
                break;
            case SDLK_DOWN:
                snake->setDir(Snake::DOWN);
                break;
            case SDLK_LEFT:
                snake->setDir(Snake::LEFT);
                break;
            case SDLK_RIGHT:
                snake->setDir(Snake::RIGHT);
                break;
            case SDLK_ESCAPE:
                if (!snake->isAlive()) running = false;
                break;
            default:
                break;
            }
        }
        else if (e.type == SDL_QUIT) running = false;
    }
}

void gameManager::update() {
    if (snake->isAlive()) {
        snake->collider();
        snake->eat();
        snake->movement();
    }
}

void gameManager::render() {
    SDL_RenderClear(renderer);
    snake->render();
    if (!snake->isAlive()) {
        running = false;
    }
    SDL_RenderPresent(renderer);
}

void gameManager::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}