#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include "gameobject.hpp"

// Sprite (SDL_Renderer* renderer , SDL_Texture* texture).
class Sprite : public GameObject
{
    public:
    float subSpeed = .3;

    SDL_Renderer* renderer = NULL;
    Sprite(SDL_Renderer* _renderer, SDL_Texture* _texture);
    void update();
    void onCollision(GameObject* collider);
    void setPosition(int x, int y);
    void destroyed();
    void render();
    void setSize(int h, int w);
    void setRenderable(bool renderable);
    void setCollidable(bool collidable);
    void setRect(SDL_Rect _rect);
    void setRect(int x, int y, int w, int h);

};