#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

namespace Main
{
    class Game
    {
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        bool _isRunning;

    public:
        Game();
        ~Game();
        void Initialize();
        void Run();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        int WindowWidth;
        int WindowHeight;
    };
}
