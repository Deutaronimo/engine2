#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Settings
{
    public:

    

    // Position of the window on the desktop at start
    const int WINDOW_POSITION_X = 0;
    const int WINDOW_POSITION_Y = 0;

    // Upscale factor of games resolution
    const int SCREEN_SCALE = 2;

    // The scaled up resolution of the games screen.
    const int WINDOW_SIZE_X = 1280;
    const int WINDOW_SIZE_Y = 960;

    // The actual game resolution.
    const int GAME_RESOLUTION_X = 640;
    const int GAME_RESOLUTION_Y = 480;

    // Games set frame rate.
    const int FPS = 60;

    // Under here is not implemented yet.
    bool IS_FULLSCREEN = true;
    
    bool muteAudio = false;
    bool useGamepad = true;
    bool useKeyboard = true;
    bool useMouse = true;
    int musicVolume = 128;
    int soundVolume = 128;

    Settings();

};