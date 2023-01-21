#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../ECS/ECS.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

namespace Main
{
    class Game
    {
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        bool _isRunning;
        int _milliscondsPreviousFrame;

        std::unique_ptr<Registry> registry;

    public:
        Game();
        ~Game();
        void Initialize();
        void Setup();
        void Run();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        int WindowWidth;
        int WindowHeight;
    };
}
