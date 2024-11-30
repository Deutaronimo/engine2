#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "assetmanager.hpp"


namespace fs = std::filesystem;

// Manages the loading and playing of all assets.
AssetManager::AssetManager(SDL_Renderer* _renderer)
{
    // Load Sound Assets from disk.
    renderer = _renderer;

    Mix_Chunk* testSound    = NULL;
    Mix_Music* testMusic    = NULL;
    Mix_Music* currentMusic = NULL;
    
    // Volume settings.
    soundVolume  = 128;
    musicVolume  = 64;
    masterVolume = 128;
    
    // Configue sound card
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    init();
}

// Loads all graphics and sounds from disk and free surfaces.
void AssetManager::init()
{
    // Load all .png from the graphics folder and put in a textureMap.
    std::cout << "Loading all textures from: " << graphicsPath << std::endl;
    try 
    { 
        int key = 0;
        for (const auto& entry : fs::directory_iterator(graphicsPath))
        { 
            
            if (entry.path().extension() == ".png")
            { 
                std::cout << "Texture loaded: " << key << " : " << entry.path().string() << std::endl;
                SDL_Surface* surface = IMG_Load(entry.path().string().c_str());

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
                textureMap[key++] = texture;
            } 
        } 
    }

    catch (const fs::filesystem_error& err) 
    { 
        std::cerr << "Filesystem error: " << err.what() << std::endl; 
    }

    // load all audio.
    
    testSound = Mix_LoadWAV("audio/testSound.wav");
    testMusic = Mix_LoadMUS("audio/testMusic.mp3");

}

// Play a loaded sound.
void AssetManager::playSound(int soundID)
{
    Mix_PlayChannel(-1, testSound, 0);
}

// Play a loaded music file.
void AssetManager::playMusic(int musicID)
{
    Mix_PlayMusic(testMusic, -1);
    Mix_VolumeMusic(musicVolume);
}

// Stop ALL audio that is playing.
void AssetManager::stopAllSounds()
{

}

// Stop Music that is playing.
void AssetManager::stopMusic()
{

}

// Pause currently playing music.
void AssetManager::pauseMusic()
{
    Mix_PauseMusic();
}

// Unpause any paused music.
void AssetManager::unpauseMusic()
{
    Mix_ResumeMusic();
}

// Set global volume level.
void AssetManager::setSoundVolume(int _volume)
{
    Mix_MasterVolume(masterVolume);
}

// Ser music volume
void AssetManager::setMusicVolume(int _volume)
{
    Mix_VolumeMusic(_volume);
}

// Returns the requested texture pointer.
SDL_Texture* AssetManager::getTexture(int textureID)
{
    // return loadedTexture
    if (textureID >= textureMap.size())
    {

        std::cout << "Invalid textureID request, using default texture.\n";
        return textureMap[0];
    }

    else
    {
        return textureMap[textureID];
    }
    
}

// Cleans up pointers and frees memory to close program. 
void AssetManager::cleanUp()
{
    std::cout << "Quitting, Freeing up loaded assets...\n"; 
    Mix_FreeChunk(testSound);

    // Destroy all loaded texture.
    for (auto& [key, texture] : textureMap) 
    { 
        SDL_DestroyTexture(texture); 
        std::cout << "+";
    }
    std::cout << "\n";

}


