#include<iostream>
// #define SDL_MAIN_HANDLED
// #include <SDL2/SDL.h>
// #include<SDL2/SDL_image.h>
// #include<SDL2/SDL_mixer.h>
// #include<SDL2/SDL_ttf.h>
// #include<glm/glm.hpp>
// #include<imgui.h>
// #include <sol/sol.hpp>


#include "Main/Game.h"


int main()
{
    Main::Game game = Main::Game();
    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
