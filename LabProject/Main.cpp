#include<SDL.h>
#include <stdlib.h>
#include"SDL_image.h"
#include <SDL_mixer.h>




#include "Game.h"


Game* game = nullptr;


int main(int argc, char* argv[])
{
   

     const int FPS = 60;
    const int frameDelay = 100 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("GameWindow", 800, 600, false);

  

    while (game->running())
    {

        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        //Sin esto no hay delay ******
        if (frameDelay > frameStart) {
            SDL_Delay(frameDelay - frameTime);
        }
    }


    


    game->clean();
    return 0;

}




