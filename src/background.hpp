#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "vector2d.hpp"
#include "gameobject.hpp"

class BackGround : public GameObject
{
    public:
    double angle = 0;
    int scaleSpeed = 0;
    bool isScrolling = false;
    int scrollDirection = 1;
    int scrollSpeed = 0;
    bool autoScroll = false;
    

   
    SDL_Rect scrollPositionRect = {0,0,640,480};
    

    std::string tag = "background";

    BackGround();
    BackGround(SDL_Renderer* _renderer, SDL_Texture* _texture, bool autoScroll);
    void onCollision(GameObject* _collider);
    void update();
    void render();
    void scrollBackground(int _direction, int _speed);
    void setScrollDirection(int _direction);
    void setScrollSpeed(int _speed);
    void setSize(int h, int w);
    void setPosition(int x, int y);

};