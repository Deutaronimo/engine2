#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class GameObject
{
    public:

    double angle = 0;
    bool isCollidable = true;
    bool isRenderable = true;
    bool debugRender  = false;;
    bool isStatic     = false;
    bool isDestroyed  = false;
    std::string tag   = "none";
    
    int speed;
    int type;
    int direction;
    int moveDistance;
    int animationFrame;
    int tileSize;

    SDL_Rect     rect;
    SDL_Rect     previousRect;
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;  
    SDL_Renderer* renderer = NULL; 

    GameObject();
    GameObject(SDL_Renderer* _renderer);
    virtual void update();
    virtual void onCollision(GameObject* collider);
    void setPosition(int x, int y);
    void setSize(int h, int w);
    SDL_Rect getCenter();
    std::string getTag();
    void setTag(std::string _tag);
    virtual void render();

};
