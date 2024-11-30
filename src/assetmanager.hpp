#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <map>

class AssetManager
{
    public:
    int soundVolume;
    int musicVolume;
    int masterVolume;

    // Holds all the loaded texture.
    std::map<int,SDL_Texture*> textureMap;

    // Paths to media.
    std::string graphicsPath = "graphics/";
    std::string audioPath    = "audio/";

    SDL_Renderer* renderer;

    // Sound.
    Mix_Chunk* testSound;
    Mix_Music* currentMusic;
    Mix_Music* testMusic;


    bool isMuted  = false;
    bool isPaused = false;

    AssetManager(SDL_Renderer* _renderer);
    void init();  
    void playSound(int soundID);
    void playMusic(int musicID);
    void stopAllSounds();
    void stopMusic();
    void pauseMusic();
    void unpauseMusic();
    void setSoundVolume(int _volume);
    void setMusicVolume(int _volume);
    void cleanUp();
    SDL_Texture* getTexture(int textureID);
    

};