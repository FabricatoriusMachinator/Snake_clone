#include "Snake.h"

Snake::Snake(int startx, int starty, char dir, SDL_Renderer* ren) {
    direction = dir;
    renderer = ren;
    alive = true;
    headTexture = loadTexture("head_body.bmp");
    bodyTexture = loadTexture("head_body.bmp");
    foodTexture = loadTexture("fruit.bmp");
    tailTexture = loadTexture("tail.bmp");
    fruit = new Segment(0, 0);
    do {
        fruit->x = rand() % map;
        fruit->y = rand() % map;
    } while (fruit->x != startx && fruit->y != starty);
    grow(startx, starty);
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
    int dx, dy;
    switch (direction) {
    case Snake::NORTH:
        dx = 0;
        dy = -1;
        break;
    case Snake::SOUTH:
        dx = 0;
        dy = 1;
        break;
    case Snake::EAST:
        dx = 1;
        dy = 0;
        break;
    case Snake::WEST:
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

SDL_Texture* Snake::loadTexture(const char* filename) {
    SDL_Surface* tSurface = SDL_LoadBMP(filename);
    if (!tSurface)
        std::cout << "Failed to load image " << filename << ": " << SDL_GetError() << std::endl;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_FreeSurface(tSurface);
    return texture;
}

void Snake::setDir(char dir) {
    switch (direction) {
    case Snake::NORTH:
        if (dir == Snake::SOUTH) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) return;
        break;
    case Snake::SOUTH:
        if (dir == Snake::NORTH) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) return;
        break;
    case Snake::EAST:
        if (dir == Snake::WEST) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) return;
        break;
    case Snake::WEST:
        if (dir == Snake::EAST) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) return;
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
    SDL_Rect r;
    r.w = r.h = characterSize;
    r.x = fruit->x * characterSize;
    r.y = fruit->y * characterSize;
    SDL_RenderCopy(renderer, foodTexture, NULL, &r);

    r.x = body[0]->x * characterSize;
    r.y = body[0]->y * characterSize;
    SDL_RenderCopyEx(renderer, headTexture, NULL, &r,
        (direction == Snake::WEST || direction == Snake::EAST) ? 90.0 : 0.0,
        NULL, SDL_FLIP_NONE);



    for (int i = 1; i < body.size(); i++) {
        r.x = body[i]->x * characterSize;
        r.y = body[i]->y * characterSize;
        SDL_RenderCopy(renderer, bodyTexture, NULL, &r);
        if (i == body.size() - 1) {
            SDL_RenderCopyEx(renderer, tailTexture, NULL, &r,
                (direction == Snake::WEST || direction == Snake::EAST) ? 90.0:0.0,
                NULL, SDL_FLIP_NONE);
        }
    }
}

void Snake::eat() {
    if (body[0]->x == fruit->x && body[0]->y == fruit->y)
        grow(body[body.size() - 1]->x, body[body.size() - 1]->y);
    else return;

    auto collides = [&]() {
        for (auto s : body) {
            if (fruit->x == s->x && fruit->y == s->y)
                return true;
        }
        return false;
    };

    do {
        fruit->x = rand() % map;
        fruit->y = rand() % map;
    } while (collides());
}