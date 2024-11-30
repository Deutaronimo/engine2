#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <time.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "src/gameobject.hpp"
#include "src/wall.hpp"
#include "src/background.hpp"
#include "src/assetmanager.hpp"
#include "src/settings.hpp"
#include "src/sprite.hpp"

using namespace std;

Uint32 FRAMETIMESTART;

vector<GameObject*> GameObjectBatch;
vector<GameObject*> splashScreenBatch;

std::string currentScene = "main";
std::string folderPath   = "/graphics";

std::map<string,SDL_Texture*> textureMap;

SDL_Event event;


void coreUpdate(const vector<GameObject*>& _gameObjectBatch, SDL_Renderer* renderer)
{
        FRAMETIMESTART = SDL_GetTicks();

        // Clear the screen and set the background color.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Update all entities in the batch.
        for (auto x = 0; x < GameObjectBatch.size(); x++)
        {
            GameObjectBatch.at(x)->update();
        }


        // Check everything for collisions and inform each object.
        for (size_t i = 0; i < GameObjectBatch.size(); ++i) 
        { 
            for (size_t j = i + 1; j < GameObjectBatch.size(); ++j) 
            { 
                // A very simple "FOR NOW" collision check.
                if (SDL_HasIntersection(&GameObjectBatch[i]->rect, &GameObjectBatch[j]->rect) && !&GameObjectBatch[i]->isCollidable)
                { 
                    // Send each object a copy of what it collided with.
                    GameObjectBatch[i]->onCollision(GameObjectBatch[j]); 
                    GameObjectBatch[j]->onCollision(GameObjectBatch[i]);            
                } 
            }        

        }


        // Delete everything in batch marked isDestroyed.
        for (auto it = GameObjectBatch.begin(); it != GameObjectBatch.end();) 
        {
            if ((*it)->isDestroyed) 
            {
                //delete *it;                     // Free the memory
                it = GameObjectBatch.erase(it); // Erase the element and get the new iterator
            } 
        
            else 
            {
                ++it;
            }
        }
        

        // present our renderer to the screen.
        SDL_RenderPresent(renderer);

        // FPS Check and maintainer.
        if (1000 / 60 > SDL_GetTicks() - FRAMETIMESTART)
        {
            SDL_Delay(1000 / 60 - (SDL_GetTicks() - FRAMETIMESTART));
        }

}


int main(int argc, char** args)
{
    Settings settings;
    srand(time(NULL));
    const char windowTitle[] = "Tech Demo";

    // Settings for FPS and constants.
    bool quit = false;
    int imgFlags = IMG_INIT_PNG;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL Init Error: "<< SDL_GetError()<<endl;
    }
    
    if (IMG_Init(IMG_INIT_PNG) != 0)
    {
        //cout << "err code. "<< IMG_GetError() << endl;;
    };
    
    if (SDL_Init(SDL_INIT_AUDIO) != 0);
    {
        //cout << "rr code "<< SDL_GetError() << endl;
    } 

    // Create a Window and Renderer.
    SDL_Window* window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, settings.WINDOW_SIZE_X, settings.WINDOW_SIZE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Enable for texture filtering.
    //SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "2");


    // Scale the origional screen resolution up by x4.
    SDL_RenderSetScale(renderer,settings.SCREEN_SCALE,settings.SCREEN_SCALE);

    // Create the asset manager
    AssetManager assetManager(renderer);

    //Play test music and a sound.
    //assetManager.playMusic(1);


    BackGround backGroundLong(renderer, assetManager.getTexture(4), true);
    backGroundLong.setSize(480, 2560);
    backGroundLong.setPosition(0,0);

    Sprite logo(renderer, assetManager.getTexture(1));
    logo.setPosition(128,32);
    logo.setCollidable(false);
    logo.setSize(400,400);

    Sprite wallLeft(renderer, assetManager.getTexture(3));
    wallLeft.setRect(0,0,16,480);
    wallLeft.setRenderable(true);

    Sprite wallRight(renderer, assetManager.getTexture(3));
    wallRight.setRect(624,0,16,480);
    wallRight.setRenderable(true);

    Sprite wallTop(renderer, assetManager.getTexture(3));
    wallTop.setRect(16,0,608,16);
    wallTop.setRenderable(true);

    Sprite wallBottom(renderer, assetManager.getTexture(3));
    wallBottom.setRect(16,464,608,16);
    wallBottom.setRenderable(true);

    
    // Add assets to the render batcher
    GameObjectBatch.push_back(&backGroundLong);
    GameObjectBatch.push_back(&logo);
    GameObjectBatch.push_back(&wallLeft);
    GameObjectBatch.push_back(&wallRight);
    GameObjectBatch.push_back(&wallTop);
    GameObjectBatch.push_back(&wallBottom);

    // Main game loop.
    while (!quit)
    {
        
 	    while (SDL_PollEvent(&event))
	    { 
		    if (event.type == SDL_QUIT)
		    { 
			    quit = true; 
		    } 
		
		    if (event.type == SDL_KEYDOWN) 
		    { 
			    if (event.key.keysym.sym == SDLK_ESCAPE) 
			    { 
				    quit = true; 
			    } 
		    } 
	    }

         if (currentScene == "splashscreen")
        {
            coreUpdate(splashScreenBatch, renderer);
            
            
        }    

        if (currentScene == "main")
        {
            coreUpdate(GameObjectBatch, renderer);
        }
    }

    assetManager.cleanUp();

    return 0;
}