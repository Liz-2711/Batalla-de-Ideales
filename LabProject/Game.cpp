#include "Game.h"
#include"SDL_image.h"
#include <stdlib.h>
#include <stdio.h>


SDL_Texture* playText;
SDL_Rect scrR, destR;
SDL_Rect    rcSprite;
SDL_Rect    gdSprite;

int gameover = 0;
Game::Game()
{}

Game::~Game()
{}

const int SPRITE_SIZE = 256;

void Game::init(const char* title, int WIDTH, int HEIGHT, bool fullscreen)
{




    
        SDL_Init(SDL_INIT_EVERYTHING);
        
        SDL_Surface* windowSurface = NULL;
        SDL_Surface* temp = NULL;
        SDL_Surface* sprite = NULL;
        SDL_Surface* imageSurface = NULL;
        SDL_Surface* SDL_DisplayFormat(SDL_Surface * surface);
        SDL_Rect    rcSprite;
        SDL_Rect    gdSprite;
        SDL_Event windowEvent;
        SDL_Event   event;
        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture;
        SDL_Texture* spriteTexture;

        const Uint8* keystate;
        int colorkey;
        int count;
        int xPosition = 0;
        int yPosition = 0;
        int gameover = 0;


        SDL_Window* window = SDL_CreateWindow("Intro", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        windowSurface = SDL_GetWindowSurface(window);


  


        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        


      
     
        sprite = IMG_Load("IntroBK2.png");
        //imageSurface = IMG_Load("BttSkip.png");

      
        int SPRITE_SIZE = 1;

       
        spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite);
        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

        
       
        SDL_FreeSurface(sprite);
       
       SDL_FreeSurface(imageSurface);
      

        //rcSprite used as source rectangle, gdSprite as destination rectangle. Initialize them to the same position
       
        
        
        rcSprite.x = 0;
        rcSprite.y = 0;
        rcSprite.w = 800;
        rcSprite.h = 600;

        gdSprite.x = xPosition;
        gdSprite.y = yPosition;
        gdSprite.w = 800;
        gdSprite.h = 800;


       


//*****************************************************************************************************************************************************************************
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8* wavBuffer;

        SDL_LoadWAV("musicaIntro1.wav", &wavSpec, &wavBuffer, &wavLength);

        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

        int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
        SDL_PauseAudioDevice(deviceId, 0);
        
        
       // SDL_Surface* ecran = NULL, * imageSurface = NULL, * sapin = NULL;
        int continuer = 1;
       // SDL_Event event;
        SDL_Rect positionFond, positionSapin;

        positionSapin.x = 0;
        positionSapin.y = 0;
        positionFond.x = 0;
        positionFond.y = 0;

        // keep application running long enough to hear the sound

        SDL_Delay(3000);
       //************************************************************************************************************************************************

        while (!gameover)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    gameover = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        gameover = 1;
                        break;

                    }
                    break;


                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        positionFond.x = event.button.x;

                        positionFond.y = event.button.y;
                        if (event.button.x > 150 && event.button.x < 320 && event.button.y > 340 && event.button.y < 415)
                        {
                            continuer = 0;
                        }
                        else if (event.button.x > 150 && event.button.x < 320 && event.button.y > 105 && event.button.y < 180)
                        {
                            continuer = 0;
                            SDL_Quit();

                            int status = system("./cs");


/*****************************************STEVVEEEEEEEEEE*************************************************************************************************************************************************************************/
                            
                            menuPrincipal();

 /******************************************************************************************************************************************************************************************************************/

                        }

                    }

                    break;
                }
            }

            keystate = SDL_GetKeyboardState(NULL);

            // When key pressed, update the destination rectangle

            if (keystate[SDL_SCANCODE_UP]) {
               // gdSprite.y -= 1;              
                rcSprite.y += 1;
            }
            if (keystate[SDL_SCANCODE_DOWN]) {
             //   gdSprite.y += 1;
                rcSprite.y -= 1;
            }
            if (gdSprite.x < 0) {
                gdSprite.x = 0;
            }
          
            //***********************************************************************************************************************************************/
           

           
            
            
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &gdSprite);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderCopy(renderer, spriteTexture, &rcSprite, &gdSprite);
            SDL_RenderPresent(renderer);


           


        }
      

        // clean up

        SDL_CloseAudioDevice(deviceId);
        SDL_FreeWAV(wavBuffer);
       // SDL_DestroyTexture(spriteTexture2);
       // SDL_DestroyTexture(texture2);
        SDL_DestroyTexture(spriteTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        //SDL_DestroyRenderer(renderer2);
        SDL_DestroyWindow(window);




        SDL_Quit();
        
    
    }

   //Funciones STEVE
   // Funcion para correr constantemente las funciones del menu principal
    void Game::menuPrincipal() {
        ventanaMenuPrincipal("Menu Principal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, false);
        elementosMenuPrincipal();
        while (true)
            eventosMenuPrincipal();
   }

    //crear ventana de menu principal
    void Game::ventanaMenuPrincipal(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
        int flags = 0;

        if (fullscreen)
            flags = SDL_WINDOW_FULLSCREEN;

        if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
            window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
            isRunning = true;
        }
        else
            isRunning = false;

    }

    //funcion de eventos para el menu principal
    void Game::eventosMenuPrincipal() {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {

            //cerrar la ventana
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            int cursorx = event.motion.x, cursory = event.motion.y;

            //detectar si esta en boton 1
            if (cursorx > 385 && cursorx < 630 && cursory > 80 && cursory < 130) {
                std::cout << "Tocaste el boton de NUEVO JUEGO\n";
                SDL_Quit();
                pantallaCartas();
            }
            //detectar si esta en boton 2
            if (cursorx > 385 && cursorx < 630 && cursory > 190 && cursory < 240) {
                std::cout << "Tocaste el boton de CONTROLES.\n";
            }
            //detectar si esta en boton 3
            if (cursorx > 385 && cursorx < 630 && cursory > 300 && cursory < 350) {
                std::cout << "Tocaste el boton de CREDITOS.\n";
            }
            //detectar si esta en boton 4
            if (cursorx > 385 && cursorx < 630 && cursory > 410 && cursory < 460) {
                std::cout << "Tocaste el boton de SALIR.\n";
                SDL_Quit();
            }
            break;
        }
    }

    //elementos de menu principal (botones)
    void Game::elementosMenuPrincipal() {
        //fondo
        superficieVentana = SDL_GetWindowSurface(window);

        background = IMG_Load("assets/backgroundmenu2.png");
        SDL_BlitSurface(background, NULL, superficieVentana, NULL);

        //boton1
        posInicial.x = 0; posInicial.y = 0; posInicial.w = 360; posInicial.h = 120;
        posFinal.x = 330; posFinal.y = 50; posFinal.w = 360; posFinal.h = 120;
        boton1 = IMG_Load("assets/botonjugar2.png");
        SDL_BlitSurface(boton1, &posInicial, superficieVentana, &posFinal);

        //boton2
        posInicial.x = 0; posInicial.y = 0; posInicial.w = 360; posInicial.h = 120;
        posFinal.x = 330; posFinal.y = 160; posFinal.w = 360; posFinal.h = 120;
        boton2 = IMG_Load("assets/botoncontroles2.png");
        SDL_BlitSurface(boton2, &posInicial, superficieVentana, &posFinal);

        //boton3
        posInicial.x = 0; posInicial.y = 0; posInicial.w = 360; posInicial.h = 120;
        posFinal.x = 330; posFinal.y = 270; posFinal.w = 360; posFinal.h = 120;
        boton3 = IMG_Load("assets/botoncreditos2.png");
        SDL_BlitSurface(boton3, &posInicial, superficieVentana, &posFinal);

        //boton4
        posInicial.x = 0; posInicial.y = 0; posInicial.w = 360; posInicial.h = 120;
        posFinal.x = 330; posFinal.y = 380; posFinal.w = 360; posFinal.h = 120;
        boton4 = IMG_Load("assets/botonsalir2.png");
        SDL_BlitSurface(boton4, &posInicial, superficieVentana, &posFinal);

        SDL_UpdateWindowSurface(window);
    }


void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}



void Game::update()
{
	destR.y = 500;
	cnt--;
	destR.h = 600;
	destR.w = 800;
	//destR.x = 40;


	//moving 
	
	//destR.y = cnt;


	std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playText,NULL,&destR);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_CloseAudio();
    

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}





//****************************************************Pantalla Cartas*********************************************


void Game::pantallaCartas() 
{
    const int WIDTH = 800; //Ancho de pantalla
    const int HEIGHT = 600; // altura de pantallla
    const int SPRITE_SIZE = 120; //tamaño de cartas
    const int SizeMessaje = 600; // tamaño de mensaje de carta eleguida

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
   

    //Imagenes
    SDL_Surface* Fondo;
   
    SDL_Surface* superficieVentana;

    SDL_Surface* Carta1; //Arte
   
    SDL_Surface* Carta2; //Historia
   
    SDL_Surface* Carta3; //Politica
  
    SDL_Surface* Carta4; // ciencia
    
    SDL_Surface* Continuar; // imagen de tecla espace y tecla escape



    //enveno para salir
    SDL_Event EventoSalir;

    
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    //evento para el toque de la carta
    SDL_Event eleccion;

    Ventana = SDL_CreateWindow("Pantalla Cartas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);


    if (Ventana == NULL)
    {
        std::cout << ("error en ventana %s\n", SDL_GetError());
    }
    else
    {

        Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
        SDL_FillRect(superficieVentana, NULL, Color);

        rcInicial.x = 0; rcInicial.y = 0; rcInicial.w = SPRITE_SIZE; rcInicial.h = SPRITE_SIZE;

        rcMI.x = 0; rcMI.y = 0; rcMI.w = SizeMessaje; rcMI.h = SizeMessaje;

        gdPosCartas.x = 120; gdPosCartas.y = 350; gdPosCartas.w = SPRITE_SIZE; gdPosCartas.h = SPRITE_SIZE;

        //Posicion de mensaje ganador;
        gdMensaje.x = 182; gdMensaje.y = 40; gdMensaje.w = 500; gdMensaje.h = 500;


        srand(time(NULL));
        
        

        Fondo = IMG_Load("Imagenes/MesaFacherita1.png");
        SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

        Carta1 = IMG_Load("Imagenes/Carta1.png");
        SDL_BlitSurface(Carta1, &rcInicial, superficieVentana, &gdPosCartas);

        gdPosCartas.x = 270;
        Carta2 = IMG_Load("Imagenes/Carta1.png");
        SDL_BlitSurface(Carta2, &rcInicial, superficieVentana, &gdPosCartas);
        gdPosCartas.x = 420;
        Carta3 = IMG_Load("Imagenes/Carta1.png");
        SDL_BlitSurface(Carta3, &rcInicial, superficieVentana, &gdPosCartas);
        gdPosCartas.x = 570;
        Carta4 = IMG_Load("Imagenes/Carta1.png");
        SDL_BlitSurface(Carta4, &rcInicial, superficieVentana, &gdPosCartas);

        gdPosCartas.x = 120;
        Continuar = IMG_Load("Imagenes/Continuar.png");


        ////Liberemaos las imagenes
        SDL_FreeSurface(Fondo);
        SDL_FreeSurface(Carta1);
        SDL_FreeSurface(Carta2);
        SDL_FreeSurface(Carta3);
        SDL_FreeSurface(Carta4);


        SDL_UpdateWindowSurface(Ventana);

        int i = 0;
        while (!i) {
            if (SDL_PollEvent(&eleccion))
            {
                int posicionClick = 0;
                switch (eleccion.type)
                {
                case SDL_QUIT:
                    i = 1;
                    break;
               
                case SDL_MOUSEBUTTONDOWN:


                    if (eleccion.button.button == SDL_BUTTON_LEFT)
                    {
                        int posx = eleccion.motion.x;
                        int posy = eleccion.motion.y;
                       
                      
                        gdPosCartas.x = 120; gdPosCartas.y = 350; gdPosCartas.w = SPRITE_SIZE; gdPosCartas.h = SPRITE_SIZE;
                        if (posx > gdPosCartas.x && posx < gdPosCartas.x + gdPosCartas.w && posy >gdPosCartas.y && posy < gdPosCartas.y + gdPosCartas.h)
                        {

                            numeroAdivinar = 1 + rand() % 4;
                            if (numeroAdivinar == 1)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeA.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 2)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeH.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 3)
                            {
                                Carta1 = IMG_Load("Imagenes/MensajeP.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 4)
                            {
                                Carta1 = IMG_Load("Imagenes/MensajeC.png");
                                i = 1;
                            }
                            SDL_BlitSurface(Carta1, &rcMI, superficieVentana, &gdMensaje);
                            gdMensaje.x = 130; gdMensaje.y = 530; gdMensaje.w = 513; gdMensaje.h = 87;
                            SDL_BlitSurface(Continuar, &rcMI, superficieVentana, &gdMensaje);
                            SDL_UpdateWindowSurface(Ventana);

                        }
                        gdPosCartas.x = 270;
                        if (posx > gdPosCartas.x && posx < gdPosCartas.x + gdPosCartas.w && posy >gdPosCartas.y && posy < gdPosCartas.y + gdPosCartas.h)
                        {
                            numeroAdivinar = 1 + rand() % 4;
                            if (numeroAdivinar == 1)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeA.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 2)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeH.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 3)
                            {
                                Carta1 = IMG_Load("Imagenes/MensajeP.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 4)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeC.png");
                                i = 1;
                            }
                            SDL_BlitSurface(Carta1, &rcMI, superficieVentana, &gdMensaje);
                            gdMensaje.x = 130; gdMensaje.y = 530; gdMensaje.w = 513; gdMensaje.h = 87;
                            SDL_BlitSurface(Continuar, &rcMI, superficieVentana, &gdMensaje);
                            SDL_UpdateWindowSurface(Ventana);

                        }
                        gdPosCartas.x = 420;
                        if (posx > gdPosCartas.x && posx < gdPosCartas.x + gdPosCartas.w && posy >gdPosCartas.y && posy < gdPosCartas.y + gdPosCartas.h)
                        {
                            numeroAdivinar = 1 + rand() % 4;
                            if (numeroAdivinar == 1)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeA.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 2)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeH.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 3)
                            {
                                Carta1 = IMG_Load("Imagenes/MensajeP.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 4)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeC.png");
                                i = 1;
                            }

                            SDL_BlitSurface(Carta1, &rcMI, superficieVentana, &gdMensaje);
                            gdMensaje.x = 130; gdMensaje.y = 530; gdMensaje.w = 513; gdMensaje.h = 87;
                            SDL_BlitSurface(Continuar, &rcMI, superficieVentana, &gdMensaje);
                            SDL_UpdateWindowSurface(Ventana);

                        }
                        gdPosCartas.x = 570;
                        if (posx > gdPosCartas.x && posx < gdPosCartas.x + gdPosCartas.w && posy >gdPosCartas.y && posy < gdPosCartas.y + gdPosCartas.h)
                        {
                            numeroAdivinar = 1 + rand() % 4;
                            if (numeroAdivinar == 1)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeA.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 2)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeH.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 3)
                            {
                                Carta1 = IMG_Load("Imagenes/MensajeP.png");
                                i = 1;
                            }
                            if (numeroAdivinar == 4)
                            {

                                Carta1 = IMG_Load("Imagenes/MensajeC.png");
                                i = 1;
                            }
                            SDL_BlitSurface(Carta1, &rcMI, superficieVentana, &gdMensaje);
                            gdMensaje.x = 130; gdMensaje.y = 530; gdMensaje.w = 513; gdMensaje.h = 87;
                            SDL_BlitSurface(Continuar, &rcMI, superficieVentana, &gdMensaje);
                            SDL_UpdateWindowSurface(Ventana);

                        }
                    }
                    break;

                default:
                    break;
                }
            }
        }


    }

    while (!salir)
    {
        if (SDL_PollEvent(&EventoSalir))
        {
            switch (EventoSalir.type)
            {
            case SDL_QUIT:
                salir = 1;
                break;

            case SDL_KEYDOWN:
                switch (EventoSalir.key.keysym.sym)
                {
                case SDLK_SPACE:
                    if (numeroAdivinar == 1)
                    {
                        std::cout << "Carta ARTE";
                        superficieVentana = SDL_GetWindowSurface(Ventana);
                        SDL_UpdateWindowSurface(Ventana);
                    }
                    else if (numeroAdivinar == 2)
                    {
                        std::cout << "Carta Historia";
                        superficieVentana = SDL_GetWindowSurface(Ventana);
                        SDL_UpdateWindowSurface(Ventana);
                    }
                    else if (numeroAdivinar == 3)
                    {
                        std::cout << "Carta POLITICA";
                        
                        superficieVentana = SDL_GetWindowSurface(Ventana);
                        SDL_UpdateWindowSurface(Ventana);
                    }
                    else if (numeroAdivinar == 4)
                    {
                        std::cout << "Carta CIENCIA";
                        superficieVentana = SDL_GetWindowSurface(Ventana);
                        SDL_UpdateWindowSurface(Ventana);
                    }
                    

                    break;
                case SDLK_ESCAPE:
                    
                    SDL_Quit();
                    menuPrincipal();
                    break;

                }
                break;
            }
        }
    }

    SDL_DestroyWindow(Ventana);

    SDL_Quit();
    
}