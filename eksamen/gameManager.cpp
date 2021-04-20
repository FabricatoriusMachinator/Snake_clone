#include "gameManager.h"

gameManager::gameManager() {
    window = nullptr;
    renderer = nullptr;
    running = false;
    snake = nullptr;
    title = "Eksamen Snake | Score: ";
}

gameManager::~gameManager() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    delete snake;
}

void gameManager::start(const char* title, int x, int y, int w, int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Initialization failed: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cerr << "Window coudln't be created: " << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, NULL);
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    running = true;
    snake = new Snake(board / 2, board / 2, Snake::RIGHT, renderer);
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
        else if (e.type == SDL_QUIT) 
            running = false;
    }
}

void gameManager::update() {
    
    title = "Eksamen Snake | Score: " + std::to_string(snake->score);
    if (snake->isAlive()) {
        snake->collider();
        snake->eat();
        SDL_SetWindowTitle(window, title.c_str());
        snake->movement();       
    }
    else if(!snake->isAlive())
    {
        running = false;
    }
}

void gameManager::render() {
    SDL_RenderClear(renderer);
    snake->render();
    SDL_RenderPresent(renderer);
}