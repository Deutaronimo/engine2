#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gameobject.hpp"

class Wall : public GameObject
{
  
    public:
    bool isRenderable = false;

    Wall();
    Wall(SDL_Renderer* _renderer,int x, int y, int h, int w, SDL_Texture* _texture);
    void update();
    void onCollision(GameObject* collider);
    void setSize(int h, int w);
    void setPosition(int x, int y);
    void setRenderable(bool _renderable);
    void render();
};
