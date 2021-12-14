#include<SDL.h>
#include <stdlib.h>
#include"SDL_image.h"

#include "Game.h"


Game* game = nullptr;


int main(int argc, char* argv[])
{
   

     const int FPS = 60;
    const int frameDelay = 100 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    //game->init("GameWindow", 800, 600, false);
    //game->combateSujeto();
    //game->CombateporlaVerdad(5);
    //game->juegoArte();
    //game->bandosCoinFlip();
    //game->CombateTrancendental(5);
    //game->EdificioUni(0);
    //game->MesaEvidencia();
    // game->MesaEnumeracion2();
    //game->MesaSintesis();
    //game->AniMesAna(0);
    //game->mesaEnumeracion();
   // game->mesadeAnalisis();
    //game->EscapeRoom();
    //game->mesaEnumeracion();
   game->GameOver(3);
    //game->miniJuegoCiencia();
    //game->mesadeEvidenciaMinijuego();
    //game->miniJuegopolitica();
    //game->minjuegoHistoria();
    //game->Map();


    //game->mesadeAnalisis();

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




