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
    Snake(int startx, int starty, char dir, SDL_Renderer* ren);
    ~Snake();
    void addSegment(int x, int y);
    void move();
    SDL_Texture* loadTexture(const char* filename);
    void setDirection(char dir);
    void checkCollision();
    void render();
    bool isAlive() { return alive; }
    void checkAndEatFood();

    SDL_Texture* gameOverTexture;

    static const char NORTH = 0;
    static const char SOUTH = 1;
    static const char EAST = 2;
    static const char WEST = 3;

private:
    std::vector<Segment*> body;
    char direction;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Renderer* renderer;
    SDL_Texture* foodTexture;
    bool alive;
    Segment* food;
};


#endif // SNAKE_HPP_INCLUDED
