#include "Game.h"

#include <iostream>
#include<SDL2/SDL.h>

#include "../ECS/Components/TransformComponent/RigidBodyComponent.h"
#include "../ECS/Components/TransformComponent/TransformComponent.h"
#include "../Logging/Logger.h"


Main::Game::Game()
{
    _isRunning = false;
    //  registry = new Registry();
    registry = std::make_unique<Registry>();
    Logging::Logger::Log("game constructor");
}

Main::Game::~Game()
{
    //std::cout << "Game Distructor" << std::endl;
    Logging::Logger::Log("game destructor");
}


void Main::Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error Init Sdl." << std::endl;
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    WindowWidth = displayMode.w;
    WindowHeight = displayMode.h;


    _window = SDL_CreateWindow("Dreams Tech",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WindowWidth, WindowHeight,
                               SDL_WINDOW_BORDERLESS);

    if (!_window)
    {
        //std::cerr << "error making the window" << std::endl;
        Logging::Logger::Log("make  the window");
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!_renderer)
    {
        //   std::cerr << "err create renderer";
        Logging::Logger::Log("error make renderer");
        return;
    }

    SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);

    _isRunning = true;
}


void Main::Game::Run()
{
    while (_isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Main::Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                _isRunning = false;
            }
            break;
        }
    }
}


void Main::Game::Setup()
{
    Entity tank = registry->CreateEntity();
    Entity truck = registry->CreateEntity();

    registry->AddComponent<TransformComponent>(tank, glm::vec2(10, 30), glm::vec2(1, 1), 0);
    registry->AddComponent<RigidBodyComponent>(tank, glm::vec2(50, 0));
}

void Main::Game::Update()
{
    int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - _milliscondsPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - _milliscondsPreviousFrame) / 100;


    _milliscondsPreviousFrame = SDL_GetTicks();
}

void Main::Game::Render()
{
    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void Main::Game::Destroy()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    //std::cout << "sdl destroyed" << std::endl;
    Logging::Logger::Err("Destroyed Game Main");
    // delete registry;
}
