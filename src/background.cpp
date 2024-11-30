#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "gameobject.hpp"
#include "background.hpp"

BackGround::BackGround()
{

}

BackGround::BackGround(SDL_Renderer* _renderer, SDL_Texture* _texture, bool _autoScroll)
{
    renderer = _renderer;
    texture = _texture;
    angle = 0;
    tag = "background";
    autoScroll = _autoScroll;
    scrollPositionRect = {0,0,640,480};// hard coded change this
    scrollSpeed = 1;
    rect.x = 0;
    rect.y = 0;
    rect.h = 480;
    rect.w = 640;
}

void BackGround::update()
{
    scrollPositionRect.x += scrollSpeed;
    scrollPositionRect.h = 960;
    scrollPositionRect.w = 1280;

    if (scrollPositionRect.x - rect.x >= scrollPositionRect.w)
    {
        scrollPositionRect.x = 0;
    }
    

    render(); //for now
}

void BackGround::onCollision(GameObject* collider)
{

}

void BackGround::render()
{
    //
    SDL_RenderCopy(renderer, texture, &scrollPositionRect, &rect);

}

// ScrollBackground(int direction, int speed)  1 for right, 2 for left.
void BackGround::scrollBackground(int _direction, int speed)
{


}

void BackGround::setScrollDirection(int _direction)
{
    scrollDirection = _direction;
}

void BackGround::setScrollSpeed(int _speed)
{
    scrollSpeed = _speed;
}

void BackGround::setSize(int h, int w)
{
    rect.h = h;
    rect.w = w;
}

void BackGround::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}
