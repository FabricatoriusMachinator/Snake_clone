#include "Snake.h"

Snake::Snake(int startPosX, int startPosY, int dir, SDL_Renderer* ren) {
    direction = dir;
    renderer = ren;
    alive = true;
    headTexture = setTexture("head.bmp");
    bodyTexture = setTexture("body.bmp");
    foodTexture = setTexture("fruit.bmp");
    tailTexture = setTexture("tail.bmp");
    fruit = new Segment(0, 0);
    do {
        fruit->x = rand() % map;
        fruit->y = rand() % map;
    } while (fruit->x != startPosX && fruit->y != startPosY);
    grow(startPosX, startPosY);
}

Snake::~Snake() {
    for (int i = 0; i < body.size(); i++)
        delete body[i];
}

void Snake::grow(int x, int y) {
    Segment* seg = new Segment(x, y);
    body.push_back(seg);
}

void Snake::movement() {
    if (!alive) return;
    int dx;
    int dy;
    switch (direction) {
    case Snake::UP:
        dx = 0;
        dy = -1;
        break;
    case Snake::DOWN:
        dx = 0;
        dy = 1;
        break;
    case Snake::RIGHT:
        dx = 1;
        dy = 0;
        break;
    case Snake::LEFT:
        dx = -1;
        dy = 0;
        break;
    default:
        break;
    }
    for (int i = body.size() - 1; i > 0; i--) {
        body[i]->x = body[i - 1]->x;
        body[i]->y = body[i - 1]->y;
    }
    Segment* snakeHead = *(body.begin());
    snakeHead->x += dx;
    snakeHead->y += dy;
}

SDL_Texture* Snake::setTexture(const char* filename) {
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if (!surface)
        std::cout << "Failed to load image " << filename << ": " << SDL_GetError() << std::endl;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Snake::setDir(int dir) {
    switch (direction) {
    case Snake::UP:
        if (dir == Snake::DOWN) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) 
            return;
        break;
    case Snake::DOWN:
        if (dir == Snake::UP) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) 
            return;
        break;
    case Snake::RIGHT:
        if (dir == Snake::LEFT) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) 
            return;
        break;
    case Snake::LEFT:
        if (dir == Snake::RIGHT) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) 
            return;
        break;
    }
    direction = dir;
}

void Snake::collider() {
    Segment* head = body[0];
    if (head->x < 0 || head->x > map - 1 || head->y < 0 || head->y > map - 1) {
        alive = false;
        return;
    }
    for (int i = 1; i < body.size(); i++) {
        if (head->x == body[i]->x && head->y == body[i]->y) {
            alive = false;
            break;
        }
    }
}

void Snake::render() {
    SDL_Rect rect;
    rect.w = rect.h = characterSize;
    rect.x = fruit->x * characterSize;
    rect.y = fruit->y * characterSize;
    SDL_RenderCopy(renderer, foodTexture, NULL, &rect);

    rect.x = body[0]->x * characterSize;
    rect.y = body[0]->y * characterSize;
    SDL_RenderCopyEx(renderer, headTexture, NULL, &rect,
        (direction == Snake::LEFT || direction == Snake::RIGHT) ? 90.0 : 0.0,
        NULL, (direction == Snake::LEFT) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);



    for (int i = 1; i < body.size(); i++) {
        rect.x = body[i]->x * characterSize;
        rect.y = body[i]->y * characterSize;
        SDL_RenderCopy(renderer, bodyTexture, NULL, &rect);


        if (i == body.size() - 1) {
            SDL_RenderCopyEx(renderer, tailTexture, NULL, &rect,
                (direction == Snake::LEFT || direction == Snake::RIGHT) ? 180.0:0.0,
                NULL, (direction == Snake::LEFT) ? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
        }
    }
}

void Snake::eat() {
    if (body[0]->x == fruit->x && body[0]->y == fruit->y)
        grow(body[body.size() - 1]->x, body[body.size() - 1]->y);
    else return;

    spawnFruit();
}

bool Snake::checkFruitSpawn()
{
    for (auto s : body) {
        if (fruit->x == s->x && fruit->y == s->y) {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void Snake::spawnFruit() {
    
    while (!checkFruitSpawn()) {
        fruit->x = rand() % map;
        fruit->y = rand() % map;
    }
}
