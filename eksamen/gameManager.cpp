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

void gameManager::init(const char* title, int posx, int posy, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL2 initialisation failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(title, posx, posy, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, NULL);
    if (renderer == NULL) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
    running = true;
    snake = new Snake(map / 2, map / 2, rand() % 4, renderer);
}

void gameManager::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                snake->setDir(Snake::NORTH);
                break;
            case SDLK_DOWN:
                snake->setDir(Snake::SOUTH);
                break;
            case SDLK_LEFT:
                snake->setDir(Snake::WEST);
                break;
            case SDLK_RIGHT:
                snake->setDir(Snake::EAST);
                break;
            case SDLK_RETURN:
                if (!snake->isAlive()) running = false;
                break;
            default:
                break;
            }
        }
        else if (event.type == SDL_QUIT) running = false;
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