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

   // game->MesaEnumeracion2();


    //Lizzie -  Video introducctivo
    //game->init("GameWindow", 800, 600, false); 
    
    //Mirian
    //game->pantallaCartas();
    //game->juegoArte();

    //Steve
   // game->minjuegoHistoria();

    //Lizzie
   // game->miniJuegopolitica();
    //game->miniJuegoCiencia();
    
    //eleccion bandos  && mapa- Lizzie
    //game->bandosCoinFlip();
    //game->Map(5);

    //combates
    //Steve - combate por el sujeto
    //game->combateSujeto();

    //Mirian - combate por la verdad y comabte trnacendental 
    //game->CombateporlaVerdad(2);
   //game->CombateTrancendental(5);
    
    //Lizzie - musica de ganadores de combates
    
    //Edificio - Mirian, Lizzie , Steve
    game->EdificioUni(0);
    //game->Logros();
    //Primero hablo sobre lo de animacion y movimento y edificio

    //pasamos a la sala de aula donde Lizzie explica el juego de escape room
    //luego pasamos a el laboratorio donde se empezaria con el orden:
    //juego Evidencia - Lizzie
    //juego Enumeracion  -  Steve
    //juego Analisis - Lizzie
    //juego Sintesis - Mirian
    //sala de trono -  Mirian
    //Logros y objetos Mirian Lizzie

    //Game over - Lizzie

    //orden de ecplicacion de pantallas 

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




