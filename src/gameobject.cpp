#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameobject.hpp"

GameObject::GameObject()
{

}

GameObject::GameObject(SDL_Renderer* _renderer)
{
    renderer = _renderer;

}

// Objets update, run every tick.
void GameObject::update()
{
    render();
    
}

// Runs on a collision, recieves collider Information. 
void GameObject::onCollision(GameObject* collider)
{

}

// Set the position of a gameObject.
void GameObject::setPosition(int x, int y)
{
    
}

// Set the Height and width of a gameObject.
void GameObject::setSize(int h, int w)
{
 
}

std::string GameObject::getTag()
{
    return tag;
}

void GameObject::setTag(std::string _tag)
{
    tag = _tag;
}

void GameObject::render()
{
    //SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

// Returns the center of a sprite as an SDL_Rect.H and W match objects.
SDL_Rect GameObject::getCenter()
{
    int x = rect.x * .5;
    int y = rect.y * .5;

    SDL_Rect temp = {x , y, rect.w, rect.h};

    return temp;
}
