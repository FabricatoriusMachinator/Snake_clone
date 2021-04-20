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
    void grow(int x, int y);
    void movement();
    SDL_Texture* loadTexture(const char* filename);
    void setDir(char dir);
    void collider();
    void render();
    bool isAlive() { return alive; }
    void eat();

    static const char NORTH = 0;
    static const char SOUTH = 1;
    static const char EAST = 2;
    static const char WEST = 3;

private:
    std::vector<Segment*> body;
    char direction;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Texture* tailTexture;
    SDL_Renderer* renderer;
    SDL_Texture* foodTexture;
    bool alive;
    Segment* fruit;
};


#endif // SNAKE_HPP_INCLUDED
