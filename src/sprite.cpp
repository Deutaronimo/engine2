#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include "sprite.hpp"
#include "gameobject.hpp"

Sprite::Sprite(SDL_Renderer* _renderer, SDL_Texture* _texture)
{
    renderer = _renderer;
    texture = _texture;
    rect.x = 16;
    rect.y = 16;
    rect.h = 16;
    rect.w = 16;
    
}

// Run every tick.
void Sprite::update()
{
    previousRect = rect;
    rect.x = rect.x + (int)subSpeed;
    render(); // erase if you do seperate render loop.
}

// Run on collision, recives collider data.
void Sprite::onCollision(GameObject* collider)
{
    std::cout << tag << " collided with object TAG: " << collider->tag << std::endl;
    
}

void Sprite::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

// Run before destruction.
void Sprite::destroyed()
{
    isDestroyed = true;
}

void Sprite::render()
{
    if(!isRenderable)
    {
        return;
    }

    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Sprite::setSize(int h, int w)
{
    rect.h = h;
    rect.w = w;
}

void Sprite::setCollidable(bool _collidable)
{
    isCollidable = _collidable;
}

void Sprite::setRenderable(bool _renderable)
{
    isRenderable = _renderable;
}

void Sprite::setRect(SDL_Rect _rect)
{
    rect = _rect;
}

void Sprite::setRect(int x, int y, int w, int h)
{
    rect = {x,y,w,h};
    

}