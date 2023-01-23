#include <SDL2/SDL.h>
#undef main

#include<iostream>


#include "Main/Game.h"


 void main()
{
    Game game ;  
    game.Initialize();
    game.Run();
    game.Destroy();

   // return 0;
}
