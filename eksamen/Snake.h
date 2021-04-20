#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <SDL.h>
#include <cstdlib>
#include "globalConstants.h"

struct Segment {
    int x;
    int y;

    Segment(int posx, int posy) {
        x = posx;
        y = posy;
    }
};

class Snake {

public:
    Snake(int startx, int starty, int dir, SDL_Renderer* ren);
    ~Snake();
    void grow(int x, int y);
    void movement();
    SDL_Texture* setTexture(const char* file);
    void setDir(int dir);
    void collider();
    void render();
    bool isAlive() { return alive; }
    void eat();
    bool checkFruitSpawn();
    void spawnFruit();
    int score;

    enum { UP, DOWN, RIGHT, LEFT };

private:
    std::vector<Segment*> body;
    int direction;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Texture* tailTexture;
    SDL_Renderer* renderer;
    SDL_Texture* foodTexture;
    bool alive;
    Segment* fruit;
};


#endif // SNAKE_HPP_INCLUDED
