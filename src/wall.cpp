#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gameobject.hpp"
#include "wall.hpp"

Wall::Wall()
{

}

Wall::Wall(SDL_Renderer* _renderer, int x, int y, int h, int w, SDL_Texture* _texture)
{
    isCollidable = true;
    isStatic = true;

    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;

    texture = _texture;
    renderer = _renderer;

    tag = "wall";
    
}

void Wall::update()
{
    
    previousRect = rect;
    render();
}

void Wall::onCollision(GameObject* collider)
{

}

void Wall::setSize(int h, int w)
{
    rect.w = w;
    rect.h = h;

}

void Wall::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
    
}

void Wall::render()
{
    
    if(isRenderable)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    
}

void Wall::setRenderable(bool _renderable)
{
    isRenderable = _renderable;

}
