#include "Game.h"
#include"SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

SDL_Texture* playText;
SDL_Rect scrR, destR;
SDL_Rect    rcSprite;
SDL_Rect    gdSprite;

//controla que elemento va despues
int elementospantalla = 0, preguntaCS = 1, puntos = 0, J1posx = 100, J1posy = 110, J2posx = 820, J2posy = 110, turno = 1,
J1movimiento = 0, J2movimiento = 0, cantCodigo = 0, gameover = 0;
bool eliminado = false, J1RespuestaCorrecta, J2RespuestaCorrecta, opcionSeleccionada = 0; 
std::string codigo = "";

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

       // SDL_Delay(3000);
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
                SDL_Quit();
                CombateporlaVerdad(5);
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
    const int SPRITE_SIZE = 120; //tama�o de cartas
    const int SizeMessaje = 600; // tama�o de mensaje de carta eleguida

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
                        SDL_Quit();
                        juegoArte();
                        //miniJuegoCiencia(); 
                        
                    }
                    else if (numeroAdivinar == 2)
                    {
                        std::cout << "Carta Historia";
                        SDL_Quit();
                        juegoArte();
                        //miniJuegoCiencia();
                       
                    }
                    else if (numeroAdivinar == 3)
                    {
                        std::cout << "Carta POLITICA";
                        
                        SDL_Quit();
                        juegoArte();
                        //miniJuegoCiencia();
                        //juegoPolitica();
                       
                    }
                    else if (numeroAdivinar == 4)
                    {
                        std::cout << "Carta CIENCIA";
                        SDL_Quit();
                        juegoArte();
                        //miniJuegoCiencia();
                        //juegoCiencia();
                        


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


//****************************************************PANTALLA JUEGOS***********************************************
//Arte

void Game::juegoArte()
{
    vidas = 0;
    const int WIDTH = 1000; //Ancho de pantalla
    const int HEIGHT =  564; // altura de pantallla
    const int SPRITE_SIZE = 600; //TAMA;O D ELA ORCA
    const int SizeMessaje = 600; // tama�o de mensaje de carta eleguida

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;


    //Imagenes
    SDL_Surface* Fondo;
    SDL_Surface* superficieVentana;

    SDL_Surface* Orca1;
    
    SDL_Surface* Pregunta1;

    SDL_Surface* Respuesta1;
    SDL_Surface* R1;
    SDL_Surface* Corazones;
    



    //enveno para salir
    SDL_Event EventoSalir;


    int salir = 0;
    //POsiciones de las imagenes
    SDL_Rect    rcInicial;
    SDL_Rect    gdFinal;
  

    //evento para el toque de la carta
    SDL_Event eleccion;

    Ventana = SDL_CreateWindow("Minijuego Arte", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    if (Ventana == NULL) 
    {
        std::cout << "Error";

    }
    else 
    {
        
        rcInicial.x = 0; rcInicial.y = 0; rcInicial.w = SPRITE_SIZE; rcInicial.h = SPRITE_SIZE;

        gdFinal.x = 150; gdFinal.y = 100; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;




        Fondo = IMG_Load("Imagenes/FondoOrca.png");
        SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);


        Orca1 = IMG_Load("Imagenes/Orca1.png");
        SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

        gdFinal.x = 400; gdFinal.y = 80;
        Pregunta1 = IMG_Load("Imagenes/Pregunta1.png");
        SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

        gdFinal.x = 400; gdFinal.y = 200;
        Respuesta1 = IMG_Load("Imagenes/Respuesta0.png");
        SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);
       
        gdFinal.x = 0; gdFinal.y = 0;
        Corazones = Vidas(1);
        
        

       /* gdFinal.x = 768; gdFinal.y = 145;
        R1 = IMG_Load("Imagenes/R1.5.png");
        SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);

        gdFinal.x = 737; gdFinal.y = 145;
        R11 = IMG_Load("Imagenes/R1.4.png");
        SDL_BlitSurface(R11, &rcInicial, superficieVentana, &gdFinal);*/

        SDL_FreeSurface(Fondo);
        SDL_FreeSurface(Orca1);
        SDL_FreeSurface(Pregunta1);
        SDL_FreeSurface(Respuesta1);
        int i = 0;
        //respietsa 2 MIGUEL ANGEL
        int M = 0, I = 0, G = 0, U = 0, E = 0, L = 0, A = 0, N = 0; //intentos 10 // correctas 8 //prgeunta 1
        //respuesta 2  Miguel �ngel Buonarroti.
        int M2 = 0, I2 = 0, G2 = 0, U2 = 0, E2 = 0, L2 = 0, A2 = 0, N2 = 0, B2 = 0, O2 = 0, R2 = 0, T2 = 0;//intentos 14 //correctas 12 //prgeunta 2
        //Respuesta 3 El barroco
        int E3 = 0, L3 = 0, B3 = 0, A3 = 0, R3 = 0, O3 = 0, C3 = 0; //intentos 9 // correctas 7 //prgeunta 3
        //Respuesta 4 Humanismo
        int H4 = 0, U4 = 0, M4 = 0, A4 = 0, N4 = 0, I4 = 0, S4 = 0, O4=0; //intentos 10  //correctas 8 //prgeunta 4
        //Respuetsa 5  tortugas ninjas
        int L5=0,  S5=0, T5 = 0, O5 = 0, R5 = 0,  U5 = 0, G5 = 0, A5 = 0, N5 = 0, I5 = 0, J5 = 0; //intentos 13 //correctas 11 //prgeunta 5


        int intentos1 = 0;

        int preguntas = 1;
        int pregun1 = 0;
        int pregun2 = 0;
        int pregun3 = 0;
        int pregun4 = 0;
        int pregun5 = 0;

        int limite = 10;

        int correctas1 = 0;

        int correcta = 8;

        //int correctaP = 0;


        SDL_UpdateWindowSurface(Ventana);

        while (!i) {
            if (SDL_PollEvent(&eleccion))
            {
                int posicionClick = 0;
                
                if (correctas1 == correcta)
                {
                    
                    Fondo = IMG_Load("Imagenes/C3.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(1000);
                    Fondo = IMG_Load("Imagenes/C2.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(1000);
                    Fondo = IMG_Load("Imagenes/C1.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(800);




                    Fondo = IMG_Load("Imagenes/FondoOrca.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                        if (preguntas == 1) 
                        {
                            pregun1 = 1;
                            gdFinal.x = 150; gdFinal.y = 100;
                            Orca1 = IMG_Load("Imagenes/Orca1.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 400; gdFinal.y = 80;
                            Pregunta1 = IMG_Load("Imagenes/Pregunta2.png");
                            SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 400; gdFinal.y = 200;
                            Respuesta1 = IMG_Load("Imagenes/Respuesta2.png");
                            SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 0; gdFinal.y = 0;
                            Corazones = Vidas(1);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            correcta = 12;
                            intentos1 = 0;
                            correctas1 = 0;
                            limite = 14;
                           
                            preguntas = 2;
                           
                            SDL_FreeSurface(Fondo);
                            
                            SDL_FreeSurface(Orca1);
                            SDL_UpdateWindowSurface(Ventana);
                            
                        }
                        else if (preguntas == 2) 
                        {
                            std::cout << "Correcta";
                            if (pregun1 == 1 )
                            {
                                
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/Orca1.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(2);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);
                                
                                correcta = 7;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 9;
                                preguntas = 3;


                                pregun2 = 1;

                                
                                
                                
                            }
                            else if (pregun1 == 2)
                            {
                                
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca2.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(1);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 7;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 9; 

                                preguntas = 3;

                                pregun2 = 1;
                                
                            }
                            gdFinal.x = 400; gdFinal.y = 80;
                            Pregunta1 = IMG_Load("Imagenes/Pregunta3.png");
                            SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 400; gdFinal.y = 200;
                            Respuesta1 = IMG_Load("Imagenes/Respuesta3.png");
                            SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(Orca1);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (preguntas == 3)
                        {
                            std::cout << "Correcta3";
                            if (pregun1 == 1 && pregun2 == 1)
                            {
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/Orca1.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(3);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 8;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 10;

                                preguntas = 4;

                                pregun3 = 1;

                                
                            }
                            else if (pregun1 == 1 && pregun2 == 2 || pregun1 == 2 && pregun2 == 1)
                            {
                                std::cout << "1:2 2:1";
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca2.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(2);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 8;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 10;
                                pregun3 = 1;

                                preguntas = 4;

                               
                            }
                            else if (pregun1 == 2 && pregun2 == 2)
                            {
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca3.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(1);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 8;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 10;

                                preguntas = 4;
                                pregun3 = 1;
                            }

                            preguntas = 4;
                            gdFinal.x = 400; gdFinal.y = 80;
                            Pregunta1 = IMG_Load("Imagenes/Pregunta4.png");
                            SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 430; gdFinal.y = 200;
                            Respuesta1 = IMG_Load("Imagenes/Respuesta4.png");
                            SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(Orca1);
                            SDL_UpdateWindowSurface(Ventana);

                        }
                        else if (preguntas == 4)
                        {
                            if (pregun1 == 1 && pregun2 == 1 && pregun3 == 1)
                            {
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/Orca1.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(4);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 11;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 13;

                                preguntas = 5;
                                pregun4 = 1;
                            }
                            else if (pregun1 == 1 && pregun2 == 1 && pregun3 == 2  || pregun1 == 2 && pregun2 == 1 && pregun3 == 1 || pregun1 == 1 && pregun2 == 2 && pregun3 == 1)
                            {
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca2.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(3);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);
                               
                                correcta = 11;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 13;

                                preguntas = 5;
                                pregun4 = 1;
                            }
                            else if (pregun1 == 1 && pregun2 == 2 && pregun3 == 2 || pregun1 == 2 && pregun2 == 2 && pregun3 == 1 || pregun1 == 2 && pregun2 == 1 && pregun3 == 2)
                            {
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca3.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(2);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 11;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 13;

                                preguntas = 5;
                                pregun4 = 1;
                                
                            }
                            else if (pregun1 == 2 && pregun2 == 2 && pregun3 == 2)
                            {
                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca4.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 0; gdFinal.y = 0;
                                Corazones = Vidas(1);
                                SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                SDL_FreeSurface(Corazones);

                                correcta = 11;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 13;

                                preguntas = 5;
                                pregun4 = 1;
                               
                            }

                            preguntas = 5;
                            correctas1 = 0;
                            gdFinal.x = 400; gdFinal.y = 80;
                            Pregunta1 = IMG_Load("Imagenes/Pregunta5.png");
                            SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 400; gdFinal.y = 200;
                            Respuesta1 = IMG_Load("Imagenes/Respuesta5.png");
                            SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(Orca1);
                            SDL_UpdateWindowSurface(Ventana);

                        }
                        else if (preguntas == 5)
                        {
                            std::cout << "Correctas: " << correctas1;
                            if (pregun1 == 1 && pregun2 == 1 && pregun3 == 1 && pregun4 == 1)
                            {
                                //orca1
                                //gano 5 corazones
                                pregun5 = 1;
                                vidas = 5;
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/G5.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                
                                
                                i = 1;
                            }
                            else if (pregun1 == 1 && pregun2 == 1 && pregun3 == 1 && pregun4 == 2 || pregun1 == 2 && pregun2 == 1 && pregun3 == 1 && pregun4 == 1 || pregun1 == 1 && pregun2 == 2 && pregun3 == 1 && pregun4 == 1)
                            {
                                //orca 2
                                //gano 4 corazones
                                pregun5 = 1;
                                
                                std::cout << "\nVidas ganadas: 4";

                                
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/G4.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                vidas = 4;
                                std::cout << "\n4";
                                i = 1;
                            }
                            else if (pregun1 == 1 && pregun2 == 1 && pregun3 == 2 && pregun4 == 2 || pregun1 == 2 && pregun2 == 2 && pregun3 == 1 && pregun4 == 1 || pregun1 == 2 && pregun2 == 1 && pregun3 == 1 && pregun4 == 2)
                            {
                                //orca 3
                                //gano 3 corazones
                                pregun5 = 1;
                                
                                std::cout << "\nVidas ganadas: 3";
                                vidas = 3;

                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/G3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                i = 1;
                            }
                            else if (pregun1 == 1 && pregun2 == 2 && pregun3 == 2 && pregun4 == 2 || pregun1 == 2 && pregun2 == 2 && pregun3 == 2 && pregun4 == 1)
                            {
                                //orca 4
                                //gano 2 corazones
                                pregun5 = 1;
                                
                                std::cout << "\nVidas ganadas: 2";
                                vidas = 2;
                                
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/G2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);

                                
                                i = 1;
                            }
                            else if (pregun1 == 2 && pregun2 == 2 && pregun3 == 2 && pregun4 == 2)
                            {
                                //orca 6
                                //gano 1 corazones
                                pregun5 = 1;
                              
                                std::cout << "\nVidas ganadas: 1";
                                vidas = 1;
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/G1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                std::cout << "Salir";
                                i = 1;
                            }
                            else {
                                //p1 - 2 p2 - 1 p3 - 1 p4 - 2 p5 -1
                                pregun5 = 1;
                                std::cout << "\nOtra validacion: p1 - " << pregun1 << " p2- " << pregun2 << " p3- " << pregun3 << " p4- " << pregun4 << " p5- " << pregun5;
                                i = 1;
                            }

                        }
                        
                        

                }
                else {
                    switch (eleccion.type)
                    {
                    case SDL_QUIT:
                        i = 1;
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:
                        switch (eleccion.key.keysym.sym)
                        {


                        case SDLK_m:

                            if (preguntas == 1) {
                                if (M == 0)
                                {
                                    M++;
                                    correctas1++;
                                    std::cout << "\n M\n";
                                    intentos1++;
                                    gdFinal.x = 421; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/M.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-M1\n";
                                }
                            }
                            else if (preguntas == 2)
                            {
                                if (M2 == 0)
                                {
                                    M++;
                                    correctas1++;
                                    std::cout << "\n M2\n";
                                    intentos1++;
                                    gdFinal.x = 421; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/M.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-M2\n";
                                }
                            }
                            else if (preguntas == 4)
                            {
                                if (M4 == 0)
                                {
                                    M4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 505; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/M.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);

                                    gdFinal.x = 670; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/M.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                                std::cout << "\nPO-O2\n";
                            }
                            break;

                        case SDLK_i:

                            if (preguntas == 1) {
                                if (I == 0)
                                {
                                    I++; intentos1++;
                                    correctas1++;
                                    std::cout << "\nI\n";
                                    gdFinal.x = 446; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/I.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\n O-I1\n";
                                }
                            }
                            else if (preguntas == 2)
                            {
                                if (I2 == 0)
                                {
                                    I2++; intentos1++;
                                    correctas1++;
                                    std::cout << "\nI2\n";
                                    gdFinal.x = 446; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/I.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 680; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/I.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-I2\n";
                                }
                            }
                            else if (preguntas == 4)
                            {
                                if (I4 == 0)
                                {
                                    I4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 600; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/I.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (I5 == 0)
                                {
                                    I5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 523; gdFinal.y = 308;
                                    R1 = IMG_Load("Imagenes/I.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                    
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                                std::cout << "\nPO-O2\n";
                            }

                            break;


                        case SDLK_g:
                            if (preguntas == 1)
                            {
                                if (G == 0)
                                {
                                    G++; intentos1++;
                                    std::cout << "\nG\n";
                                    correctas1++;
                                    gdFinal.x = 474; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/G.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 655; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/G.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                     intentos1++;
                                    std::cout << "\nO-G\n";
                                }


                            }
                            else if (preguntas == 2)
                            {
                                if (G2 == 0)
                                {
                                    
                                    G2++; intentos1++;
                                    std::cout << "\nG2\n";
                                    correctas1++;
                                    gdFinal.x = 474; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/G.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 655; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/G.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nG2\n";
                                }
                            }
                            else if (preguntas == 5)
                            {
                                if (G5 == 0)
                                {
                                    G5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 670; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/G.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;

                        case SDLK_u:
                            if (preguntas == 1)
                            {

                                if (U == 0)
                                {
                                    U++; intentos1++;
                                    correctas1++;
                                    std::cout << "\nU";
                                    gdFinal.x = 503; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/U.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-U1\n";
                                }

                            }
                            else if (preguntas == 2)
                            {
                                if (U2 == 0)
                                {
                                    U2++; intentos1++;
                                    correctas1++;
                                    std::cout << "\nU2\n";
                                    gdFinal.x = 503; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/U.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                 

                                    gdFinal.x = 478; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/U.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-U2\n";
                                }
                            }
                            else if (preguntas == 4)
                            {
                                if (U4 == 0)
                                {
                                    U4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 470; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/U.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (U5 == 0)
                                {
                                    U5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 640; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/U.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    


                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;

                        case SDLK_e:
                            if (preguntas == 1)
                            {

                                if (E == 0)
                                {
                                    E++; intentos1++;
                                    std::cout << "\nE";
                                    correctas1++;
                                    gdFinal.x = 527; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/E.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 680; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/E.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\no-E1\n";
                                }

                            }
                            else if (preguntas == 2)
                            {
                                if (E2 == 0)
                                {
                                    E2++; intentos1++;
                                    std::cout << "\nE2\n";
                                    correctas1++;
                                    gdFinal.x = 527; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/E.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 680; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/E.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\no-E2\n";

                                }
                            }
                            else if (preguntas == 3) 
                            {
                                if (E3 == 0) 
                                {
                                    E3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 440; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/E.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else 
                                {
                                    intentos1++;
                                }

                            }
                            break;

                        case SDLK_l:
                            if (preguntas == 1)
                            {

                                if (L == 0)
                                {
                                    L++; intentos1++;
                                    std::cout << "\nL";
                                    correctas1++;
                                    gdFinal.x = 555; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/L.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x  = 705; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/L.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nYa la habias presionado una vez";
                                }
                            }
                            else if (preguntas == 2)
                            {
                                if (L2 == 0)
                                {
                                    L2++; intentos1++;
                                    std::cout << "\nL2\n";
                                    correctas1++;
                                    gdFinal.x = 555; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/L.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 705; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/L.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-L2\n";
                                }
                            }
                            else if (preguntas == 3)
                            {
                                if (L3 == 0)
                                {
                                    L3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 471; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/L.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (L5 == 0)
                                {
                                    L5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 407; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/L.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else 
                            {
                                intentos1++;
                            }
                            break;

                        case SDLK_a:
                            if (preguntas == 1)
                            {

                                if (A == 0)
                                {
                                    A++; intentos1++;
                                    std::cout << "\nA1\n";
                                    correctas1++;
                                    gdFinal.x = 605; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-A1\n";
                                }
                            }
                            else if (preguntas == 2)
                            {

                                if (A2 == 0)
                                {
                                    A2++; intentos1++;
                                    std::cout << "\nA2\n";
                                    correctas1++;
                                    gdFinal.x = 605; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 550; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-A2\n";
                                }
                            }
                            else if (preguntas == 3)
                            {
                                if (A3 == 0)
                                {
                                    A3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 556; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 4)
                            {
                                if (A4 == 0)
                                {
                                    A4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 537; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (A5 == 0)
                                {
                                    A5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 435; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                    gdFinal.x = 703; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                    gdFinal.x = 615; gdFinal.y = 308;
                                    R1 = IMG_Load("Imagenes/A.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;

                        case SDLK_n:
                            if (preguntas == 1)
                            {
                                if (N == 0)
                                {

                                    N++; intentos1++;
                                    std::cout << "\nN1\n";
                                    correctas1++;
                                    gdFinal.x = 633; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/N.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-N1\n";
                                }


                            }
                            else if (preguntas == 2)
                            {
                                if (N2 == 0)
                                {
                                    N2++; intentos1++;
                                    std::cout << "\nN2\n";
                                    correctas1++;
                                    gdFinal.x = 633; gdFinal.y = 221;
                                    R1 = IMG_Load("Imagenes/N.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    

                                    gdFinal.x = 528; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/N.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-N2\n";
                                }
                            }
                            else if (preguntas == 4)
                            {
                                if (N4 == 0)
                                {
                                    N4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 572; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/N.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (N5 == 0)
                                {
                                    N5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 495; gdFinal.y = 308;
                                    R1 = IMG_Load("Imagenes/N.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                    gdFinal.x = 555; gdFinal.y = 308;
                                    R1 = IMG_Load("Imagenes/N.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                                std::cout << "\nPO-O2\n";
                            }
                            break;


                            //lETRAS ADISIONALES DE PREGUNTA 2 BU
                            
                            
                        case SDLK_b:
                            if (preguntas == 2) {
                                if (B2 == 0)
                                {
                                    B2++; intentos1++;
                                    std::cout << "\nB2\n";
                                    correctas1++;
                                    gdFinal.x = 450; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/B.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-B2\n";
                                }
                            }
                            else if (preguntas == 3)
                            {
                                if (B3 == 0)
                                {
                                    B3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 525; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/B.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else 
                            {
                                intentos1++;
                                std::cout << "\nPO-B2\n";
                            }

                            break;
                        case SDLK_o:
                            if (preguntas == 2) {
                                if (O2 == 0)
                                {
                                    O2++; intentos1++;
                                    std::cout << "\nO2\n";
                                    correctas1++;
                                    gdFinal.x = 500; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/O.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 628; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/O.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                    std::cout << "\nO-O2\n";
                                }
                            }
                            else if (preguntas == 3)
                            {
                                if (O3 == 0)
                                {
                                    O3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 644; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/O.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);

                                    gdFinal.x = 705; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/O.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 4)
                            {
                                if (O4 == 0)
                                {
                                    O4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 700; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/O.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (O5 == 0)
                                {
                                    O5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 545; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/O.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                   

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;
                        case SDLK_r:
                            if (preguntas == 2) {
                                if (R2 == 0 && preguntas == 2)
                                {
                                    R2++; intentos1++;
                                    std::cout << "\nR2\n";
                                    correctas1++;

                                    gdFinal.x = 580; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/R.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 602; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/R.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                }
                                else
                                {
                                    std::cout << "\nO-R2\n";
                                    intentos1++;
                                }
                            }
                            else if (preguntas == 3)
                            {
                                if (R3 == 0)
                                {
                                    R3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 587; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/R.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);

                                    gdFinal.x = 613; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/R.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (R5 == 0)
                                {
                                    R5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 575; gdFinal.y = 238;
                                    R1 = IMG_Load("Imagenes/R.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    


                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;
                        case SDLK_t:
                            if (preguntas == 2) {
                                if (T2 == 0)
                                {
                                    T2++; intentos1++;
                                    std::cout << "\nT2\n";
                                    correctas1++;
                                    gdFinal.x = 655; gdFinal.y = 270;
                                    R1 = IMG_Load("Imagenes/T.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    std::cout << "\nO-T2\n";
                                }
                            }
                            else if (preguntas == 5)
                            {
                                if (T5 == 0)
                                {
                                    T5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 513; gdFinal.y = 238;
                                    R1 = IMG_Load("Imagenes/T.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 610; gdFinal.y = 238;
                                    R1 = IMG_Load("Imagenes/T.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;
                        case SDLK_c:
                            if (preguntas == 3)
                            {
                                if (C3 == 0)
                                {
                                    C3++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 674; gdFinal.y = 246;
                                    R1 = IMG_Load("Imagenes/C.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);

                                    
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                                std::cout << "\nPO-O2\n";
                            }
                            break;
                        case SDLK_h:
                            if (preguntas == 4)
                            {
                                if (H4 == 0)
                                {
                                    H4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 440; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/H.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                                std::cout << "\nPO-O2\n";
                            }
                            break;
                        case SDLK_s:
                            if (preguntas == 4)
                            {
                                if (S4 == 0)
                                {
                                    S4++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 635; gdFinal.y = 244;
                                    R1 = IMG_Load("Imagenes/S.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else if (preguntas == 5)
                            {
                                if (S5 == 0)
                                {
                                    S5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 463; gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/S.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    gdFinal.x = 740;  gdFinal.y = 240;
                                    R1 = IMG_Load("Imagenes/S.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);


                                    gdFinal.x = 650; gdFinal.y = 308;
                                    R1 = IMG_Load("Imagenes/S.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;
                        case SDLK_j:
                            
                            if (preguntas == 5)
                            {
                                if (J5 == 0)
                                {
                                    J5++; intentos1++;
                                    correctas1++;
                                    gdFinal.x = 583; gdFinal.y = 308;
                                    R1 = IMG_Load("Imagenes/J.png");
                                    SDL_BlitSurface(R1, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_UpdateWindowSurface(Ventana);

                                    
                                }
                                else
                                {
                                    intentos1++;
                                }

                            }
                            else
                            {
                                intentos1++;
                            }
                            break;
                      
                            




                        default:
                            std::cout << "\nIncorrecta\n";
                            std::cout << "L- " << limite;
                            gdFinal.x = 150; gdFinal.y = 100; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;
                            if (intentos1 != limite && intentos1 < limite)
                            {
                                
                                intentos1++;
                                std::cout << "\nI-" << intentos1;

                            }
                            else if (preguntas == 1)
                            {
                                Fondo = IMG_Load("Imagenes/I3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(800);

                                pregun1 = 2;

                                SDL_FreeSurface(superficieVentana);
                                Fondo = IMG_Load("Imagenes/FondoOrca.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                gdFinal.x = 150; gdFinal.y = 100;
                                Orca1 = IMG_Load("Imagenes/orca2.png");
                                SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 400; gdFinal.y = 80;
                                Pregunta1 = IMG_Load("Imagenes/Pregunta2.png");
                                SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 400; gdFinal.y = 200;
                                Respuesta1 = IMG_Load("Imagenes/Respuesta2.png");
                                SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                                correcta = 12;
                                intentos1 = 0;
                                correctas1 = 0;
                                limite = 14;
                                preguntas = 2;
                                pregun1 = 2;

                                SDL_FreeSurface(Fondo);
                                SDL_FreeSurface(Orca1);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            else if (preguntas == 2 )
                            {
                                Fondo = IMG_Load("Imagenes/I3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(800);

                                SDL_FreeSurface(superficieVentana);
                                Fondo = IMG_Load("Imagenes/FondoOrca.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                if (pregun1 == 1) 
                                {
                                    pregun2 = 2;

                                   
                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca2.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                    gdFinal.x = 0; gdFinal.y = 0;
                                    Corazones = Vidas(1);
                                    SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_FreeSurface(Corazones);

                                    correcta = 7;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 9;
                                    preguntas = 3;


                                }
                                else if (pregun1 == 2)
                                {
                                    pregun2 = 2;

                                    
                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca3.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                    

                                    correcta = 7;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 9;
                                    preguntas = 3;

                                }

                                gdFinal.x = 400; gdFinal.y = 80;
                                Pregunta1 = IMG_Load("Imagenes/Pregunta3.png");
                                SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 400; gdFinal.y = 200;
                                Respuesta1 = IMG_Load("Imagenes/Respuesta3.png");
                                SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                                SDL_FreeSurface(Fondo);
                                SDL_FreeSurface(Orca1);
                                SDL_UpdateWindowSurface(Ventana);
                                
                            }
                            else if (preguntas == 3)
                            {
                                Fondo = IMG_Load("Imagenes/I3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(800);


                                SDL_FreeSurface(superficieVentana);
                                Fondo = IMG_Load("Imagenes/FondoOrca.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                if (pregun1 == 1 && pregun2 == 1)
                                {
                                    pregun3 = 2;
                                    gdFinal.x = 0; gdFinal.y = 0;
                                    Corazones = Vidas(2);
                                    SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_FreeSurface(Corazones);
                                    
                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca2.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);


                                    correcta = 8;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 10;
                                    preguntas = 4;

                                }
                                else if (pregun1 == 1 && pregun2 == 2|| pregun1 == 2 && pregun2 == 1)
                                {
                                   
                                    pregun3 = 2;

                                    gdFinal.x = 0; gdFinal.y = 0;
                                    Corazones = Vidas(1);
                                    SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_FreeSurface(Corazones);

                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca3.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);


                                    correcta = 8;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 10;
                                    preguntas = 4;

                                   
                                }
                                else if (pregun1 == 2 && pregun2 == 2)
                                {

                                    pregun3 = 2;


                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca4.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);


                                    correcta = 8;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 10;
                                    preguntas = 4;
                                }
                                preguntas = 4;
                                gdFinal.x = 400; gdFinal.y = 80;
                                Pregunta1 = IMG_Load("Imagenes/Pregunta4.png");
                                SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 430; gdFinal.y = 200;
                                Respuesta1 = IMG_Load("Imagenes/Respuesta4.png");
                                SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                                SDL_FreeSurface(Fondo);
                                SDL_FreeSurface(Orca1);
                                SDL_UpdateWindowSurface(Ventana);

                            }
                            else if (preguntas == 4)
                            {
                                Fondo = IMG_Load("Imagenes/I3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(1000);
                                Fondo = IMG_Load("Imagenes/I1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(800);
                               
    
                                SDL_FreeSurface(superficieVentana);
                                Fondo = IMG_Load("Imagenes/FondoOrca.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                if (pregun1 == 1 && pregun2 == 1 && pregun3 == 1)
                                {
                                    pregun4 = 2;
                                   
                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca2.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                    gdFinal.x = 0; gdFinal.y = 0;
                                    Corazones = Vidas(3);
                                    SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_FreeSurface(Corazones);

                                    correcta = 11;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 12;
                                    preguntas = 5;

                                   

                                }
                                else if (pregun1 == 1 && pregun2 == 1 && pregun3 == 2 || pregun1 == 2 && pregun2 == 1 && pregun3 == 1)
                                {
                                    pregun4 = 2;

                                 
                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca3.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                    gdFinal.x = 0; gdFinal.y = 0;
                                    Corazones = Vidas(2);
                                    SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_FreeSurface(Corazones);

                                    correcta = 11;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 12;
                                    preguntas = 5;

                                }
                                else if (pregun1 == 1 && pregun2 == 2 && pregun3 == 2 || pregun1 == 2 && pregun2 == 2 && pregun3 == 1)
                                {

                                    pregun4 = 2;
                                    
                                    gdFinal.x = 0; gdFinal.y = 0;
                                    Corazones = Vidas(1);
                                    SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                                    SDL_FreeSurface(Corazones);

                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca4.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);


                                    correcta = 11;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 12;
                                    preguntas = 5;

                                   
                                }
                                else if (pregun1 == 2 && pregun2 == 2 && pregun3 == 2)
                                {

                                    pregun4 = 2;
                                    
                                  

                                    gdFinal.x = 150; gdFinal.y = 100;
                                    Orca1 = IMG_Load("Imagenes/orca6.png");
                                    SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);

                                    

                                    correcta = 11;
                                    intentos1 = 0;
                                    correctas1 = 0;
                                    limite = 12;
                                    preguntas = 5;

                                   
                                }
                                preguntas = 5;
                                correcta = 11;
                                correctas1 = 0;
                                gdFinal.x = 400; gdFinal.y = 80;
                                Pregunta1 = IMG_Load("Imagenes/Pregunta5.png");
                                SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 400; gdFinal.y = 200;
                                Respuesta1 = IMG_Load("Imagenes/Respuesta5.png");
                                SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);

                                correctas1 = 0;
                                SDL_FreeSurface(Fondo);
                                SDL_FreeSurface(Orca1);
                                SDL_UpdateWindowSurface(Ventana);

                            }
                            else if (preguntas == 5)
                            {
                            std::cout << "Correctas: " << correctas1;
                                SDL_FreeSurface(superficieVentana);
                                Fondo = IMG_Load("Imagenes/FondoOrca.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                if (pregun1 == 1 && pregun2 == 1 && pregun3 == 1 && pregun4 == 1)
                                {
                                   
                                    pregun5 = 2;
                                    //orca 2
                                    vidas = 4;
                                    //gano 4 cora
                                    std::cout << "\nVidas ganadas: 4" ;
                                    SDL_Delay(1000);
                                    Fondo = IMG_Load("Imagenes/G4.png");
                                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                    SDL_FreeSurface(Fondo);
                                    SDL_UpdateWindowSurface(Ventana);
                                    SDL_Delay(1000);

                                    i = 1;
                                }
                                else if (pregun1 == 1 && pregun2 == 1 && pregun3 == 1 && pregun4 == 2 || pregun1 == 2 && pregun2 == 1 && pregun3 == 1 && pregun4 == 1 || pregun1 == 1 && pregun2 == 2 && pregun3 == 1 && pregun4 == 1)
                                {
                                    pregun5 = 2;
                                    //orca 3 
                                   //gano 3 cora
                                    std::cout << "\nVidas ganadas: 3";
                                    vidas = 3;
                                    SDL_Delay(1000);
                                    Fondo = IMG_Load("Imagenes/G3.png");
                                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                    SDL_FreeSurface(Fondo);
                                    SDL_UpdateWindowSurface(Ventana);
                                    SDL_Delay(1000);

                                    i = 1;
                                }
                                else if (pregun1 == 1 && pregun2 == 1 && pregun3 == 2 && pregun4 == 2 || pregun1 == 2 && pregun2 == 2 && pregun3 == 1 && pregun4 == 1)
                                {
                                    pregun5 = 2;
                                    //orca 4
                                    vidas = 2;
                                  //gano 2 cora
                                    std::cout << "\nVidas ganadas: 2";

                                    SDL_Delay(1000);
                                    Fondo = IMG_Load("Imagenes/G2.png");
                                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                    SDL_FreeSurface(Fondo);
                                    SDL_UpdateWindowSurface(Ventana);
                                    SDL_Delay(1000);

                                    i = 1;
                                }
                                else if (pregun1 == 1 && pregun2 == 2 && pregun3 == 2 && pregun4 == 2 || pregun1 == 2 && pregun2 == 2 && pregun3 == 2 && pregun4 == 1)
                                {
                                    pregun5 = 2;
                                    //orca 6
                                    vidas = 1;
                                  //gano 1 cora
                                    std::cout << "\nVidas ganadas: 1";

                                    SDL_Delay(1000);
                                    Fondo = IMG_Load("Imagenes/G1.png");
                                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                    SDL_FreeSurface(Fondo);
                                    SDL_UpdateWindowSurface(Ventana);
                                    SDL_Delay(1000);

                                    i = 1;
                                }
                                else if (pregun1 == 2 && pregun2 == 2 && pregun3 == 2 && pregun4 == 2)
                                {
                                    pregun5 = 2;
                                    //orca 8
                                    vidas = 0;
                                  //gano 0 cora
                                    std::cout << "\nVidas ganadas: 0";

                                    SDL_Delay(1000);
                                    Fondo = IMG_Load("Imagenes/G0.png");
                                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                    SDL_FreeSurface(Fondo);
                                    SDL_UpdateWindowSurface(Ventana);
                                    SDL_Delay(1000);

                                    i = 1;
                                }
                                else {
                                    std::cout << "\nOtra validacion: p1 - " << pregun1 << " p2- " << pregun2 << " p3- " << pregun3 << " p4- " << pregun4 << " p5- " << pregun5;

                                }
                               

                                i = 1;
                                
                            }
                            
                            break;

                        }

                        default:

                        break;
                    }
                }
            }
        }
    }

    SDL_UpdateWindowSurface(Ventana);

    
    std::cout << "hola";


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


                  
                    SDL_FreeSurface(superficieVentana);
                    SDL_DestroyWindow(Ventana);

                    SDL_Quit();
                    
                }

                
          
            }
        }
    }

    SDL_FreeSurface(superficieVentana);
    SDL_DestroyWindow(Ventana);

    SDL_Quit();



}

//Ciencia
void Game::miniJuegoCiencia()
{




    const int WIDTH = 1000;
    const int HEIGHT = 600;
    //const int SPRITE_SIZE = 120;
    const int SizeMessaje = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
    SDL_Renderer* renderizado; // render de ventana

    //Imagenes
    SDL_Surface* Fondo1;
    SDL_Texture* Tfondo;
    SDL_Surface* superficieVentana;
    SDL_Surface* prt1 = nullptr;
    SDL_Surface* prt2 = nullptr;
    SDL_Surface* prt3 = nullptr;
    SDL_Surface* prt4 = nullptr;
    SDL_Surface* prt5 = nullptr;
    SDL_Surface* prt6 = nullptr;
    SDL_Surface* prt7 = nullptr;
    SDL_Surface* prt8 = nullptr;
    SDL_Surface* prt9 = nullptr;
    SDL_Surface* prt10 = nullptr;
    SDL_Surface* prt11 = nullptr;
    SDL_Surface* prt12 = nullptr;
    SDL_Surface* prt13 = nullptr;
    SDL_Surface* prt14 = nullptr;
    SDL_Surface* prt15 = nullptr;
    SDL_Surface* prt16 = nullptr;
    SDL_Surface* prt17 = nullptr;
    SDL_Surface* prt18 = nullptr;
    SDL_Surface* prt19 = nullptr;
    SDL_Surface* prt20 = nullptr;
    SDL_Surface* prt21 = nullptr;
    SDL_Surface* prt22 = nullptr;
    SDL_Surface* prt23 = nullptr;
    SDL_Surface* prt24 = nullptr;
    SDL_Surface* prt25 = nullptr;

    SDL_Surface* correct1 = nullptr;
    SDL_Surface* correct2 = nullptr;
    SDL_Surface* correct3 = nullptr;
    SDL_Surface* correct4 = nullptr;
    SDL_Surface* correct5 = nullptr;

    SDL_Surface* win1 = nullptr;
    SDL_Surface* win2 = nullptr;
    SDL_Surface* win3 = nullptr;
    SDL_Surface* win4 = nullptr;
    SDL_Surface* win5 = nullptr;

    SDL_Surface* heart;

    SDL_Texture* Fondo;



    SDL_Surface* Continuar;




    SDL_Event EventoSalir;

    const Uint32* m;
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    SDL_Renderer* renderer;
    //evento para el toque de el vaso

    SDL_Event eleccion;
    int SPRITE_SIZE = 50;

    Ventana = SDL_CreateWindow("Pantalla Cartas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
    SDL_FillRect(superficieVentana, NULL, Color);

    renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);



    Fondo1 = IMG_Load("Img/5sec.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/4sec.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);

    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/3sec.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/2sec.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/1sec.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);

    Fondo1 = IMG_Load("Img/1.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Surface* numScore;
    SDL_Rect    gdPosScore;
    prt1 = IMG_Load("Img/1.png");
    prt2 = IMG_Load("Img/2.png");
    prt3 = IMG_Load("Img/3.png");
    prt4 = IMG_Load("Img/4.png");
    prt5 = IMG_Load("Img/5.png");
    prt6 = IMG_Load("Img/6.png");
    prt7 = IMG_Load("Img/7.png");
    prt8 = IMG_Load("Img/8.png");
    prt9 = IMG_Load("Img/9.png");
    prt10 = IMG_Load("Img/10.png");
    prt11 = IMG_Load("Img/11.png");
    prt12 = IMG_Load("Img/12.png");
    prt13 = IMG_Load("Img/13.png");
    prt14 = IMG_Load("Img/14.png");
    prt15 = IMG_Load("Img/15.png");
    prt16 = IMG_Load("Img/16.png");
    prt17 = IMG_Load("Img/17.png");
    prt18 = IMG_Load("Img/18.png");
    prt19 = IMG_Load("Img/19.png");
    prt20 = IMG_Load("Img/20.png");
    prt21 = IMG_Load("Img/21.png");
    prt22 = IMG_Load("Img/22.png");
    prt23 = IMG_Load("Img/23.png");
    prt24 = IMG_Load("Img/24.png");
    prt25 = IMG_Load("Img/25.png");
    correct1 = IMG_Load("Img/1correct.png");
    correct2 = IMG_Load("Img/2correct.png");
    correct3 = IMG_Load("Img/3correct.png");
    correct4 = IMG_Load("Img/4correct.png");
    correct5 = IMG_Load("Img/5correct.png");
    win1 = IMG_Load("Img/win1.png");
    win2 = IMG_Load("Img/win2.png");
    win3 = IMG_Load("Img/win3.png");
    win4 = IMG_Load("Img/win4.png");
    win5 = IMG_Load("Img/win5.png");


    SDL_Surface* heart1 = NULL;

    int Puntuacion = 0;
    int bk = 0;
    int prtnum = 1;
    SDL_Surface* currentImg = prt1;
    SDL_Event evento;

    /*

    if (Puntuacion == 1) {
                               heart1 = IMG_Load("Img/5heart.png");

                               SDL_BlitSurface(heart1, NULL, superficieVentana, NULL);
                               SDL_UpdateWindowSurface(Ventana);
                           }*/

                           /*gdPosScore.x = 670; gdPosScore.y = 525; gdPosScore.w = SPRITE_SIZE; gdPosScore.h = SPRITE_SIZE;
                           if (Puntuacion == 1) {
                               heart1 = IMG_Load("Img/5heart.png");

                               SDL_BlitSurface(heart1, &rcInicial, superficieVentana, &gdPosScore);
                               SDL_UpdateWindowSurface(Ventana);
                           }*/


    while (isRunning) {

        gdPosScore.x = 700; gdPosScore.y = 480; gdPosScore.w = SPRITE_SIZE; gdPosScore.h = SPRITE_SIZE;

        if (Puntuacion == 1) {

            heart1 = IMG_Load("Img/1heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 2) {

            heart1 = IMG_Load("Img/2heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 3) {

            heart1 = IMG_Load("Img/3heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 4) {

            heart1 = IMG_Load("Img/4heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 5) {

            heart1 = IMG_Load("Img/5heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }

        SDL_UpdateWindowSurface(Ventana);
        if (prtnum == 1) {



            while (SDL_PollEvent(&evento) != 0) {


                if (evento.button.x >= 106 && evento.button.x <= 305 && evento.button.y >= 175 && evento.button.y <= 274) {



                    currentImg = prt1;

                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = prt5;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);



                        SDL_Delay(2000);

                        prtnum = 2;
                    }

                }
                if (evento.button.x >= 280 && evento.button.x <= 480 && evento.button.y >= 30 && evento.button.y <= 125) {


                    currentImg = prt2;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt5;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 2;
                    }

                }
                if (evento.button.x >= 458 && evento.button.x <= 656 && evento.button.y >= 180 && evento.button.y <= 274) {


                    currentImg = prt3;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = correct1;

                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 2;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 680 && evento.button.x <= 871 && evento.button.y >= 34 && evento.button.y <= 124) {


                    currentImg = prt4;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt5;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 2;
                    }

                }


            }

            //****************************************************************

        }

        if (prtnum == 2) {
            if (Puntuacion == 1) {

                heart1 = IMG_Load("Img/1heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 2) {

                heart1 = IMG_Load("Img/2heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 3) {

                heart1 = IMG_Load("Img/3heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 4) {

                heart1 = IMG_Load("Img/4heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 5) {

                heart1 = IMG_Load("Img/5heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }


            while (SDL_PollEvent(&evento) != 0) {
                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }

                if (bk == 0) {
                    Fondo1 = IMG_Load("Img/5sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 1;
                }


                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);
                if (evento.button.x >= 106 && evento.button.x <= 305 && evento.button.y >= 175 && evento.button.y <= 274) {

                    currentImg = prt6;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = correct2;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);

                        SDL_Delay(2000);

                        prtnum = 3;
                    }

                }
                if (evento.button.x >= 280 && evento.button.x <= 480 && evento.button.y >= 30 && evento.button.y <= 125) {


                    currentImg = prt7;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt10;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 3;
                    }

                }
                if (evento.button.x >= 458 && evento.button.x <= 656 && evento.button.y >= 180 && evento.button.y <= 274) {


                    currentImg = prt8;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt10;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 3;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 680 && evento.button.x <= 871 && evento.button.y >= 34 && evento.button.y <= 124) {


                    currentImg = prt9;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt10;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 3;
                    }

                }

            }
        }
        //****************************************************************
        if (prtnum == 3) {
            while (SDL_PollEvent(&evento) != 0) {
                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (bk == 1) {
                    Fondo1 = IMG_Load("Img/5sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 2;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                //SDL_UpdateWindowSurface(Ventana);


                if (evento.button.x >= 106 && evento.button.x <= 305 && evento.button.y >= 175 && evento.button.y <= 274) {

                    currentImg = prt11;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt15;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);

                        SDL_Delay(2000);

                        prtnum = 4;
                    }

                }
                if (evento.button.x >= 280 && evento.button.x <= 480 && evento.button.y >= 30 && evento.button.y <= 125) {


                    currentImg = prt12;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = correct3;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 4;
                    }

                }
                if (evento.button.x >= 458 && evento.button.x <= 656 && evento.button.y >= 180 && evento.button.y <= 274) {


                    currentImg = prt13;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt15;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 4;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 680 && evento.button.x <= 871 && evento.button.y >= 34 && evento.button.y <= 124) {


                    currentImg = prt14;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt15;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 4;
                    }

                }


            }

        }


        //****************************************************************
        if (prtnum == 4) {
            while (SDL_PollEvent(&evento) != 0) {
                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (bk == 2) {
                    Fondo1 = IMG_Load("Img/5sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 3;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);

                if (evento.button.x >= 106 && evento.button.x <= 305 && evento.button.y >= 175 && evento.button.y <= 274) {

                    currentImg = prt16;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = correct4;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);

                        SDL_Delay(2000);

                        prtnum = 5;
                    }

                }
                if (evento.button.x >= 280 && evento.button.x <= 480 && evento.button.y >= 30 && evento.button.y <= 125) {


                    currentImg = prt17;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt20;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 5;
                    }

                }
                if (evento.button.x >= 458 && evento.button.x <= 656 && evento.button.y >= 180 && evento.button.y <= 274) {


                    currentImg = prt18;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt20;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 5;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 680 && evento.button.x <= 871 && evento.button.y >= 34 && evento.button.y <= 124) {


                    currentImg = prt19;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt20;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 5;
                    }

                }


            }

        }




        //****************************************************************
        if (prtnum == 5) {
            while (SDL_PollEvent(&evento) != 0) {

                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (bk == 3) {
                    Fondo1 = IMG_Load("Img/5sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    /// SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1sec.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 4;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                //SDL_UpdateWindowSurface(Ventana);
                if (evento.button.x >= 106 && evento.button.x <= 305 && evento.button.y >= 175 && evento.button.y <= 274) {

                    currentImg = prt21;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt25;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);

                        SDL_Delay(2000);

                        prtnum = 6;
                    }

                }
                if (evento.button.x >= 280 && evento.button.x <= 480 && evento.button.y >= 30 && evento.button.y <= 125) {


                    currentImg = prt22;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt25;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 6;
                    }

                }
                if (evento.button.x >= 458 && evento.button.x <= 656 && evento.button.y >= 180 && evento.button.y <= 274) {


                    currentImg = prt23;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = prt25;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 6;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 680 && evento.button.x <= 871 && evento.button.y >= 34 && evento.button.y <= 124) {


                    currentImg = prt24;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = correct5;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 6;
                    }

                }


            }

        }

        //****************************************************************
        if (prtnum == 6) {

            if (Puntuacion == 1) {


                currentImg = win1;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }
            if (Puntuacion == 2) {


                currentImg = win2;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }  if (Puntuacion == 3) {


                currentImg = win3;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }  if (Puntuacion == 4) {


                currentImg = win4;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            } if (Puntuacion == 5) {


                currentImg = win5;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }




        }



        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
        // SDL_UpdateWindowSurface(Ventana);
    }



    SDL_Surface* tmpsurface;


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
                    salir = 1;
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


    SDL_FreeSurface(prt1);
    SDL_FreeSurface(prt2);
    SDL_FreeSurface(prt3);
    SDL_FreeSurface(prt4);
    SDL_FreeSurface(prt5);

    prt1 = prt2 = prt3 = superficieVentana = nullptr;
    Ventana = nullptr;

    SDL_DestroyWindow(Ventana);

    SDL_Quit();



}


//Historia
void Game::minjuegoHistoria() {

    ventanaMinijuegoHistoria("Historia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, false);
    minijuegoHistoriaElementos();
    while (true)
        minijuegoHistoriaEventos();
}

void Game::ventanaMinijuegoHistoria(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
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

void Game::minijuegoHistoriaElementos() {
    //fondo
    superficieVentana = SDL_GetWindowSurface(window);

    background = IMG_Load("assets/fondominijuegohistoria.png");
    SDL_BlitSurface(background, NULL, superficieVentana, NULL);

    //personaje - mensajero del rey
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 635; posInicial.h = 1011;
    posFinal.x = 480; posFinal.y = 50; posFinal.w = 635; posFinal.h = 1011;
    personaje1 = IMG_Load("assets/mensajerohistoria.png");
    SDL_BlitSurface(personaje1, &posInicial, superficieVentana, &posFinal);

    //mensaje de pulsa espacio
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
    posFinal.x = 10; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
    pulsaespacio = IMG_Load("assets/pulsaespacio.png");
    SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

    //globo de texto 1
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 720;
    posFinal.x = 100; posFinal.y = 50; posFinal.w = 500; posFinal.h = 720;
    globodetexto1 = IMG_Load("assets/globodetexto1.png");
    SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);

    SDL_UpdateWindowSurface(window);
}

void Game::minijuegoHistoriaEventos() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        //cerrar ventana
    case SDL_QUIT:
        exit(1);
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_SPACE:
            //determina que elemento va despues
            if (elementospantalla == 0) {
                globodetexto1 = IMG_Load("assets/globodetexto2.png");
                SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);
                elementospantalla++;
            }
            else if (elementospantalla == 1) {
                globodetexto1 = IMG_Load("assets/globodetexto3.png");
                SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);
                elementospantalla++;
            }
            else if (elementospantalla == 2) {
                //limpiar la ventana (surface)
                SDL_FillRect(superficieVentana, NULL, 0x000000);
                SDL_BlitSurface(background, NULL, superficieVentana, NULL);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 377;
                posFinal.x = 70; posFinal.y = 40; posFinal.w = 500; posFinal.h = 377;
                mensaje1 = IMG_Load("assets/mensajeminijuegohistoria1a.png");
                SDL_BlitSurface(mensaje1, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 300; posInicial.h = 530;
                posFinal.x = 620; posFinal.y = 2; posFinal.w = 300; posFinal.h = 530;
                tablajuego = IMG_Load("assets/tabladelingotes.png");
                SDL_BlitSurface(tablajuego, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
                posFinal.x = 10; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
                pulsaespacio = IMG_Load("assets/pulsaespacio.png");
                SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

                elementospantalla++;
            }
            else if (elementospantalla == 3) {
                SDL_FillRect(superficieVentana, NULL, 0x000000);
                SDL_BlitSurface(background, NULL, superficieVentana, NULL);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 635; posInicial.h = 1011;
                posFinal.x = 460; posFinal.y = -10; posFinal.w = 635; posFinal.h = 1011;
                personaje1 = IMG_Load("assets/mensajerohistoria.png");
                SDL_BlitSurface(personaje1, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 946; posInicial.h = 283;
                posFinal.x = 30; posFinal.y = 260; posFinal.w = 946; posFinal.h = 283;
                pregunta1 = IMG_Load("assets/minijuegohistoriapregunta1.png");
                SDL_BlitSurface(pregunta1, &posInicial, superficieVentana, &posFinal);
            }

            SDL_UpdateWindowSurface(window);
            break;
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        int cursorx = event.motion.x, cursory = event.motion.y;

        opcionSeleccionada = 0;
        //detectar que opcion elige con el mouse
        if (elementospantalla == 3 || elementospantalla == 5 || elementospantalla == 7 || elementospantalla == 9
            || elementospantalla == 11) {
            //Si presiona la opcion A
            if (cursorx > 70 && cursorx < 470 && cursory > 402 && cursory < 450) {
                switch (elementospantalla) {
                case 3:
                    eliminado = true;
                    break;
                case 5:
                    eliminado = true;
                    break;
                case 7:
                    puntos++;
                    break;
                case 9:
                    puntos--;
                    eliminado = true;
                    break;
                case 11:
                    puntos++;
                    break;
                }
                elementospantalla++;
                opcionSeleccionada = 1;
            }

            //Si presiona la opcion B
            if (cursorx > 540 && cursorx < 920 && cursory > 402 && cursory < 450) {
                switch (elementospantalla) {
                case 3:
                    eliminado = true;
                    break;
                case 5:
                    puntos++;
                    break;
                case 7:
                    puntos--;
                    eliminado = true;
                    break;
                case 9:
                    puntos++;
                    break;
                case 11:
                    puntos--;
                    eliminado = true;
                    break;
                }
                elementospantalla++;
                opcionSeleccionada = 2;
            }

            //Si presiona la opcion C
            if (cursorx > 70 && cursorx < 470 && cursory > 470 && cursory < 532) {
                switch (elementospantalla) {
                case 3:
                    puntos++;
                    break;
                case 5:
                    eliminado = true;
                    break;
                case 7:
                    puntos--;
                    eliminado = true;
                    break;
                case 9:
                    puntos--;
                    eliminado = true;
                    break;
                case 11:
                    puntos--;
                    eliminado = true;
                    break;
                }
                elementospantalla++;
                opcionSeleccionada = 3;
            }

            //Si presiona la opcion D
            if (cursorx > 540 && cursorx < 920 && cursory > 470 && cursory < 532) {
                switch (elementospantalla) {
                case 3:
                    eliminado = true;
                    break;
                case 5:
                    eliminado = true;
                    break;
                case 7:
                    puntos--;
                    eliminado = true;
                    break;
                case 9:
                    puntos--;
                    eliminado = true;
                    break;
                case 11:
                    puntos--;
                    eliminado = true;
                    break;
                }
                elementospantalla++;
                opcionSeleccionada = 4;
            }
        }


        if (!eliminado && opcionSeleccionada != 0) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 250; posInicial.h = 250;
            posFinal.x = 60; posFinal.y = 10; posFinal.w = 250; posFinal.h = 250;
            correcto = IMG_Load("assets/correcto.png");
            SDL_BlitSurface(correcto, &posInicial, superficieVentana, &posFinal);
            SDL_UpdateWindowSurface(window);

            for (int i = 0; i < 3000; i++) {
                std::cout << i << "\n";
            }

            //resetear pantalla
            SDL_FillRect(superficieVentana, NULL, 0x000000);
            SDL_BlitSurface(background, NULL, superficieVentana, NULL);

            posInicial.x = 0; posInicial.y = 0; posInicial.w = 635; posInicial.h = 1011;
            posFinal.x = 460; posFinal.y = -10; posFinal.w = 635; posFinal.h = 1011;
            personaje1 = IMG_Load("assets/mensajerohistoria.png");
            SDL_BlitSurface(personaje1, &posInicial, superficieVentana, &posFinal);

            //detectar en que pantalla va
            if (elementospantalla == 4) {
                posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 720;
                posFinal.x = 100; posFinal.y = 50; posFinal.w = 500; posFinal.h = 720;
                globodetexto1 = IMG_Load("assets/globodetexto4.png");
                SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
                posFinal.x = -100; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
                pulsaespacio = IMG_Load("assets/pulsaCoR.png");
                SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

                SDL_UpdateWindowSurface(window);

                bool runWhile = true;
                while (runWhile) {
                    SDL_Event event2;
                    SDL_PollEvent(&event2);
                    switch (event2.type) {
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDL_KEYDOWN:
                        switch (event2.key.keysym.sym) {
                        case SDLK_c:
                            runWhile = false;
                            break;
                        case SDLK_r:
                            runWhile = false;
                            eliminado = true;
                            break;
                        }
                        break;
                    }
                }
            }
            if (elementospantalla == 6) {
                posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 720;
                posFinal.x = 100; posFinal.y = 50; posFinal.w = 500; posFinal.h = 720;
                globodetexto1 = IMG_Load("assets/globodetexto4.png");
                SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
                posFinal.x = -100; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
                pulsaespacio = IMG_Load("assets/pulsaCoR.png");
                SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

                SDL_UpdateWindowSurface(window);

                bool runWhile = true;
                while (runWhile) {
                    SDL_Event event2;
                    SDL_PollEvent(&event2);
                    switch (event2.type) {
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDL_KEYDOWN:
                        switch (event2.key.keysym.sym) {
                        case SDLK_c:
                            runWhile = false;
                            break;
                        case SDLK_r:
                            runWhile = false;
                            eliminado = true;
                            break;
                        }
                        break;
                    }
                }
            }
            if (elementospantalla == 8) {
                posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 720;
                posFinal.x = 100; posFinal.y = 50; posFinal.w = 500; posFinal.h = 720;
                globodetexto1 = IMG_Load("assets/globodetexto4.png");
                SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
                posFinal.x = -100; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
                pulsaespacio = IMG_Load("assets/pulsaCoR.png");
                SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

                SDL_UpdateWindowSurface(window);

                bool runWhile = true;
                while (runWhile) {
                    SDL_Event event2;
                    SDL_PollEvent(&event2);
                    switch (event2.type) {
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDL_KEYDOWN:
                        switch (event2.key.keysym.sym) {
                        case SDLK_c:
                            runWhile = false;
                            break;
                        case SDLK_r:
                            runWhile = false;
                            eliminado = true;
                            break;
                        }
                        break;
                    }
                }
            }
            if (elementospantalla == 10) {
                posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 720;
                posFinal.x = 100; posFinal.y = 50; posFinal.w = 500; posFinal.h = 720;
                globodetexto1 = IMG_Load("assets/globodetexto4.png");
                SDL_BlitSurface(globodetexto1, &posInicial, superficieVentana, &posFinal);

                posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
                posFinal.x = -100; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
                pulsaespacio = IMG_Load("assets/pulsaCoR.png");
                SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

                SDL_UpdateWindowSurface(window);

                bool runWhile = true;
                while (runWhile) {
                    SDL_Event event2;
                    SDL_PollEvent(&event2);
                    switch (event2.type) {
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDL_KEYDOWN:
                        switch (event2.key.keysym.sym) {
                        case SDLK_c:
                            runWhile = false;
                            break;
                        case SDLK_r:
                            runWhile = false;
                            eliminado = true;
                            break;
                        }
                        break;
                    }
                }
            }

            SDL_FillRect(superficieVentana, NULL, 0x000000);
            SDL_BlitSurface(background, NULL, superficieVentana, NULL);
            elementospantalla++;

            posInicial.x = 0; posInicial.y = 0; posInicial.w = 635; posInicial.h = 1011;
            posFinal.x = 460; posFinal.y = -10; posFinal.w = 635; posFinal.h = 1011;
            personaje1 = IMG_Load("assets/mensajerohistoria.png");
            SDL_BlitSurface(personaje1, &posInicial, superficieVentana, &posFinal);

            posInicial.x = 0; posInicial.y = 0; posInicial.w = 946; posInicial.h = 283;
            posFinal.x = 30; posFinal.y = 260; posFinal.w = 946; posFinal.h = 283;

            //detectar en que pregunta va
            if (!eliminado) {
                if (elementospantalla == 5) {
                    pregunta1 = IMG_Load("assets/minijuegohistoriapregunta2.png");
                    SDL_BlitSurface(pregunta1, &posInicial, superficieVentana, &posFinal);

                    posInicial.x = 0; posInicial.y = 0; posInicial.w = 268; posInicial.h = 102;
                    posFinal.x = 380; posFinal.y = 50; posFinal.w = 268; posFinal.h = 102;
                    lingote = IMG_Load("assets/10lingotes.png");
                    SDL_BlitSurface(lingote, &posInicial, superficieVentana, &posFinal);
                }
                if (elementospantalla == 7) {
                    pregunta1 = IMG_Load("assets/minijuegohistoriapregunta3.png");
                    SDL_BlitSurface(pregunta1, &posInicial, superficieVentana, &posFinal);

                    posInicial.x = 0; posInicial.y = 0; posInicial.w = 268; posInicial.h = 102;
                    posFinal.x = 380; posFinal.y = 50; posFinal.w = 268; posFinal.h = 102;
                    lingote = IMG_Load("assets/20lingotes.png");
                    SDL_BlitSurface(lingote, &posInicial, superficieVentana, &posFinal);
                }
                if (elementospantalla == 9) {
                    pregunta1 = IMG_Load("assets/minijuegohistoriapregunta4.png");
                    SDL_BlitSurface(pregunta1, &posInicial, superficieVentana, &posFinal);

                    posInicial.x = 0; posInicial.y = 0; posInicial.w = 268; posInicial.h = 102;
                    posFinal.x = 380; posFinal.y = 50; posFinal.w = 268; posFinal.h = 102;
                    lingote = IMG_Load("assets/40lingotes.png");
                    SDL_BlitSurface(lingote, &posInicial, superficieVentana, &posFinal);
                }
                if (elementospantalla == 11) {
                    pregunta1 = IMG_Load("assets/minijuegohistoriapregunta5.png");
                    SDL_BlitSurface(pregunta1, &posInicial, superficieVentana, &posFinal);

                    posInicial.x = 0; posInicial.y = 0; posInicial.w = 268; posInicial.h = 102;
                    posFinal.x = 380; posFinal.y = 50; posFinal.w = 268; posFinal.h = 102;
                    lingote = IMG_Load("assets/70lingotes.png");
                    SDL_BlitSurface(lingote, &posInicial, superficieVentana, &posFinal);
                }
                if (elementospantalla == 13) {

                    posInicial.x = 0; posInicial.y = 0; posInicial.w = 268; posInicial.h = 102;
                    posFinal.x = 380; posFinal.y = 50; posFinal.w = 268; posFinal.h = 102;
                    lingote = IMG_Load("assets/100lingotes.png");
                    SDL_BlitSurface(lingote, &posInicial, superficieVentana, &posFinal);

                    eliminado = true;
                }
            }
        }

        SDL_UpdateWindowSurface(window);
        break;
    }

    if (eliminado) {
        std::cout << "perdiste, te llevas " << puntos << " puntos\n";
        elementospantalla = -1;
        eliminado = false;

        SDL_FillRect(superficieVentana, NULL, 0x000000);
        SDL_BlitSurface(background, NULL, superficieVentana, NULL);

        posInicial.x = 0; posInicial.y = 0; posInicial.w = 635; posInicial.h = 1011;
        posFinal.x = 460; posFinal.y = -10; posFinal.w = 635; posFinal.h = 1011;
        personaje1 = IMG_Load("assets/mensajerohistoria.png");
        SDL_BlitSurface(personaje1, &posInicial, superficieVentana, &posFinal);

        for (int i = puntos, x = 10, y = 50; i > 0; i--) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 500;
            posFinal.x = x; posFinal.y = y; posFinal.w = 500; posFinal.h = 500;
            imagen = IMG_Load("assets/corazon2.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            if (i != 3)
                x += 200;
            else {
                y = 200;
                x = 120;
            }
        }

        posInicial.x = 0; posInicial.y = 0; posInicial.w = 700; posInicial.h = 106;
        posFinal.x = -100; posFinal.y = 470; posFinal.w = 700; posFinal.h = 106;
        pulsaespacio = IMG_Load("assets/mensajecorazonesconseguidos.png");
        SDL_BlitSurface(pulsaespacio, &posInicial, superficieVentana, &posFinal);

        SDL_UpdateWindowSurface(window);
    }
}

//politica
void Game::miniJuegopolitica() {

    const int WIDTH = 1000;
    const int HEIGHT = 600;
    //const int SPRITE_SIZE = 120;
    const int SizeMessaje = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
    SDL_Renderer* renderizado; // render de ventana

    //Imagenes
    SDL_Surface* Fondo1;
    SDL_Texture* Tfondo;
    SDL_Surface* superficieVentana;
    SDL_Surface* prt1 = nullptr;
    SDL_Surface* prt2 = nullptr;
    SDL_Surface* prt3 = nullptr;
    SDL_Surface* prt4 = nullptr;
    SDL_Surface* prt5 = nullptr;
    SDL_Surface* prt6 = nullptr;
    SDL_Surface* prt7 = nullptr;
    SDL_Surface* prt8 = nullptr;
    SDL_Surface* prt9 = nullptr;
    SDL_Surface* prt10 = nullptr;
    SDL_Surface* prt11 = nullptr;
    SDL_Surface* prt12 = nullptr;
    SDL_Surface* prt13 = nullptr;
    SDL_Surface* prt14 = nullptr;
    SDL_Surface* prt15 = nullptr;
    SDL_Surface* prt16 = nullptr;
    SDL_Surface* prt17 = nullptr;
    SDL_Surface* prt18 = nullptr;
    SDL_Surface* prt21 = nullptr;

    SDL_Surface* prt31 = nullptr;


    SDL_Surface* right = nullptr;
    SDL_Surface* wrong = nullptr;


    SDL_Surface* win1 = nullptr;
    SDL_Surface* win2 = nullptr;
    SDL_Surface* win3 = nullptr;
    SDL_Surface* win4 = nullptr;
    SDL_Surface* win5 = nullptr;

    SDL_Surface* heart;

    SDL_Texture* Fondo;



    SDL_Surface* Continuar;




    SDL_Event EventoSalir;

    const Uint32* m;
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    SDL_Renderer* renderer;
    //evento para el toque de el vaso

    SDL_Event eleccion;
    int SPRITE_SIZE = 50;

    Ventana = SDL_CreateWindow("Politica", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
    SDL_FillRect(superficieVentana, NULL, Color);

    renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);



    Fondo1 = IMG_Load("Img/5COUNTDOWN.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/4COUNTDOWN.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);

    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/3COUNTDOWN.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/2COUNTDOWN.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);


    Fondo1 = IMG_Load("Img/1COUNTDOWN.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(500);

    Fondo1 = IMG_Load("Img/1puzzle.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Surface* numScore;
    SDL_Rect    gdPosScore;
    prt1 = IMG_Load("Img/1puzzle.png");
    prt2 = IMG_Load("Img/2puzzle.png");
    prt3 = IMG_Load("Img/3puzzle.png");
    prt4 = IMG_Load("Img/4puzzle.png");
    prt5 = IMG_Load("Img/5puzzle.png");


    prt21 = IMG_Load("Img/1.1puzzle.png");
    prt31 = IMG_Load("Img/1.2puzzle.png");
    prt3 = IMG_Load("Img/3(1).png");
    prt4 = IMG_Load("Img/4(1).png");
    prt5 = IMG_Load("Img/5(1).png");
    prt6 = IMG_Load("Img/6(1).png");
    prt7 = IMG_Load("Img/7(1).png");
    prt8 = IMG_Load("Img/8(1).png");
    prt9 = IMG_Load("Img/9(1).png");
    prt10 = IMG_Load("Img/10(1).png");
    prt11 = IMG_Load("Img/11(1).png");
    prt12 = IMG_Load("Img/12(1).png");
    prt13 = IMG_Load("Img/13(1).png");
    prt14 = IMG_Load("Img/14(1).png");
    prt15 = IMG_Load("Img/15(1).png");
    prt16 = IMG_Load("Img/16(1).png");
    prt17 = IMG_Load("Img/17(1).png");
    prt18 = IMG_Load("Img/18(1).png");

    right = IMG_Load("Img/right.png");
    wrong = IMG_Load("Img/wrong.png");

    win1 = IMG_Load("Img/1hrt.png");
    win2 = IMG_Load("Img/2hrt.png");
    win3 = IMG_Load("Img/3hrt.png");
    win4 = IMG_Load("Img/4hrt.png");
    win5 = IMG_Load("Img/5hrt.png");


    SDL_Surface* heart1 = NULL;

    int Puntuacion = 0;
    int bk = 0;
    int prtnum = 1;
    SDL_Surface* currentImg = prt1;
    SDL_Event evento;




    /*

    if (Puntuacion == 1) {
                               heart1 = IMG_Load("Img/5heart.png");

                               SDL_BlitSurface(heart1, NULL, superficieVentana, NULL);
                               SDL_UpdateWindowSurface(Ventana);
                           }*/

                           /*gdPosScore.x = 670; gdPosScore.y = 525; gdPosScore.w = SPRITE_SIZE; gdPosScore.h = SPRITE_SIZE;
                           if (Puntuacion == 1) {
                               heart1 = IMG_Load("Img/5heart.png");

                               SDL_BlitSurface(heart1, &rcInicial, superficieVentana, &gdPosScore);
                               SDL_UpdateWindowSurface(Ventana);
                           }*/


    while (isRunning) {
        gdPosScore.x = 18; gdPosScore.y = 18; gdPosScore.w = SPRITE_SIZE; gdPosScore.h = SPRITE_SIZE;

        if (Puntuacion == 1) {

            heart1 = IMG_Load("Img/1heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 2) {

            heart1 = IMG_Load("Img/2heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            // SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 3) {

            heart1 = IMG_Load("Img/3heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            // SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 4) {

            heart1 = IMG_Load("Img/4heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            // SDL_UpdateWindowSurface(Ventana);
        }
        if (Puntuacion == 5) {

            heart1 = IMG_Load("Img/5heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            // SDL_UpdateWindowSurface(Ventana);
        }

        SDL_UpdateWindowSurface(Ventana);
        if (prtnum == 1) {


            // SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento) != 0) {


                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 170 && evento.button.y <= 240) {



                    currentImg = prt21;

                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = right;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);



                        SDL_Delay(1000);

                        prtnum = 2;
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 290 && evento.button.y <= 351) {


                    currentImg = prt31;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 2;
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 407 && evento.button.y <= 471) {


                    currentImg = prt3;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;


                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 2;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 510 && evento.button.y <= 570) {


                    currentImg = prt4;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 2;
                    }

                }


            }

            //****************************************************************

        }

        if (prtnum == 2) {
            if (Puntuacion == 1) {

                heart1 = IMG_Load("Img/1heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 2) {

                heart1 = IMG_Load("Img/2heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 3) {

                heart1 = IMG_Load("Img/3heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 4) {

                heart1 = IMG_Load("Img/4heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 5) {

                heart1 = IMG_Load("Img/5heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 1) {

                heart1 = IMG_Load("Img/1heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 2) {

                heart1 = IMG_Load("Img/2heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 3) {

                heart1 = IMG_Load("Img/3heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 4) {

                heart1 = IMG_Load("Img/4heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 5) {

                heart1 = IMG_Load("Img/5heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }


            while (SDL_PollEvent(&evento) != 0) {
                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //  SDL_UpdateWindowSurface(Ventana);
                }

                if (bk == 0) {
                    Fondo1 = IMG_Load("Img/5COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    //SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 1;
                }


                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);
                if (evento.button.x >= 35 && evento.button.x <= 101 && evento.button.y >= 172 && evento.button.y <= 235) {

                    currentImg = prt5;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);

                        SDL_Delay(1000);

                        prtnum = 3;
                    }

                }
                if (evento.button.x >= 35 && evento.button.x <= 101 && evento.button.y >= 289 && evento.button.y <= 355) {


                    currentImg = prt6;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {
                        Puntuacion++;
                        currentImg = right;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 3;
                    }

                }
                if (evento.button.x >= 35 && evento.button.x <= 101 && evento.button.y >= 400 && evento.button.y <= 472) {


                    currentImg = prt7;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 3;
                        //pregunta2();
                    }

                }


            }
        }
        //****************************************************************
        if (prtnum == 3) {
            if (Puntuacion == 1) {

                heart1 = IMG_Load("Img/1heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //  SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 2) {

                heart1 = IMG_Load("Img/2heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 3) {

                heart1 = IMG_Load("Img/3heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 4) {

                heart1 = IMG_Load("Img/4heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 5) {

                heart1 = IMG_Load("Img/5heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento) != 0) {

                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //   SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                /*if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    SDL_UpdateWindowSurface(Ventana);
                }*/
                if (bk == 1) {
                    Fondo1 = IMG_Load("Img/5COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    //  SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    //  SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 2;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);


                if (evento.button.x >= 35 && evento.button.x <= 101 && evento.button.y >= 172 && evento.button.y <= 235) {

                    currentImg = prt8;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = wrong;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);

                        SDL_Delay(1000);

                        prtnum = 4;
                    }

                }
                if (evento.button.x >= 35 && evento.button.x <= 101 && evento.button.y >= 289 && evento.button.y <= 355) {


                    currentImg = prt9;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = right;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 4;
                    }

                }
                if (evento.button.x >= 35 && evento.button.x <= 101 && evento.button.y >= 400 && evento.button.y <= 472) {


                    currentImg = prt10;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 4;
                        //pregunta2();
                    }

                }


            }

        }


        //****************************************************************
        if (prtnum == 4) {
            if (Puntuacion == 1) {

                heart1 = IMG_Load("Img/1heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 2) {

                heart1 = IMG_Load("Img/2heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 3) {

                heart1 = IMG_Load("Img/3heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 4) {

                heart1 = IMG_Load("Img/4heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 5) {

                heart1 = IMG_Load("Img/5heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }
            while (SDL_PollEvent(&evento) != 0) {
                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //  SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (bk == 2) {
                    Fondo1 = IMG_Load("Img/5COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    //  SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    //   SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    //   SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 3;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);

                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 170 && evento.button.y <= 240) {



                    currentImg = prt11;

                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);



                        SDL_Delay(1000);

                        prtnum = 5;
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 290 && evento.button.y <= 351) {


                    currentImg = prt12;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 5;
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 407 && evento.button.y <= 471) {


                    currentImg = prt13;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = right;

                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 5;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 510 && evento.button.y <= 570) {


                    currentImg = prt14;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 5;
                    }

                }


            }

        }




        //****************************************************************
        if (prtnum == 5) {
            if (Puntuacion == 1) {

                heart1 = IMG_Load("Img/1heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 2) {

                heart1 = IMG_Load("Img/2heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 3) {

                heart1 = IMG_Load("Img/3heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 4) {

                heart1 = IMG_Load("Img/4heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                // SDL_UpdateWindowSurface(Ventana);
            }
            if (Puntuacion == 5) {

                heart1 = IMG_Load("Img/5heart.png");

                SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(heart1);
                //SDL_UpdateWindowSurface(Ventana);
            }
            while (SDL_PollEvent(&evento) != 0) {

                if (Puntuacion == 1) {

                    heart1 = IMG_Load("Img/1heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 2) {

                    heart1 = IMG_Load("Img/2heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 3) {

                    heart1 = IMG_Load("Img/3heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 4) {

                    heart1 = IMG_Load("Img/4heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    //SDL_UpdateWindowSurface(Ventana);
                }
                if (Puntuacion == 5) {

                    heart1 = IMG_Load("Img/5heart.png");

                    SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(heart1);
                    // SDL_UpdateWindowSurface(Ventana);
                }
                if (bk == 3) {
                    Fondo1 = IMG_Load("Img/5COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/4COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);

                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/3COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/2COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    // SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);


                    Fondo1 = IMG_Load("Img/1COUNTDOWN.png");
                    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
                    SDL_FreeSurface(Fondo1);
                    //SDL_UpdateWindowSurface(Ventana);
                    SDL_Delay(500);
                    bk = 4;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 170 && evento.button.y <= 240) {



                    currentImg = prt15;

                    if (evento.type == SDL_MOUSEBUTTONDOWN) {


                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);



                        SDL_Delay(1000);

                        prtnum = 6;
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 290 && evento.button.y <= 351) {


                    currentImg = prt16;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = right;
                        Puntuacion++;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 6;
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 407 && evento.button.y <= 471) {


                    currentImg = prt17;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;


                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 6;
                        //pregunta2();
                    }

                }
                if (evento.button.x >= 38 && evento.button.x <= 200 && evento.button.y >= 510 && evento.button.y <= 570) {


                    currentImg = prt18;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);

                        prtnum = 6;
                    }

                }


            }

        }

        //****************************************************************
        if (prtnum == 6) {

            if (Puntuacion == 1) {


                currentImg = win1;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }
            if (Puntuacion == 2) {


                currentImg = win2;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                // SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }  if (Puntuacion == 3) {


                currentImg = win3;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                //  SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }  if (Puntuacion == 4) {


                currentImg = win4;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                //  SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            } if (Puntuacion == 5) {


                currentImg = win5;
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                //   SDL_UpdateWindowSurface(Ventana);

                SDL_Delay(6000);



            }




        }



        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
        // SDL_UpdateWindowSurface(Ventana);
    }



    SDL_Surface* tmpsurface;


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
                    salir = 1;
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


    SDL_FreeSurface(prt1);
    SDL_FreeSurface(prt2);
    SDL_FreeSurface(prt3);
    SDL_FreeSurface(prt4);
    SDL_FreeSurface(prt5);

    prt1 = prt2 = prt3 = superficieVentana = nullptr;
    Ventana = nullptr;

    SDL_DestroyWindow(Ventana);

    SDL_Quit();



}

//mapa
void Game::Map()
{
    const int WIDTH = 1000;
    const int HEIGHT = 600;
    //const int SPRITE_SIZE = 120;
    const int SizeMessaje = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
    SDL_Renderer* renderizado; // render de ventana

    //Imagenes

    SDL_Surface* superficieVentana;
    SDL_Surface* prt1 = nullptr;
    SDL_Surface* prt2 = nullptr;
    SDL_Surface* prt3 = nullptr;
    SDL_Surface* prt4 = nullptr;
    SDL_Surface* prt5 = nullptr;
    SDL_Surface* prt6 = nullptr;
    SDL_Surface* prt7 = nullptr;
    SDL_Surface* prt8 = nullptr;

    SDL_Surface* heart;

    SDL_Texture* Fondo;

    SDL_Surface* heart1;
    SDL_Surface* heart2;
    SDL_Surface* heart3;
    SDL_Surface* heart4;
    SDL_Surface* heart5;

    SDL_Surface* Continuar;




    SDL_Event EventoSalir;

    const Uint32* m;
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    SDL_Renderer* renderer;
    //evento para el toque de el vaso

    SDL_Event eleccion;
    int SPRITE_SIZE = 50;

    Ventana = SDL_CreateWindow("Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
    SDL_FillRect(superficieVentana, NULL, Color);

    renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);




    prt1 = IMG_Load("Imgs/8.png");
    prt2 = IMG_Load("Imgs/9.png");
    prt3 = IMG_Load("Imgs/10.png");
    prt4 = IMG_Load("Imgs/11.png");
    prt5 = IMG_Load("Imgs/12.png");




    SDL_Rect    gdPosScore;
    //SDL_Surface* heart1 = NULL;

    int Puntuacion = 0;
    int bk = 0;
    int prtnum = 1;
    SDL_Surface* currentImg = prt1;
    SDL_Event evento;
    currentImg = prt1;
    gdPosScore.x = 18; gdPosScore.y = 18; gdPosScore.w = SPRITE_SIZE; gdPosScore.h = SPRITE_SIZE;
    while (isRunning) {
        if (vidas == 1) {
            heart1 = IMG_Load("Img/1heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (vidas == 2) {
            heart1 = IMG_Load("Img/2heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            // SDL_UpdateWindowSurface(Ventana);
        }
        if (vidas == 3) {
            heart1 = IMG_Load("Img/3heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (vidas == 4) {
            heart1 = IMG_Load("Img/4heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            //SDL_UpdateWindowSurface(Ventana);
        }
        if (vidas == 5) {
            heart1 = IMG_Load("Img/5heart.png");

            SDL_BlitSurface(heart1, NULL, superficieVentana, &gdPosScore);
            SDL_FreeSurface(heart1);
            // SDL_UpdateWindowSurface(Ventana);
        }

        SDL_UpdateWindowSurface(Ventana);



        while (SDL_PollEvent(&evento) != 0) {


            if (evento.button.x >= 703 && evento.button.x <= 825 && evento.button.y >= 12 && evento.button.y <= 156) {



                currentImg = prt5;

                if (evento.type == SDL_MOUSEBUTTONDOWN) {



                }

            }
            if (evento.button.x >= 326 && evento.button.x <= 586 && evento.button.y >= 29 && evento.button.y <= 270) {


                currentImg = prt4;
                if (evento.type == SDL_MOUSEBUTTONDOWN) {

                    /*    currentImg = prt5;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(2000);

                        prtnum = 2;*/
                }

            }
            if (evento.button.x >= 79 && evento.button.x <= 144 && evento.button.y >= 375 && evento.button.y <= 497) {


                currentImg = prt3;
                if (evento.type == SDL_MOUSEBUTTONDOWN) {


                }

            }
            if (evento.button.x >= 666 && evento.button.x <= 850 && evento.button.y >= 317 && evento.button.y <= 416) {


                currentImg = prt2;
                if (evento.type == SDL_MOUSEBUTTONDOWN) {


                }

            }
            /* if (evento.button.x >= 680 && evento.button.x <= 871 && evento.button.y >= 34 && evento.button.y <= 124) {


                 currentImg = prt5;
                 if (evento.type == SDL_MOUSEBUTTONDOWN) {


                 }

             }*/


        }







        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);

    }



    SDL_Surface* tmpsurface;


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
                    salir = 1;
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


    SDL_FreeSurface(prt1);
    SDL_FreeSurface(prt2);
    SDL_FreeSurface(prt3);
    SDL_FreeSurface(prt4);
    SDL_FreeSurface(prt5);

    prt1 = prt2 = prt3 = superficieVentana = nullptr;
    Ventana = nullptr;

    SDL_DestroyWindow(Ventana);

    SDL_Quit();


}

//eleccion de bandos
void Game::bandosCoinFlip()
{

    const int WIDTH = 1000;
    const int HEIGHT = 600;
    //const int SPRITE_SIZE = 120;
    const int SizeMessaje = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
    SDL_Renderer* renderizado; // render de ventana

    //Imagenes
    SDL_Surface* Fondo1;
    SDL_Texture* Tfondo;
    SDL_Surface* superficieVentana;
    SDL_Surface* coin1 = nullptr;
    SDL_Surface* coin2 = nullptr;
    SDL_Surface* coin3 = nullptr;
    SDL_Surface* coin4 = nullptr;
    SDL_Surface* coin5 = nullptr;
    SDL_Surface* coin6 = nullptr;
    SDL_Surface* coin7 = nullptr;
    SDL_Surface* coin8 = nullptr;
    SDL_Surface* coin9 = nullptr;
    SDL_Surface* currentImag = nullptr;

    SDL_Surface* Empirista = nullptr;
    SDL_Surface* Racional = nullptr;


    SDL_Surface* win1 = nullptr;
    SDL_Surface* win2 = nullptr;
    SDL_Surface* win3 = nullptr;
    SDL_Surface* win4 = nullptr;
    SDL_Surface* win5 = nullptr;

    SDL_Surface* heart;
    SDL_Texture* Fondo;
    SDL_Surface* Continuar;
    SDL_Event EventoSalir;

    const Uint32* m;
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    SDL_Renderer* renderer;
    //evento para el toque de el vaso

    SDL_Event eleccion;
    int SPRITE_SIZE = 50;

    Ventana = SDL_CreateWindow("Coin Toss", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
    SDL_FillRect(superficieVentana, NULL, Color);

    renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);



    Fondo1 = IMG_Load("Imgs/1.png");
    SDL_BlitSurface(Fondo1, NULL, superficieVentana, NULL);
    SDL_FreeSurface(Fondo1);
    SDL_UpdateWindowSurface(Ventana);
    SDL_Delay(5000);



    SDL_Surface* numScore;
    SDL_Rect    gdPosScore;
    coin1 = IMG_Load("Imgs/4.png");
    coin2 = IMG_Load("Imgs/5.png");
    coin3 = IMG_Load("Imgs/6.png");
    coin4 = IMG_Load("Imgs/7.png");
    coin5 = IMG_Load("Imgs/coin1.png");
    coin6 = IMG_Load("Imgs/coin2.png");
    coin7 = IMG_Load("Imgs/coin3.png");
    coin8 = IMG_Load("Imgs/coin4.png");
    coin9 = IMG_Load("Imgs/coin5.png");

    Empirista = IMG_Load("Imgs/2.png");
    Racional = IMG_Load("Imgs/3.png");




    SDL_Surface* heart1 = NULL;

    SDL_Event evento;




    srand(time(0));

    unsigned seed = time(0);
    srand(seed);
    int numRandom = rand();
    std::cout << numRandom << "   *    ";
    numRandom = numRandom % 2;
    std::cout << numRandom;

    if (0 == numRandom) {

        SDL_BlitSurface(coin1, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin1);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(coin5, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin5);

        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(coin6, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin6);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(coin7, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin7);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);

        SDL_BlitSurface(coin8, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin8);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);

        SDL_BlitSurface(coin9, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin9);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);
        coin5 = IMG_Load("Imgs/coin1.png");
        coin6 = IMG_Load("Imgs/coin2.png");
        coin7 = IMG_Load("Imgs/coin3.png");
        coin8 = IMG_Load("Imgs/coin4.png");
        coin9 = IMG_Load("Imgs/coin5.png");

        SDL_BlitSurface(coin8, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin8);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);
        SDL_BlitSurface(coin7, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin7);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);

        SDL_BlitSurface(coin6, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin6);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(Empirista, NULL, superficieVentana, NULL);
        SDL_FreeSurface(Empirista);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(1500);
        bando = 1;
    }
    else {
        coin1 = IMG_Load("Imgs/4.png");
        bando = 2;

        // coin2 = IMG_Load("Imgs/5.png");
        coin3 = IMG_Load("Imgs/6.png");
        coin4 = IMG_Load("Imgs/7.png");

        coin5 = IMG_Load("Imgs/coin1.png");
        coin6 = IMG_Load("Imgs/coin2.png");
        coin7 = IMG_Load("Imgs/coin3.png");
        coin8 = IMG_Load("Imgs/coin4.png");
        coin9 = IMG_Load("Imgs/coin5.png");
        SDL_BlitSurface(coin1, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin1);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(coin5, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin5);

        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(coin6, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin6);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);



        SDL_BlitSurface(coin7, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin7);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);

        SDL_BlitSurface(coin8, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin8);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);
        SDL_BlitSurface(coin9, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin9);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);

        coin5 = IMG_Load("Imgs/coin1.png");
        coin6 = IMG_Load("Imgs/coin2.png");
        coin7 = IMG_Load("Imgs/coin3.png");
        coin8 = IMG_Load("Imgs/coin4.png");
        coin9 = IMG_Load("Imgs/coin5.png");

        SDL_BlitSurface(coin8, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin8);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);
        SDL_BlitSurface(coin7, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin7);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);

        SDL_BlitSurface(coin6, NULL, superficieVentana, NULL);
        SDL_FreeSurface(coin6);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(50);


        SDL_BlitSurface(Racional, NULL, superficieVentana, NULL);
        SDL_FreeSurface(Racional);
        SDL_UpdateWindowSurface(Ventana);
        SDL_Delay(1500);
    }





    SDL_Surface* tmpsurface;


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
                    salir = 1;
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




    superficieVentana = nullptr;
    Ventana = nullptr;

    SDL_DestroyWindow(Ventana);

    SDL_Quit();





}

SDL_Surface* Game::Vidas(int vidas)
{
    SDL_Surface* Vidas;

    if (vidas == 1) {
        return Vidas = IMG_Load("CVerdad/C1.png");
    }
    else if (vidas == 2) 
    {
        return Vidas = IMG_Load("CVerdad/C2.png");
    }
    else if (vidas == 3)
    {
        return Vidas = IMG_Load("CVerdad/C3.png");
    }
    else if (vidas == 4)
    {
        return Vidas = IMG_Load("CVerdad/C4.png");
    }
    else if (vidas == 5)
    {
        return Vidas = IMG_Load("CVerdad/C5.png");
    }

}

//Combate por la verdad
void Game::CombateporlaVerdad(int vidas)
{
   
    const int WIDTH = 1000; //Ancho de pantalla
    const int HEIGHT = 564; // altura de pantallla
    const int SPRITE_SIZE = 600; //TAMA;O D ELA ORCA
    const int SizeMessaje = 600; // tama�o de mensaje de carta eleguida

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;


    //Imagenes
    SDL_Surface* Fondo;
    SDL_Surface* superficieVentana;

    SDL_Surface* CaballoU;
    SDL_Surface* CaballoIA;

    SDL_Surface* Corazones;



    //envento para salir
    SDL_Event EventoSalir;

    int vida = vidas;
    int vidaIa = 3;
    int salir = 0;
    //POsiciones de las imagenes
    SDL_Rect    rcInicial;
    SDL_Rect    gdFinal;


    //evento 
    SDL_Event Event;

    Ventana = SDL_CreateWindow("Combate por la verdad", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    if (Ventana == NULL)
    {
        std::cout << "Error";

    }
    else
    {

        rcInicial.x = 0; rcInicial.y = 0; rcInicial.w = SPRITE_SIZE; rcInicial.h = SPRITE_SIZE;

        gdFinal.x = 0; gdFinal.y = 0; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;

        Fondo = IMG_Load("CVerdad/Fondo.png");
        SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

        Corazones = Vidas(vida);

        gdFinal.x = 4; gdFinal.y = 270;
        CaballoU = IMG_Load("CVerdad/CaballoU1.png");

        gdFinal.x = 700; gdFinal.y = 270;
        CaballoIA = IMG_Load("CVerdad/CaballoR1.png");
        gdFinal.x = 0; gdFinal.y = 0;
     

        SDL_FreeSurface(Fondo);



        SDL_UpdateWindowSurface(Ventana);
        int p = 0;
        int pregunta = 0;
        int correctas = 0;
        std::string contra = "";
        std::string verda = "hola";

        while (p == 0) {
            //std::cout << "i";
            if (SDL_PollEvent(&Event))
            {
                //std::cout << "o";
                if (pregunta == 0) {
                    switch (Event.type)
                    {
                       
                        //std::cout << "o2";
                    case SDL_QUIT:
                        //std::cout << "sal";
                        p = 1;
                        salir = 1;
                        break;
                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_y:
                            std::cout << "Y";
                            Fondo = IMG_Load("CVerdad/3.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(1000);
                            Fondo = IMG_Load("CVerdad/2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(1000);
                            Fondo = IMG_Load("CVerdad/1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(500);

                            //musicaHallowedBeThyName();

                            Fondo = IMG_Load("CVerdad/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 850;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 4; gdFinal.y = 260;
                            SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 730; gdFinal.y = 260;
                            SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);
                           

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(CaballoU);
                            SDL_FreeSurface(CaballoIA);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;
                            std::cout << "\n\ncontr; " << contra;
                            

                            if (verda.compare(contra)) 
                            {
                                std::cout << "Zi";
                            }
                            else 
                            {
                                std::cout << "No";
                            }

                            break;

                        case SDLK_n:
                            std::cout << "N";

                            SDL_Quit;
                            Map();
                            break;
                        default:
                            
                            std::cout << "\nEvent.key.keysym.unused - " << Event.key.keysym.scancode;
                            std::cout << SDL_GetKeyName(Event.key.keysym.sym);

                            
                            contra += SDL_GetKeyName(Event.key.keysym.sym);
                            
                            break;
                        }

                    }
                }else if (pregunta == 1)
                {
                    gdFinal.x = 0; gdFinal.y = 0;

                    switch (Event.type)
                    {
                    case SDL_QUIT:
                        salir = 1;
                        p = 1;
                        break;
                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_b:
                            //vidas siguen siendo iguales
                            //el caballo se acerca
                           
                            
                            std::cout << "Nada";
                            correctas++;
                            Fondo = IMG_Load("CVerdad/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            Corazones = Vidas(vida);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 200; gdFinal.y = 260;
                            CaballoU = IMG_Load("CVerdad/CaballoU.png");
                            SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 730; gdFinal.y = 260;
                            CaballoIA = IMG_Load("CVerdad/CaballoR1.png");
                            SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 900; gdFinal.y = 0;
                            std::cout << "-1IA b";
                            vidaIa -= 1;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballoU);
                            SDL_FreeSurface(CaballoIA);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;

                            break;

                        default:
                            vida -= 1;
                            Corazones = Vidas(vida);
                            std::cout << "a";

                            Fondo = IMG_Load("CVerdad/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            
                            gdFinal.x = 4; gdFinal.y = 260;
                            CaballoU = IMG_Load("CVerdad/CaballoU1.png");
                            SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                            CaballoIA = IMG_Load("CVerdad/CaballoR2.png");
                            gdFinal.x = 600; gdFinal.y = 260;
                            SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 850; gdFinal.y = 0;
                            std::cout << "IA b "<<vidaIa;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(CaballoU);
                            SDL_FreeSurface(CaballoIA);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;
                            break;
                        }


                    }
                }else if (pregunta == 2)
                {
                    gdFinal.x = 0; gdFinal.y = 0;

                    switch (Event.type)
                    {
                    case SDL_QUIT:
                        salir = 1;
                        p = 1;
                        break;
                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_a:
                            //vidas siguen siendo iguales
                            //el caballo se acerca

                            Fondo = IMG_Load("CVerdad/Pregunta3.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            Corazones = Vidas(vida);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);
                            correctas++;
                            if (correctas > 1) {
                                gdFinal.x = 730; gdFinal.y = 270;
                                CaballoIA = IMG_Load("CVerdad/CaballoR1.png");
                                SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 400; gdFinal.y = 260;
                                CaballoU = IMG_Load("CVerdad/CaballoU1.png");
                                SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                            }
                            else 
                            {
                                gdFinal.x = 200; gdFinal.y = 260;
                                CaballoU = IMG_Load("CVerdad/CaballoU1.png");
                                SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                                CaballoIA = IMG_Load("CVerdad/CaballoR2.png");
                                gdFinal.x = 600; gdFinal.y = 260;
                                SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);
                               
                            }


                            gdFinal.x = 900;  gdFinal.y = 0;
                            std::cout << "-1IA a";
                            vidaIa -= 1;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(CaballoIA);
                            SDL_FreeSurface(CaballoU);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;

                            break;
                        default:
                            vida -= 1;
                            Corazones = Vidas(vida);
                            //SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                           
                            Fondo = IMG_Load("CVerdad/Pregunta3.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            //SDL_FreeSurface(Corazones);

                            if (correctas == 1) {

                                gdFinal.x = 600; gdFinal.y = 260;
                                CaballoIA = IMG_Load("CVerdad/CaballoR1.png");
                                SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);

                                gdFinal.x = 200; gdFinal.y = 260;
                                CaballoU = IMG_Load("CVerdad/CaballoU1.png");
                                SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                            }
                            else
                            {
                                gdFinal.x = 4; gdFinal.y = 260;
                                CaballoU = IMG_Load("CVerdad/CaballoU1.png");
                                SDL_BlitSurface(CaballoU, &rcInicial, superficieVentana, &gdFinal);

                                CaballoIA = IMG_Load("CVerdad/CaballoR2.png");
                                gdFinal.x = 300; gdFinal.y = 260;
                                SDL_BlitSurface(CaballoIA, &rcInicial, superficieVentana, &gdFinal);

                            }


                            gdFinal.x = 900; gdFinal.y = 0;
                            std::cout << "\n\nIA a"<< vidaIa;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballoIA);
                            SDL_FreeSurface(CaballoU);
                            SDL_UpdateWindowSurface(Ventana);

                            pregunta++;
                            break;
                        }


                    }
                }else if (pregunta == 3)
                {
                    switch (Event.type)
                    {
                    case SDL_QUIT:
                        salir = 1;
                        p = 1;
                        break;
                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                            
                        case SDLK_c:
                            //vidas siguen siendo iguales
                            //el caballo se acerca
                            correctas++;

                            if (correctas > 1) {
                                Fondo = IMG_Load("CVerdad/10.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/11.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/12.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/13.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/14.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/15.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/16.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/17.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/18.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/19.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/20.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/21.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/Ganador.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);

                                if (bando == 1) 
                                {
                                    musicaHallowedBeThyName();
                                }
                                else 
                                {
                                    musicaCarminaBurana();
                                }

                                std:: cout << "Se termino";
                                p = 1;
                            }
                            else 
                            {
                                Fondo = IMG_Load("CVerdad/24.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/25.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/26.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/27.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/28.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/29.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/30.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/31.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/32.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/33.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/34.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                              
                                Fondo = IMG_Load("CVerdad/Perdiste.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                if (bando == 1)
                                {
                                    musicaCarminaBurana();
                                }
                                else
                                {
                                    musicaHallowedBeThyName();
                                }

                                p = 1;
                                
                            }

                            break;
                        default:
                           
                            if (correctas > 1) {
                                Fondo = IMG_Load("CVerdad/10.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/11.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/12.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/13.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/14.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/15.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/16.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/17.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/18.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/19.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/20.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/21.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/Ganador.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);

                                if (bando == 1)
                                {
                                   
                                    musicaHallowedBeThyName();
                                }
                                else
                                { 
                                    musicaCarminaBurana();
                                }


                                p = 1;
                            }
                            else
                            {
                                Fondo = IMG_Load("CVerdad/24.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/25.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/26.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/27.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/28.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/29.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/30.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/31.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/32.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/33.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);

                                Fondo = IMG_Load("CVerdad/34.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(500);


                                Fondo = IMG_Load("CVerdad/Perdiste.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                if (bando == 1)
                                {
                                    musicaCarminaBurana();
                                    
                                }
                                else
                                {
                                    musicaHallowedBeThyName();
                                }
                                p = 1;

                            }
                            break;
                        }


                    }

                }
            }

        }
        SDL_UpdateWindowSurface(Ventana);

        while (!salir)
        {
            if (SDL_PollEvent(&EventoSalir))
            {
                switch (EventoSalir.type)
                {
                case SDL_QUIT:
                    salir = 1;

                    break;

                }
            }
        }

        SDL_FreeSurface(superficieVentana);
        SDL_DestroyWindow(Ventana);
        SDL_Quit();
    }
}

//Musica ganador
void Game::musicaHallowedBeThyName()
{
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    SDL_LoadWAV("HallowedBeThy.wav", &wavSpec, &wavBuffer, &wavLength);

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

}

void Game::musicaCarminaBurana()
{
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    SDL_LoadWAV("CarminaBurana.wav", &wavSpec, &wavBuffer, &wavLength);

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

}



//combate del sujeto
void Game::combateSujeto()
{
    ventanaCombateSujeto("Combate Sujeto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, false);
    elementosCombateSujeto();
    while (true)
        eventosCombateSujeto();
}

void Game::ventanaCombateSujeto(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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

void Game::elementosCombateSujeto()
{
    //fondo
    superficieVentana = SDL_GetWindowSurface(window);

    background = IMG_Load("assets/paisaje.png");
    SDL_BlitSurface(background, NULL, superficieVentana, NULL);

    //jugadores
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 51; posInicial.h = 100;
    posFinal.x = J1posx; posFinal.y = J1posy; posFinal.w = 51; posFinal.h = 100;
    imagen = IMG_Load("assets/J1Sujeto.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    posFinal.x = J2posx; posFinal.y = J2posy; posFinal.w = 51; posFinal.h = 100;
    imagen = IMG_Load("assets/J2Sujeto.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    //puentes
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 300; posInicial.h = 52;
    posFinal.x = 170; posFinal.y = 190; posFinal.w = 300; posFinal.h = 52;
    imagen = IMG_Load("assets/puente.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    posFinal.x = 490; posFinal.y = 190; posFinal.w = 300; posFinal.h = 52;
    imagen = IMG_Load("assets/puente.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    //torres
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 500; posInicial.h = 500;
    posFinal.x = -120; posFinal.y = 100; posFinal.w = 500; posFinal.h = 500;
    imagen = IMG_Load("assets/torre.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    posFinal.x = 250; posFinal.y = 100; posFinal.w = 500; posFinal.h = 500;
    imagen = IMG_Load("assets/torre.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    posFinal.x = 600; posFinal.y = 100; posFinal.w = 500; posFinal.h = 500;
    imagen = IMG_Load("assets/torre.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    //corona
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 100; posInicial.h = 65;
    posFinal.x = 450; posFinal.y = 80; posFinal.w = 100; posFinal.h = 65;
    imagen = IMG_Load("assets/corona.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    //preguntas
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 689; posInicial.h = 196;
    posFinal.x = 160; posFinal.y = 280; posFinal.w = 689; posFinal.h = 196;
    if (preguntaCS == 1) {
        imagen = IMG_Load("assets/preguntasCS1.png");
        SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);
    }
    else if (preguntaCS == 2) {
        imagen = IMG_Load("assets/preguntasCS2.png");
        SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);
    }
    else if (preguntaCS == 3) {
        imagen = IMG_Load("assets/preguntasCS3.png");
        SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);
    }
    else if (preguntaCS == 4) {
        if (J1movimiento == J2movimiento)
            std::cout << "J1 y J2 empataron.\n";
        else if (J1movimiento > J2movimiento)
            std::cout << "J1 fue el ganador.\n";
        else
            std::cout << "J2 fue el ganador.\n";
    }


    SDL_UpdateWindowSurface(window);
}

void Game::eventosCombateSujeto() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        //cerrar ventana
    case SDL_QUIT:
        exit(1);
        break;
    case SDL_MOUSEBUTTONDOWN:
        int cursorx = event.motion.x, cursory = event.motion.y;

        //seleccion de respuesta
        if (cursorx > 175 && cursorx < 465 && cursory > 360 && cursory < 407) {
            std::cout << "presionaste A\n";
            if (turno == 1) {
                switch (preguntaCS) {
                case 1:
                    J1RespuestaCorrecta = true;
                    break;
                case 2:
                    J1RespuestaCorrecta = false;
                    break;
                case 3:
                    J1RespuestaCorrecta = false;
                    break;
                }
                turno++;
            }
            else if (turno == 2) {
                switch (preguntaCS) {
                case 1:
                    J2RespuestaCorrecta = true;
                    break;
                case 2:
                    J2RespuestaCorrecta = false;
                    break;
                case 3:
                    J2RespuestaCorrecta = false;
                    break;
                }
                turno++;
            }
        }
        if (cursorx > 540 && cursorx < 835 && cursory > 360 && cursory < 410) {
            std::cout << "presionaste B\n";
            if (turno == 1) {
                switch (preguntaCS) {
                case 1:
                    J1RespuestaCorrecta = false;
                    break;
                case 2:
                    J1RespuestaCorrecta = true;
                    break;
                case 3:
                    J1RespuestaCorrecta = false;
                    break;
                }
                turno++;
            }
            else if (turno == 2) {
                switch (preguntaCS) {
                case 1:
                    J2RespuestaCorrecta = false;
                    break;
                case 2:
                    J2RespuestaCorrecta = true;
                    break;
                case 3:
                    J2RespuestaCorrecta = false;
                    break;
                }
                turno++;
            }
        }
        if (cursorx > 175 && cursorx < 465 && cursory > 425 && cursory < 470) {
            std::cout << "presionaste C\n";
            if (turno == 1) {
                switch (preguntaCS) {
                case 1:
                    J1RespuestaCorrecta = false;
                    break;
                case 2:
                    J1RespuestaCorrecta = false;
                    break;
                case 3:
                    J1RespuestaCorrecta = true;
                    break;
                }
                turno++;
            }
            else if (turno == 2) {
                switch (preguntaCS) {
                case 1:
                    J2RespuestaCorrecta = false;
                    break;
                case 2:
                    J2RespuestaCorrecta = false;
                    break;
                case 3:
                    J2RespuestaCorrecta = true;
                    break;
                }
                turno++;
            }
        }
        if (cursorx > 540 && cursorx < 835 && cursory > 425 && cursory < 470) {
            std::cout << "presionaste D\n";
            if (turno == 1) {
                switch (preguntaCS) {
                case 1:
                    J1RespuestaCorrecta = false;
                    break;
                case 2:
                    J1RespuestaCorrecta = false;
                    break;
                case 3:
                    J1RespuestaCorrecta = false;
                    break;
                }
                turno++;
            }
            else if (turno == 2) {
                switch (preguntaCS) {
                case 1:
                    J2RespuestaCorrecta = false;
                    break;
                case 2:
                    J2RespuestaCorrecta = false;
                    break;
                case 3:
                    J2RespuestaCorrecta = false;
                    break;
                }
                turno++;
            }
        }

        //avanzar jugadores si respondieron bien
        if (turno == 3) {
            if (J1RespuestaCorrecta) {
                std::cout << "jugador 1 respondio bien, avanza\n";
                if (J1movimiento == 0) {
                    J1posx += 140;
                    J1posy += 20;
                }
                else if (J1movimiento == 1)
                    J1posx += 110;
                else {
                    J1posx += 80;
                    J1posy -= 20;
                }
                J1movimiento++;
            }
            if (J2RespuestaCorrecta) {
                std::cout << "jugador 2 respondio bien, avanza\n";
                if (J2movimiento == 0) {
                    J2posx -= 130;
                    J2posy += 20;
                }
                else if (J2movimiento == 1)
                    J2posx -= 100;
                else {
                    J2posx -= 60;
                    J2posy -= 20;
                }
                J2movimiento++;
            }

            turno = 1;
            preguntaCS++;
            SDL_FillRect(superficieVentana, NULL, 0x000000);
            elementosCombateSujeto();
        }

        break;
    }
}

//Combate trancendental
void Game::CombateTrancendental(int vidas)
{

    const int WIDTH = 1000; //Ancho de pantalla
    const int HEIGHT = 564; // altura de pantallla
    const int SPRITE_SIZE = 900; //TAMA;O D ELA ORCA
    const int SizeMessaje = 900; // tama�o de mensaje de carta eleguida

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;


    //Imagenes
    SDL_Surface* Fondo;
    SDL_Surface* superficieVentana;

    SDL_Surface* CaballeroU;
    SDL_Surface* CaballeroIA;

    SDL_Surface* Corazones;



    //envento para salir
    SDL_Event EventoSalir;

    int vida = vidas;
    int vidaIa = 3;
    int salir = 0;
    //POsiciones de las imagenes
    SDL_Rect    rcInicial;
    SDL_Rect    gdFinal;


    //evento 
    SDL_Event Event;

    Ventana = SDL_CreateWindow("Combate por la verdad", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    if (Ventana == NULL)
    {
        std::cout << "Error";

    }
    else
    {

        rcInicial.x = 0; rcInicial.y = 0; rcInicial.w = SPRITE_SIZE; rcInicial.h = SPRITE_SIZE;

        gdFinal.x = 0; gdFinal.y = 0; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;

        Fondo = IMG_Load("UltimoC/Fondo.png");
        SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

        Corazones = Vidas(vida);

        gdFinal.x = 4; gdFinal.y = 270;
        CaballeroU = IMG_Load("UltimoC/U00.png");

        gdFinal.x = 700; gdFinal.y = 270;
        CaballeroIA = IMG_Load("UltimoC/I0.png");
        gdFinal.x = 0; gdFinal.y = 0;


        SDL_FreeSurface(Fondo);



        SDL_UpdateWindowSurface(Ventana);
        int p = 0;
        int pregunta = 0;
        int correctas = 0;


        while (p == 0) {
            //std::cout << "i";
            if (SDL_PollEvent(&Event))
            {

                if (pregunta == 0) {
                    switch (Event.type)
                    {
                        //std::cout << "o2";
                    case SDL_QUIT:
                        //std::cout << "sal";
                        p = 1;
                        salir = 1;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        std::cout << "x = " << Event.motion.x;
                        std::cout << "\ny = " << Event.motion.y;
                        int x = Event.motion.x;
                        int y = Event.motion.y;
                        if (x >= 462 && y >= 244 && x <= 554 && y <= 315) {
                            std::cout << "Si";

                            Fondo = IMG_Load("UltimoC/1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/3.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(200);

                            //musicaHallowedBeThyName();

                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 850;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 70; gdFinal.y = 220;
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);


                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_FreeSurface(CaballeroU);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;
                            break;

                        }else if (x >= 462 && y >= 244 && x <= 554 && y <= 315) {
                            
                            std::cout << "N";

                            SDL_Quit;
                            Map();
                        }


                    }
                }
                else if (pregunta == 1)
                {
                    gdFinal.x = 0; gdFinal.y = 0;

                    switch (Event.type)
                    {
                    case SDL_QUIT:
                        salir = 1;
                        p = 1;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        std::cout << "\nx = " << Event.motion.x;
                        std::cout << "\ny = " << Event.motion.y;
                        int x = Event.motion.x;
                        int y = Event.motion.y;
                        //vidas siguen siendo iguales
                        //el caballo se acerca

                        if (x >= 294 && y >= 517 && x <= 524 && y <= 557) {

                            std::cout << "Nada";
                            correctas++;


                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            // U1 - I1--------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 110; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U1.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U2--------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 160; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U2.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U3--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 220; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U3.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U4---------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 290; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U4.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U5 ------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 280; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U5.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U6--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 170; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U6.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U7--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 90; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U7.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //-------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 50; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(200);
                            //-------------------------------------------

                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            Corazones = Vidas(vida);
                            gdFinal.x = 0; gdFinal.y = 0;
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);


                            gdFinal.x = 900; gdFinal.y = 0;
                            vidaIa -= 1;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;
                            break;
                        }
                        else if (x < 294 && y > 517 || x > 524 && y > 517) {



                            vida -= 1;
                            Corazones = Vidas(vida);
                            std::cout << "a";

                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            // U1 - I1--------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 520; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I2.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U2--------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 490; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I3.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U3--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 370; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I4.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U4---------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 380; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I5.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U5 ------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 450; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I6.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U6--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 490; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I7.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U7--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 520; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I8.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U8----------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta1.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(1000);

                            //U9-------------------------------------------------------------------


                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            Corazones = Vidas(vida);
                            gdFinal.x = 0; gdFinal.y = 0;
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);



                            gdFinal.x = 850; gdFinal.y = 0;
                            std::cout << vidaIa;
                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;
                            break;
                        }

                    }
                }
                else if (pregunta == 2)
                {
                    gdFinal.x = 0; gdFinal.y = 0;

                    switch (Event.type)
                    {
                    case SDL_QUIT:
                        salir = 1;
                        p = 1;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        std::cout << "\nx = " << Event.motion.x;
                        std::cout << "\ny = " << Event.motion.y;
                        int x = Event.motion.x;
                        int y = Event.motion.y;
                        //vidas siguen siendo iguales
                        //el caballo se acerca
                        if (x >= 490 && y >= 517 && x <= 666 && y <= 557) {
                            std::cout << "Nada";
                            correctas++;



                            // U1 - I1--------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 110; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U1.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U2--------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 160; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U2.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U3--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 220; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U3.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U4---------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 290; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U4.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U5 ------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 280; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U5.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U6--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 170; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U6.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U7--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 90; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U7.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //-------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 50; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(1000);
                            //-------------------------------------------

                            Fondo = IMG_Load("UltimoC/Pregunta3.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            Corazones = Vidas(vida);
                            gdFinal.x = 0; gdFinal.y = 0;
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);


                            vidaIa -= 1;
                            if (vidaIa == 2)
                            {
                                gdFinal.x = 900; gdFinal.y = 0;
                            }
                            else if (vidaIa == 1)
                            {
                                gdFinal.x = 950; gdFinal.y = 0;
                            }
                            else if (vidaIa == 3)
                            {
                                gdFinal.x = 850; gdFinal.y = 0;
                            }

                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;

                            break;


                        }
                        else if (x < 490 && y > 517 || x > 666 && y < 517) {

                            vida -= 1;
                            Corazones = Vidas(vida);
                            std::cout << "a";

                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            // U1 - I1--------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 520; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I2.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U2--------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 490; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I3.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U3--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 370; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I4.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U4---------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 380; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I5.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U5 ------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 450; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I6.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U6--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 490; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I7.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U7--------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 520; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I8.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);

                            //U8----------------------------------------------------------------------
                            SDL_Delay(200);
                            Fondo = IMG_Load("UltimoC/Pregunta2.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            gdFinal.x = 190; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U0.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 550; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I1.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Fondo);
                            SDL_FreeSurface(CaballeroU);
                            SDL_FreeSurface(CaballeroIA);
                            SDL_UpdateWindowSurface(Ventana);
                            SDL_Delay(1000);

                            //U9-------------------------------------------------------------------


                            Fondo = IMG_Load("UltimoC/Pregunta3.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                            Corazones = Vidas(vida);
                            gdFinal.x = 0; gdFinal.y = 0;
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);
                            SDL_FreeSurface(Corazones);

                            gdFinal.x = 70; gdFinal.y = 220;
                            CaballeroU = IMG_Load("UltimoC/U00.png");
                            SDL_BlitSurface(CaballeroU, &rcInicial, superficieVentana, &gdFinal);

                            gdFinal.x = 670; gdFinal.y = 220;
                            CaballeroIA = IMG_Load("UltimoC/I0.png");
                            SDL_BlitSurface(CaballeroIA, &rcInicial, superficieVentana, &gdFinal);


                            if (vidaIa == 2)
                            {
                                gdFinal.x = 900; gdFinal.y = 0;
                            }
                            else if (vidaIa == 1)
                            {
                                gdFinal.x = 950; gdFinal.y = 0;
                            }
                            else if (vidaIa == 3)
                            {
                                gdFinal.x = 850; gdFinal.y = 0;
                            }

                            Corazones = Vidas(vidaIa);
                            SDL_BlitSurface(Corazones, &rcInicial, superficieVentana, &gdFinal);

                            SDL_FreeSurface(Corazones);
                            SDL_FreeSurface(Fondo);
                            SDL_UpdateWindowSurface(Ventana);
                            pregunta++;
                            break;



                        }


                    }
                }
                else if (pregunta == 3)
                {

                    switch (Event.type)
                    {
                     case SDL_QUIT:
                        salir = 1;
                        p = 1;
                        break;
                        case SDL_MOUSEBUTTONDOWN:
                        std::cout << "\nx = " << Event.motion.x;
                        std::cout << "\ny = " << Event.motion.y;
                        int x = Event.motion.x;
                        int y = Event.motion.y;
                        //vidas siguen siendo iguales
                        //el caballo se acerca
                        if (x >= 767 && y >= 517 && x <= 944 && y <= 557) {
                            std::cout << "Nada";
                            correctas++;
                            std::wcout << correctas;
                            if (correctas > 1) {
                                Fondo = IMG_Load("UltimoC/G1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G4.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G5.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G6.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G7.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G8.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G9.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G10.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G11.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G12.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G13.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G14.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G15.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G16.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G17.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G18.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G19.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G20.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G21.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G22.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G23.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G24.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G25.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G26.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G27.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/Ganador.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);



                                if (bando == 1)
                                {
                                    musicaHallowedBeThyName();
                                }
                                else
                                {
                                    musicaCarminaBurana();
                                }

                                std::cout << "Se termino";
                                p = 1;
                            }
                            else
                            {
                                Fondo = IMG_Load("UltimoC/P1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P4.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P5.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P6.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P7.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P8.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P9.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P10.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P11.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P12.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P13.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P14.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P15.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P16.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P17.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P18.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P19.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P20.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P21.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P22.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P23.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P24.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P25.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P26.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);



                                Fondo = IMG_Load("UltimoC/Perdiste.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);

                                if (bando == 1)
                                {
                                    musicaCarminaBurana();
                                }
                                else
                                {
                                    musicaHallowedBeThyName();
                                }

                                p = 1;

                            }
                            break;
                        

                        } else if (x < 767 && y > 517 || x > 944 && y < 517) {
                            std::cout << correctas;
                            if (correctas > 1) {
                                Fondo = IMG_Load("UltimoC/G1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G4.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G5.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G6.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G7.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G8.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G9.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G10.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G11.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G12.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G13.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G14.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G15.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G16.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G17.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G18.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G19.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G20.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G21.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G22.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G23.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G24.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G25.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G26.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/G27.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/Ganador.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);

                                if (bando == 1)
                                {
                                    musicaHallowedBeThyName();
                                }
                                else
                                {
                                    musicaCarminaBurana();
                                }
                                p = 1;
                                break;
                            }
                            else

                            {
                                Fondo = IMG_Load("UltimoC/P1.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P3.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P4.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P5.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P6.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P7.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P8.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P9.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P10.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P11.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P12.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P13.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P14.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P15.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P16.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P17.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P18.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P19.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P20.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P21.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P22.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P23.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P24.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P25.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);

                                Fondo = IMG_Load("UltimoC/P26.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);
                                SDL_Delay(200);



                                Fondo = IMG_Load("UltimoC/Perdiste.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                                SDL_FreeSurface(Fondo);
                                SDL_UpdateWindowSurface(Ventana);

                                if (bando == 1)
                                {
                                    musicaCarminaBurana();
                                }
                                else
                                {
                                    musicaHallowedBeThyName();
                                }

                                p = 1;


                            }
                                
                            std::cout << "Se termino";
                            p = 1;
                        }
                        



                    }


                
                }
            }

        }
        std::cout << correctas;
    }
    

        SDL_UpdateWindowSurface(Ventana);

            while (!salir)
            {
                if (SDL_PollEvent(&EventoSalir))
                {
                    switch (EventoSalir.type)
                    {
                    case SDL_QUIT:
                        salir = 1;

                        break;

                    }
                }
            }

        SDL_FreeSurface(superficieVentana);
        SDL_DestroyWindow(Ventana);
        SDL_Quit();
    

}


//JUEGOS DE EDIFICIO
void Game::EscapeRoom()
{
    const int WIDTH = 1000;
    const int HEIGHT = 600;
   
    const int SizeMessaje = 50;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
    SDL_Renderer* renderizado; // render de ventana

    //Imagenes
    SDL_Surface* Fondo1;
    SDL_Texture* Tfondo;
    SDL_Surface* superficieVentana;
    SDL_Surface* School = nullptr;
    SDL_Surface* EscapeRoom = nullptr;
    SDL_Surface* codemachine = nullptr;
    SDL_Surface* Board = nullptr;
    SDL_Surface* clue1 = nullptr;
    SDL_Surface* clue2 = nullptr;
    SDL_Surface* clue3 = nullptr;
    SDL_Surface* clue4 = nullptr;
    SDL_Surface* clue5 = nullptr;
    SDL_Surface* clue6 = nullptr;
    SDL_Surface* clue7 = nullptr;
    SDL_Surface* clue8 = nullptr;
    SDL_Surface* clue9 = nullptr;
    SDL_Surface* clue10 = nullptr;
    SDL_Surface* clue11 = nullptr;
    SDL_Surface* clue12 = nullptr;
    SDL_Surface* clue13 = nullptr;
    SDL_Surface* clue14 = nullptr;
    SDL_Surface* clue15 = nullptr;
    SDL_Surface* clue16 = nullptr;
    SDL_Surface* clue17 = nullptr;
    SDL_Surface* clue18 = nullptr;

    SDL_Surface* right = nullptr;
    SDL_Surface* wrong = nullptr;
    SDL_Surface* comp = nullptr;
    SDL_Surface* bttn1 = nullptr;
    SDL_Surface* bttn2 = nullptr;
    SDL_Surface* bttn3 = nullptr;
    SDL_Surface* bttn4 = nullptr;
    SDL_Surface* Preguntas = nullptr;

    SDL_Surface* code1 = nullptr;
    SDL_Surface* code2 = nullptr;
    SDL_Surface* code3 = nullptr;
    SDL_Surface* code4 = nullptr;
    SDL_Surface* inv1 = nullptr;
    SDL_Surface* inv2 = nullptr;

    SDL_Surface* heart;

    SDL_Texture* Fondo;



    SDL_Surface* Continuar;




    SDL_Event EventoSalir;

    const Uint32* m;
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    SDL_Renderer* renderer;
    //evento para el toque de el vaso

    SDL_Event eleccion;
    int SPRITE_SIZE = 1 / 5;

    Ventana = SDL_CreateWindow("Escape Room", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
    SDL_FillRect(superficieVentana, NULL, Color);

    renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* numScore;
    SDL_Rect    gdPosScore;

    School = IMG_Load("Room/1.png");
    EscapeRoom = IMG_Load("Room/2.png");
    codemachine = IMG_Load("Room/4.png");
    Board = IMG_Load("Room/5.png");
    //  clue1 = IMG_Load("Img/5puzzle.png");


    clue1 = IMG_Load("Room/6.png");
    clue2 = IMG_Load("Room/7.png");
    clue3 = IMG_Load("Room/8.png");
    clue4 = IMG_Load("Room/9.png");
    clue5 = IMG_Load("Room/10.png");
    clue6 = IMG_Load("Room/11.png");
    clue7 = IMG_Load("Room/12.png");
    clue8 = IMG_Load("Room/13.png");
    clue9 = IMG_Load("Room/14.png");
    clue10 = IMG_Load("Room/15.png");
    clue11 = IMG_Load("Room/16.png");
    clue12 = IMG_Load("Room/17.png");
    clue13 = IMG_Load("Room/18.png");
    clue14 = IMG_Load("Room/19.png");
    clue15 = IMG_Load("Room/20.png");
    clue16 = IMG_Load("Room/21.png");
    clue17 = IMG_Load("Room/22.png");
    clue18 = IMG_Load("Room/23.png");

    comp = IMG_Load("Room/complete.png");
    right = IMG_Load("Room/code2.png");
    wrong = IMG_Load("Room/code1.png");
    Preguntas = IMG_Load("Room/25.png");
    bttn1 = IMG_Load("Room/code6.png");
    bttn2 = IMG_Load("Room/code5.png");
    bttn3 = IMG_Load("Room/code4.png");
    bttn4 = IMG_Load("Room/code3.png");



    int Puntuacion = 0;
    int bk = 0;
    int prtnum = 1;
    SDL_Surface* currentImg = EscapeRoom;
    SDL_Surface* imgInv;
    SDL_Surface* imgInv2;
    SDL_Surface* imgInv3;
    SDL_Surface* imgInv4;
    SDL_Surface* imgInv5;
    SDL_Surface* imgInv6;
    SDL_Surface* imgInv7;
    SDL_Surface* imgInv8;
    SDL_Surface* imgInv9;
    SDL_Surface* imgInv10;
    SDL_Surface* imgInv11;
    SDL_Surface* imgInv12;
    SDL_Surface* imgInv13;
    SDL_Surface* imgInv14;
    SDL_Surface* imgInv15;
    SDL_Surface* imgInv16;
    SDL_Surface* imgInv17;
    SDL_Surface* imgInv18;

    SDL_Event evento;
    SDL_Event evento2;
    //SDL_MouseButtonEvent b = b;
    SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
    SDL_UpdateWindowSurface(Ventana);
    int count = 0;
    SDL_Texture* grass_image = nullptr;
    grass_image = IMG_LoadTexture(renderer, "Room/1.png");
    SDL_Rect grass_rect;

    int invn1 = 1;
    int invn2 = 2;
    int invn3 = 3;
    int invn4 = 4;
    int invn5 = 5;
    int invn6 = 6;
    int invn7 = 7;
    int invn8 = 8;
    int invn9 = 9;
    int invn10 = 10;
    int invn11 = 11;
    int invn12 = 12;
    int invn13 = 13;
    int invn14 = 14;
    int invn15 = 15;
    int invn16 = 16;
    int invn17 = 17;
    int invn18 = 18;
    std::vector<int> v;
    bool codeAccess = false;
    std::vector<int> arrCode;

    while (isRunning) {
        // SDL_UpdateWindowSurface(Ventana);
        while (codeAccess == true) {


            SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento2) != 0) {




                if (evento2.button.x >= 400 && evento2.button.x <= 500 && evento2.button.y >= 217 && evento2.button.y <= 290) {

                    currentImg = bttn1;

                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "1";
                        arrCode.push_back(1);
                    }
                }
                else if (evento2.button.x >= 504 && evento2.button.x <= 595 && evento2.button.y >= 215 && evento2.button.y <= 290) {

                    currentImg = bttn2;
                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "2";
                        arrCode.push_back(2);
                    }
                }
                else if (evento2.button.x >= 400 && evento2.button.x <= 497 && evento2.button.y >= 304 && evento2.button.y <= 382) {

                    currentImg = bttn3;
                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "3";
                        arrCode.push_back(3);
                    }
                }
                else if (evento2.button.x >= 504 && evento2.button.x <= 595 && evento2.button.y >= 304 && evento2.button.y <= 382) {

                    currentImg = bttn4;
                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "4";
                        arrCode.push_back(4);
                    }
                }
                else if (evento2.button.x >= 681 && evento2.button.x <= 996 && evento2.button.y >= 509 && evento2.button.y <= 572) {

                    currentImg = bttn4;
                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        arrCode.clear();
                        codeAccess = false;

                    }
                }
                else if (!arrCode.empty() && arrCode.size() == 6) {
                    if (arrCode[0] == 1 && arrCode[1] == 2 && arrCode[2] == 2 && arrCode[3] == 3 && arrCode[4] == 3 && arrCode[5] == 2) {
                        currentImg = right;
                        SDL_Delay(500);
                        currentImg = comp;
                        //std::cout << "C O R R E C T   !!!!!";

                    }

                }
                else {

                    currentImg = wrong;
                }
                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
            }
        }
        while (codeAccess == false) {

            if (std::count(v.begin(), v.end(), 1)) {

                gdPosScore.x = 620; gdPosScore.y = 265;
                SDL_RenderClear(renderer);
                imgInv = IMG_Load("Room/inv1.png");

                SDL_BlitSurface(imgInv, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv);

                if (evento.button.x >= 629 && evento.button.x <= 292 && evento.button.y >= 690 && evento.button.y <= 339) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue1;

                    }

                }

            }
            if (std::count(v.begin(), v.end(), 2)) {

                gdPosScore.x = 700; gdPosScore.y = 265;
                SDL_RenderClear(renderer);
                imgInv2 = IMG_Load("Room/inv2.png");

                SDL_BlitSurface(imgInv2, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv2);

            }
            if (std::count(v.begin(), v.end(), 3)) {

                gdPosScore.x = 770; gdPosScore.y = 265;
                SDL_RenderClear(renderer);
                imgInv3 = IMG_Load("Room/inv3.png");
                SDL_BlitSurface(imgInv3, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv3);

            }
            if (std::count(v.begin(), v.end(), 4)) {

                gdPosScore.x = 850; gdPosScore.y = 265;
                SDL_RenderClear(renderer);
                imgInv4 = IMG_Load("Room/inv4.png");

                SDL_BlitSurface(imgInv4, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv4);

            }
            if (std::count(v.begin(), v.end(), 5)) {

                gdPosScore.x = 913; gdPosScore.y = 265;
                SDL_RenderClear(renderer);
                imgInv5 = IMG_Load("Room/inv5.png");

                SDL_BlitSurface(imgInv5, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv5);

            }
            if (std::count(v.begin(), v.end(), 6)) {

                gdPosScore.x = 620; gdPosScore.y = 325;
                SDL_RenderClear(renderer);
                imgInv6 = IMG_Load("Room/inv6.png");

                SDL_BlitSurface(imgInv6, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv6);

            }
            if (std::count(v.begin(), v.end(), 7)) {

                gdPosScore.x = 700; gdPosScore.y = 325;
                SDL_RenderClear(renderer);
                imgInv7 = IMG_Load("Room/inv7.png");

                SDL_BlitSurface(imgInv7, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv7);

            }
            if (std::count(v.begin(), v.end(), 8)) {

                gdPosScore.x = 770; gdPosScore.y = 325;
                SDL_RenderClear(renderer);
                imgInv8 = IMG_Load("Room/inv8.png");

                SDL_BlitSurface(imgInv8, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv8);

            }
            if (std::count(v.begin(), v.end(), 9)) {

                gdPosScore.x = 850; gdPosScore.y = 325;
                SDL_RenderClear(renderer);
                imgInv9 = IMG_Load("Room/inv9.png");

                SDL_BlitSurface(imgInv9, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv9);

            }
            if (std::count(v.begin(), v.end(), 10)) {

                gdPosScore.x = 913; gdPosScore.y = 325;
                SDL_RenderClear(renderer);
                imgInv10 = IMG_Load("Room/inv10.png");

                SDL_BlitSurface(imgInv10, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv10);

            }
            if (std::count(v.begin(), v.end(), 11)) {

                gdPosScore.x = 620; gdPosScore.y = 385;
                SDL_RenderClear(renderer);
                imgInv11 = IMG_Load("Room/inv11.png");

                SDL_BlitSurface(imgInv11, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv11);

            }
            if (std::count(v.begin(), v.end(), 12)) {

                gdPosScore.x = 700; gdPosScore.y = 385;
                SDL_RenderClear(renderer);
                imgInv12 = IMG_Load("Room/inv12.png");

                SDL_BlitSurface(imgInv12, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv12);
            }
            if (std::count(v.begin(), v.end(), 13)) {

                gdPosScore.x = 770; gdPosScore.y = 385;
                SDL_RenderClear(renderer);
                imgInv13 = IMG_Load("Room/inv13.png");

                SDL_BlitSurface(imgInv13, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv13);

            }
            if (std::count(v.begin(), v.end(), 14)) {

                gdPosScore.x = 850; gdPosScore.y = 385;
                SDL_RenderClear(renderer);
                imgInv14 = IMG_Load("Room/inv14.png");

                SDL_BlitSurface(imgInv14, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv14);

            }
            if (std::count(v.begin(), v.end(), 15)) {

                gdPosScore.x = 913; gdPosScore.y = 385;
                SDL_RenderClear(renderer);
                imgInv15 = IMG_Load("Room/inv15.png");

                SDL_BlitSurface(imgInv15, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv15);

            }
            if (std::count(v.begin(), v.end(), 16)) {

                gdPosScore.x = 660; gdPosScore.y = 445;
                SDL_RenderClear(renderer);
                imgInv16 = IMG_Load("Room/inv16.png");

                SDL_BlitSurface(imgInv16, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv16);

            }
            if (std::count(v.begin(), v.end(), 17)) {

                gdPosScore.x = 770; gdPosScore.y = 445;
                SDL_RenderClear(renderer);
                imgInv17 = IMG_Load("Room/inv17.png");

                SDL_BlitSurface(imgInv17, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv17);

            }
            if (std::count(v.begin(), v.end(), 18)) {

                gdPosScore.x = 881; gdPosScore.y = 445;
                SDL_RenderClear(renderer);
                imgInv18 = IMG_Load("Room/inv18.png");

                SDL_BlitSurface(imgInv18, NULL, superficieVentana, &gdPosScore);
                SDL_FreeSurface(imgInv18);

            }



            SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento) != 0) {




                if (evento.button.x >= 428 && evento.button.x <= 460 && evento.button.y >= 308 && evento.button.y <= 356) {

                    currentImg = codemachine;

                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = wrong;
                        ///count = 1;

                        codeAccess = true;
                    }

                }

                else if (evento.button.x >= 491 && evento.button.x <= 541 && evento.button.y >= 70 && evento.button.y <= 132) {

                    currentImg = Board;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = Preguntas;
                    }

                }

                // ********** C L U E 1 ************

                else if (evento.button.x >= 260 && evento.button.x <= 282 && evento.button.y >= 123 && evento.button.y <= 150 || evento.button.x >= 648 && evento.button.x <= 691 && evento.button.y >= 272 && evento.button.y <= 331) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue1;
                        if (std::count(v.begin(), v.end(), 1)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(1);
                    }

                }
                // ********** C L U E 2 ************

                else if (evento.button.x >= 364 && evento.button.x <= 377 && evento.button.y >= 114 && evento.button.y <= 129 || evento.button.x >= 700 && evento.button.x <= 725 && evento.button.y >= 445 && evento.button.y <= 495) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue2;
                        if (std::count(v.begin(), v.end(), 16)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(16);
                    }

                }
                // ********** C L U E 3 ************

                else if (evento.button.x >= 381 && evento.button.x <= 396 && evento.button.y >= 79 && evento.button.y <= 117 || evento.button.x >= 888 && evento.button.x <= 939 && evento.button.y >= 445 && evento.button.y <= 495) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue3;
                        if (std::count(v.begin(), v.end(), 18)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(18);
                    }

                }
                // ********** C L U E 4 ************

                else if (evento.button.x >= 495 && evento.button.x <= 512 && evento.button.y >= 17 && evento.button.y <= 43 || evento.button.x >= 653 && evento.button.x <= 692 && evento.button.y >= 400 && evento.button.y <= 432) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue4;
                        if (std::count(v.begin(), v.end(), 11)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(11);
                    }

                }
                // ********** C L U E 5 ************

                else if (evento.button.x >= 471 && evento.button.x <= 483 && evento.button.y >= 548 && evento.button.y <= 568 || evento.button.x >= 790 && evento.button.x <= 832 && evento.button.y >= 445 && evento.button.y <= 495) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue5;
                        if (std::count(v.begin(), v.end(), 17)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(17);
                    }

                }
                // ********** C L U E 6 ************

                else if (evento.button.x >= 78 && evento.button.x <= 97 && evento.button.y >= 236 && evento.button.y <= 252 || evento.button.x >= 936 && evento.button.x <= 962 && evento.button.y >= 335 && evento.button.y <= 397) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue6;
                        if (std::count(v.begin(), v.end(), 10)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(10);
                    }

                }
                // ********** C L U E 7 ************

                else if (evento.button.x >= 274 && evento.button.x <= 282 && evento.button.y >= 82 && evento.button.y <= 109 || evento.button.x >= 914 && evento.button.x <= 965 && evento.button.y >= 272 && evento.button.y <= 323) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue7;
                        if (std::count(v.begin(), v.end(), 5)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(5);
                    }

                }
                // ********** C L U E 8 ************

                else if (evento.button.x >= 45 && evento.button.x <= 79 && evento.button.y >= 264 && evento.button.y <= 294 || evento.button.x >= 936 && evento.button.x <= 962 && evento.button.y >= 400 && evento.button.y <= 432) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue8;
                        if (std::count(v.begin(), v.end(), 15)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(15);
                    }

                }
                // ********** C L U E 9 ************

                else if (evento.button.x >= 424 && evento.button.x <= 441 && evento.button.y >= 129 && evento.button.y <= 147 || evento.button.x >= 854 && evento.button.x <= 917 && evento.button.y >= 400 && evento.button.y <= 432) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue9;
                        if (std::count(v.begin(), v.end(), 14)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(14);
                    }

                }
                // ********** C L U E 10 ************

                else if (evento.button.x >= 116 && evento.button.x <= 142 && evento.button.y >= 205 && evento.button.y <= 218 || evento.button.x >= 790 && evento.button.x <= 832 && evento.button.y >= 400 && evento.button.y <= 432) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue10;
                        if (std::count(v.begin(), v.end(), 13)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(13);
                    }

                }
                // ********** C L U E 11 ************

                else if (evento.button.x >= 387 && evento.button.x <= 409 && evento.button.y >= 21 && evento.button.y <= 42 || evento.button.x >= 714 && evento.button.x <= 775 && evento.button.y >= 400 && evento.button.y <= 432) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue11;
                        if (std::count(v.begin(), v.end(), 12)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(12);
                    }

                }
                // ********** C L U E 12 ************

                else if (evento.button.x >= 266 && evento.button.x <= 306 && evento.button.y >= 303 && evento.button.y <= 321 || evento.button.x >= 854 && evento.button.x <= 917 && evento.button.y >= 335 && evento.button.y <= 395) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue12;
                        if (std::count(v.begin(), v.end(), 9)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(9);
                    }

                }
                // ********** C L U E 13 ************

                else if (evento.button.x >= 41 && evento.button.x <= 55 && evento.button.y >= 222 && evento.button.y <= 253 || evento.button.x >= 790 && evento.button.x <= 832 && evento.button.y >= 335 && evento.button.y <= 388) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue13; if (std::count(v.begin(), v.end(), 8)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(8);
                    }

                }
                // ********** C L U E 14 ************

                else if (evento.button.x >= 42 && evento.button.x <= 105 && evento.button.y >= 168 && evento.button.y <= 209 || evento.button.x >= 720 && evento.button.x <= 765 && evento.button.y >= 335 && evento.button.y <= 391) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue14;
                        if (std::count(v.begin(), v.end(), 7)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(7);
                    }

                }
                // ********** C L U E 15 ************

                else if (evento.button.x >= 199 && evento.button.x <= 227 && evento.button.y >= 147 && evento.button.y <= 177 || evento.button.x >= 653 && evento.button.x <= 692 && evento.button.y >= 335 && evento.button.y <= 395) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue15;
                        if (std::count(v.begin(), v.end(), 6)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(6);
                    }

                }
                // ********** C L U E 16 ************

                else if (evento.button.x >= 465 && evento.button.x <= 480 && evento.button.y >= 93 && evento.button.y <= 113 || evento.button.x >= 851 && evento.button.x <= 907 && evento.button.y >= 271 && evento.button.y <= 320) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue16;

                        if (std::count(v.begin(), v.end(), 4)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(4);
                    }

                }
                // ********** C L U E 17 ************

                else if (evento.button.x >= 461 && evento.button.x <= 477 && evento.button.y >= 19 && evento.button.y <= 42 || evento.button.x >= 794 && evento.button.x <= 842 && evento.button.y >= 276 && evento.button.y <= 321) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue17;

                        if (std::count(v.begin(), v.end(), 3)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(3);
                    }

                }
                // ********** C L U E 18 ************

                else if (evento.button.x >= 448 && evento.button.x <= 468 && evento.button.y >= 523 && evento.button.y <= 544 || evento.button.x >= 730 && evento.button.x <= 762 && evento.button.y >= 272 && evento.button.y <= 327) {

                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue18;
                        if (std::count(v.begin(), v.end(), 2)) { std::cout << "Elemnto ya fue encontrado!\n"; }
                        else
                            v.push_back(2);

                    }

                }

                else {

                    currentImg = EscapeRoom;

                    //SDL_UpdateWindowSurface(Ventana);

                }
                
            }
            //************************************************************************************************************************************************************************************************


            SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
            //SDL_UpdateWindowSurface(Ventana);
            //SDL_UpdateWindowSurface(superficieVentana);



        }

    }


   
    SDL_Quit();

}



//Jugeo de 
void Game::EdificioUni(int _Regreso)
{

    const int WIDTH = 1000; //Ancho de pantalla
    const int HEIGHT = 564; // altura de pantallla
    const int SPRITE_SIZE = 900; //TAMA;O D ELA ORCA
    const int SizeMessaje = 900; // tama�o de mensaje de carta eleguida
    const int FPS = 60;
    const int frameDaley = 1000 / FPS;

    Uint32 frameStart;
    int frameTIme;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;


    //Imagenes
    SDL_Surface* Fondo;
    SDL_Surface* superficieVentana;

    SDL_Surface* Izquierda;
    SDL_Surface* PARTESa;
    SDL_Surface* AniLab;


    //envento para salir
    SDL_Event EventoSalir;

    int vida = vidas;
    int vidaIa = 3;
    int salir = 0;
    //POsiciones de las imagenes
    SDL_Rect    rcInicial;
    SDL_Rect    gdFinal;

    bool animation = false;
    int frame = 2;
    int speed = 500;

    int movi = 1;

    int x = 0;
    //evento 
    int tiempo = 0;
    SDL_Event Event;

    Ventana = SDL_CreateWindow("Combate por la verdad", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    if (Ventana == NULL)
    {
        std::cout << "Error";

    }
    else
    {

        rcInicial.x = 0; rcInicial.y = 0; rcInicial.w = 28; rcInicial.h = SPRITE_SIZE;

        gdFinal.x = 467; gdFinal.y = 507; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;

        Fondo = IMG_Load("Edificio/Castillo.png");
        SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

        Izquierda = IMG_Load("Edificio/Arriba.png");
        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

        SDL_FreeSurface(Fondo);

        SDL_UpdateWindowSurface(Ventana);
        int p = 0;
        int mayorx = 454;
        int mayory = 301;
        int menorx = 514;
        int menory = 323;
        int correctas = 0;
        int partes = 0;
        //0 - edificio afuera
        //1 - central 
        //2- pasillo aula
        //3- pasillo lab
        //4 - aula
        //5 - laboratorio
        int sala = _Regreso;

        while (p == 0)
        {
            //tiempo++;
            //std::cout << tiempo;
            frameStart = SDL_GetTicks();
            if (SDL_PollEvent(&Event))
            {
                std::cout << "\nx - " << Event.motion.x;
                std::cout << "\ny- " << Event.motion.y;
                if (gdFinal.x >= mayorx && gdFinal.y >= mayory && gdFinal.x < menorx && gdFinal.y < menory && partes == 0)
                {
                    Fondo = IMG_Load("Edificio/Central.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);
                    
                    gdFinal.x = 484; gdFinal.y = 484;
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    partes++;
                }
                else if (gdFinal.x >= 261 && gdFinal.y >= 255 && gdFinal.x < 291 && gdFinal.y < 263 && partes == 1)
                {
                    std::cout << "siguiente";
                    Fondo = IMG_Load("Edificio/Aula.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);

                    gdFinal.x =553; gdFinal.y = 258;
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);

                   
                    
                   
                    partes = 2;
                }
                else if (gdFinal.x >= 703 && gdFinal.y >= 253 && gdFinal.x < 735 && gdFinal.y < 279 && partes == 1)
                {
                    std::cout << "siguiente";
                    Fondo = IMG_Load("Edificio/Laboratorio.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);

                    gdFinal.x = 419; gdFinal.y = 255;
                    Izquierda = IMG_Load("Edificio/Izquierda.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);

                    partes = 3;
                }
                //sala Aula
                else if (gdFinal.x >= 484 && gdFinal.y >= 48 && gdFinal.x < 518 && gdFinal.y < 63 && partes == 2)
                {
                    std::cout << "siguiente2";
                    Fondo = IMG_Load("Edificio/Azotea.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);

                    gdFinal.x = 479; gdFinal.y = 261;
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    //rcInicial.w = 36; rcInicial.h = SPRITE_SIZE;
                    partes = 4;
                }
                //minijuego aula
                else if (gdFinal.x >= 443 && gdFinal.y >= 67 && gdFinal.x < 501 && gdFinal.y < 82 && partes == 7)
                {
                    EscapeRoom();
                }
                //pasillo sotano
                else if (gdFinal.x >= 475 && gdFinal.y >= 54 && gdFinal.x < 520 && gdFinal.y < 67 && partes == 3)
                {
                    std::cout << "siguiente2";
                    Fondo = IMG_Load("Edificio/Sotano.png");
                    SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);

                    gdFinal.x = 476; gdFinal.y = 478;
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                   
                    partes = 5;
                }
                // SALAS DE LABORATORIO
                //Evidencia 
                else if (gdFinal.x >= 256 && gdFinal.y >= 179 && gdFinal.x < 279 && gdFinal.y < 239 && partes == 6)
                {
                   
                }
                // Enumarecion
                else if (gdFinal.x >= 258 && gdFinal.y >= 296 && gdFinal.x < 275 && gdFinal.y < 358 && partes == 6)
                {
                    mesaEnumeracion();
                }
                // analisis
                else if (gdFinal.x >= 713 && gdFinal.y >= 177 && gdFinal.x < 735 && gdFinal.y < 238 && partes == 6)
                {
                   
                    sala = _Regreso;

                }
                //Sintesis
                else if (gdFinal.x >= 714 && gdFinal.y >= 294 && gdFinal.x < 737 && gdFinal.y < 355 && partes == 6)
                {
                    std::cout << "Sala sintetis";
                    SDL_DestroyWindow(Ventana);
                    SDL_Quit();
                    MesaSintesis();

                    

                    p = 1;
                    salir = 1;
                }



                else if (partes == 0) {
                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            salir = 1;
                            break;
                        case SDLK_DOWN:
                            tiempo++;
                            gdFinal.y += 1;
                            std::cout << "\nY = " << gdFinal.y;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Castillo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Abajo.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/C1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            break;
                        case SDLK_UP:
                            gdFinal.y -= 1;
                            std::cout << "\nY = " << gdFinal.y;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Castillo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Arriba.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/C1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //std::cout << "\nderecha?";

                            break;
                        case SDLK_LEFT:
                            tiempo++;

                            gdFinal.x -= movi;
                            std::cout << "\n Aqui X - " << gdFinal.x;

                            //std::cout << "\n Aquia - " << x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Castillo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Izquierda.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/C1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //std::cout << "\nderecha?";
                            break;

                        case SDLK_RIGHT:
                            tiempo++;
                            gdFinal.x += (1 * movi);

                            std::cout << "\n Aquia X- " << gdFinal.x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Castillo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/derecha.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/C1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //gdFinal.y += -1 * movi;

                            break;

                            if (gdFinal.x == 470 && gdFinal.y == 321)
                            {
                                std::cout << "Entro";
                                break;
                            }

                        }
                    }

                }
                else if (partes == 1)
                {
                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            salir = 1;
                            break;
                        case SDLK_DOWN:
                            tiempo++;
                            gdFinal.y += 1;
                            std::cout << "\n" << gdFinal.y;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Central.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Abajo.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            break;
                        case SDLK_UP:
                            gdFinal.y -= 1;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Central.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Arriba.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";

                            break;
                        case SDLK_LEFT:
                            tiempo++;

                            gdFinal.x -= movi;
                            std::cout << "\n Aqui - " << gdFinal.x;

                            std::cout << "\n Aquia - " << x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Central.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Izquierda.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";
                            break;

                        case SDLK_RIGHT:
                            tiempo++;
                            gdFinal.x += (1 * movi);

                            std::cout << "\n Aquia - " << gdFinal.x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Central.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/derecha.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //gdFinal.y += -1 * movi;

                            break;

                            if (gdFinal.x == 470 && gdFinal.y == 321)
                            {
                                std::cout << "Entro";
                                break;
                            }

                        }
                    }
                }
                else if (partes == 2) 
                {
                switch (Event.type)
                {

                case SDL_QUIT:
                    salir = 1;
                    break;

                case SDL_KEYDOWN:

                    switch (Event.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        salir = 1;
                        break;
                    case SDLK_DOWN:
                        tiempo++;
                        gdFinal.y += 1;
                        std::cout << "\n" << gdFinal.y;

                        animation = true;
                        if (animation) {
                            Fondo = IMG_Load("Edificio/Aula.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                            //std::cout << "\n" << rcInicial.x;
                            //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                            Izquierda = IMG_Load("Edificio/Abajo.png");
                            SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                            Izquierda = IMG_Load("Edificio/A1.png");
                            SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                        }
                        break;
                    case SDLK_UP:
                        gdFinal.y -= 1;

                        animation = true;
                        if (animation) {
                            Fondo = IMG_Load("Edificio/Aula.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                            //std::cout << "\n" << rcInicial.x;
                            //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                            Izquierda = IMG_Load("Edificio/Arriba.png");
                            SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                            Izquierda = IMG_Load("Edificio/A1.png");
                            SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                            
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        std::cout << "\nderecha?";

                        break;
                    case SDLK_LEFT:
                        tiempo++;

                        gdFinal.x -= movi;
                        std::cout << "\n Aqui - " << gdFinal.x;

                        std::cout << "\n Aquia - " << x;
                        animation = true;
                        if (animation) {
                            Fondo = IMG_Load("Edificio/Aula.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                            //std::cout << "\n" << rcInicial.x;
                            //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                            Izquierda = IMG_Load("Edificio/Izquierda.png");
                            SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                            Izquierda = IMG_Load("Edificio/A1.png");
                            SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                        }
                        std::cout << "\nderecha?";
                        break;

                    case SDLK_RIGHT:
                        tiempo++;
                        gdFinal.x += (1 * movi);

                        std::cout << "\n Aquia - " << gdFinal.x;
                        animation = true;
                        if (animation) {
                            Fondo = IMG_Load("Edificio/Aula.png");
                            SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                            rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                            //std::cout << "\n" << rcInicial.x;
                            //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                            Izquierda = IMG_Load("Edificio/derecha.png");
                            SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                            Izquierda = IMG_Load("Edificio/A1.png");
                            SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                        }
                        //gdFinal.y += -1 * movi;

                        break;

                        if (gdFinal.x == 470 && gdFinal.y == 321)
                        {
                            std::cout << "Entro";
                            break;
                        }

                    }
                }
                }
                else if (partes == 3) 
{
                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            salir = 1;
                            break;
                        case SDLK_DOWN:
                            tiempo++;
                            gdFinal.y += 1;
                            std::cout << "\n" << gdFinal.y;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Laboratorio.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Abajo.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/L1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                            }
                            break;
                        case SDLK_UP:
                            gdFinal.y -= 1;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Laboratorio.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Arriba.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/L1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";

                            break;
                        case SDLK_LEFT:
                            tiempo++;

                            gdFinal.x -= movi;
                            std::cout << "\n Aqui - " << gdFinal.x;

                            std::cout << "\n Aquia - " << x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Laboratorio.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Izquierda.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/L1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";
                            break;

                        case SDLK_RIGHT:
                            tiempo++;
                            gdFinal.x += (1 * movi);

                            std::cout << "\n Aquia - " << gdFinal.x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Laboratorio.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/derecha.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                Izquierda = IMG_Load("Edificio/L1.png");
                                SDL_BlitSurface(Izquierda, NULL, superficieVentana, NULL);
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //gdFinal.y += -1 * movi;

                            break;

                            if (gdFinal.x == 470 && gdFinal.y == 321)
                            {
                                std::cout << "Entro";
                                break;
                            }

                        }
                    }
}
                else if (partes == 4)
                {
                    std::cout << "Animacion";
                    gdFinal.x = 479; gdFinal.y = 261;
                    AniLab = IMG_Load("Edificio/A0.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/AZ1.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/A2.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/A3.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/A4.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/A5.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/A6.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/A7.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    if (bando == 1)
                    {
                        AniLab = IMG_Load("Edificio/A8.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        Izquierda = IMG_Load("Edificio/Arriba.png");
                        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(2500);
                    }
                    else
                    {
                        AniLab = IMG_Load("Edificio/A9.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        Izquierda = IMG_Load("Edificio/Arriba.png");
                        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(2500);
                    }

                    partes = 7;
                }
                else if (partes == 7)
                {
                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            salir = 1;
                            break;
                        case SDLK_DOWN:
                            tiempo++;
                            gdFinal.y += 1;
                            std::cout << "\n" << gdFinal.y;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Azotea2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Abajo.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            break;
                        case SDLK_UP:
                            gdFinal.y -= 1;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Azotea2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Arriba.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";

                            break;
                        case SDLK_LEFT:
                            tiempo++;

                            gdFinal.x -= movi;
                            std::cout << "\n Aqui - " << gdFinal.x;

                            std::cout << "\n Aquia - " << x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Azotea2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Izquierda.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";
                            break;

                        case SDLK_RIGHT:
                            tiempo++;
                            gdFinal.x += (1 * movi);

                            std::cout << "\n Aquia - " << gdFinal.x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Azotea2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/derecha.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //gdFinal.y += -1 * movi;

                            break;

                            if (gdFinal.x == 470 && gdFinal.y == 321)
                            {
                                std::cout << "Entro";
                                break;
                            }

                        }
                    }
                }
                // ANIMACION CHARLA CON DESCARTES
                else if (partes == 5)
                {
                    gdFinal.x = 480; gdFinal.y = 478;
                    AniLab = IMG_Load("Edificio/S0.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/S1.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S2.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S3.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S4.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/S5.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S6.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S7.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S8.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);

                    AniLab = IMG_Load("Edificio/S9.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/S10.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/S11.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    AniLab = IMG_Load("Edificio/S12.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/Arriba.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2500);

                    if (bando == 1) 
                    {
                        AniLab = IMG_Load("Edificio/S13R.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        Izquierda = IMG_Load("Edificio/Arriba.png");
                        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(2500);
                    }
                    else 
                    {
                        AniLab = IMG_Load("Edificio/S14E.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        Izquierda = IMG_Load("Edificio/Arriba.png");
                        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(2500);
                    }

                    partes = 6;
                } 
                else if (partes == 6 || sala != 0)
                {
                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            salir = 1;
                            break;
                        case SDLK_DOWN:
                            tiempo++;
                            gdFinal.y += 1;
                            std::cout << "\n" << gdFinal.y;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Sotano2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Abajo.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            break;
                        case SDLK_UP:
                            gdFinal.y -= 1;

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Sotano2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Arriba.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";

                            break;
                        case SDLK_LEFT:
                            tiempo++;

                            gdFinal.x -= movi;
                            std::cout << "\n Aqui - " << gdFinal.x;

                            std::cout << "\n Aquia - " << x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Sotano2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/Izquierda.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            std::cout << "\nderecha?";
                            break;

                        case SDLK_RIGHT:
                            tiempo++;
                            gdFinal.x += (1 * movi);

                            std::cout << "\n Aquia - " << gdFinal.x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("Edificio/Sotano2.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                //std::cout << "\n" << rcInicial.x;
                                //s//td::cout << "\n" << static_cast<int>((SDL_GetTicks() / speed) % frame);
                                Izquierda = IMG_Load("Edificio/derecha.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);


                                SDL_UpdateWindowSurface(Ventana);
                            }
                            //gdFinal.y += -1 * movi;

                            break;

                            if (gdFinal.x == 470 && gdFinal.y == 321)
                            {
                                std::cout << "Entro";
                                break;
                            }

                        }
                    }
                }
            }

           
            frameTIme = SDL_GetTicks() - frameStart;

            if (frameDaley > frameTIme)
            {
                SDL_Delay(frameDaley - frameTIme);
            }
            //std::cout << tiempo;
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
                    salir = 1;
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

void Game::mesaEnumeracion()
{
    ventanaMesaEnumeracion("Mesa Enumeracion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 564, false);
    elementosMesaEnumeracion();
    while (true)
        eventosMesaEnumeracion();
}

void Game::ventanaMesaEnumeracion(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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

void Game::elementosMesaEnumeracion()
{
    //fondo
    superficieVentana = SDL_GetWindowSurface(window);

    background = IMG_Load("assets/fondopuerta.png");
    SDL_BlitSurface(background, NULL, superficieVentana, NULL);

    //panel de codigo
    posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
    posFinal.x = 210; posFinal.y = 60; posFinal.w = 600; posFinal.h = 293;
    imagen = IMG_Load("assets/panelcodigo.png");
    SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

    SDL_UpdateWindowSurface(window);
}

void Game::eventosMesaEnumeracion()
{
    int cursorx, cursory;

    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        //cerrar ventana
    case SDL_QUIT:
        exit(1);
        break;
    case SDL_MOUSEMOTION:
        cursorx = event.motion.x, cursory = event.motion.y;

        //tecla 1
        if (cursorx > 257 && cursorx < 347 && cursory > 106 && cursory < 196) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 253; posFinal.y = 104; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla1.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 2
        else if (cursorx > 361 && cursorx < 450 && cursory > 108 && cursory < 199) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 357; posFinal.y = 105; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla2.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 3
        else if (cursorx > 259 && cursorx < 347 && cursory > 212 && cursory < 301) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 255; posFinal.y = 207; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla3.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 4
        else if (cursorx > 670 && cursorx < 759 && cursory > 212 && cursory < 303) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 665; posFinal.y = 207; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla4.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 5
        else if (cursorx > 567 && cursorx < 657 && cursory > 108 && cursory < 197) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 562; posFinal.y = 104; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla5.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 6
        else if (cursorx > 464 && cursorx < 553 && cursory > 211 && cursory < 302) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 459; posFinal.y = 207; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla6.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 7
        else if (cursorx > 465 && cursorx < 553 && cursory > 108 && cursory < 197) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 459; posFinal.y = 104; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla7.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 8
        else if (cursorx > 671 && cursorx < 758 && cursory > 109 && cursory < 198) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 665; posFinal.y = 103; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla8.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 9
        else if (cursorx > 362 && cursorx < 449 && cursory > 214 && cursory < 302) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 357; posFinal.y = 207; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla9.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        //tecla 10
        else if (cursorx > 567 && cursorx < 655 && cursory > 213 && cursory < 302) {
            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 562; posFinal.y = 207; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/tecla10.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        else {
            SDL_FillRect(superficieVentana, NULL, 0x000000);
            SDL_BlitSurface(background, NULL, superficieVentana, NULL);

            posInicial.x = 0; posInicial.y = 0; posInicial.w = 600; posInicial.h = 293;
            posFinal.x = 210; posFinal.y = 60; posFinal.w = 600; posFinal.h = 293;
            imagen = IMG_Load("assets/panelcodigo.png");
            SDL_BlitSurface(imagen, &posInicial, superficieVentana, &posFinal);

            SDL_UpdateWindowSurface(window);
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        cursorx = event.motion.x, cursory = event.motion.y;

        if (cursorx > 257 && cursorx < 347 && cursory > 106 && cursory < 196) {
            codigo += "1 ";
            cantCodigo++;
        }
        if (cursorx > 361 && cursorx < 450 && cursory > 108 && cursory < 199) {
            codigo += "2 ";
            cantCodigo++;
        }
        if (cursorx > 259 && cursorx < 347 && cursory > 212 && cursory < 301) {
            codigo += "3 ";
            cantCodigo++;
        }
        if (cursorx > 670 && cursorx < 759 && cursory > 212 && cursory < 303) {
            codigo += "4 ";
            cantCodigo++;
        }
        if (cursorx > 567 && cursorx < 657 && cursory > 108 && cursory < 197) {
            codigo += "5 ";
            cantCodigo++;
        }
        if (cursorx > 464 && cursorx < 553 && cursory > 211 && cursory < 302) {
            codigo += "6 ";
            cantCodigo++;
        }
        if (cursorx > 465 && cursorx < 553 && cursory > 108 && cursory < 197) {
            codigo += "7 ";
            cantCodigo++;
        }
        if (cursorx > 671 && cursorx < 758 && cursory > 109 && cursory < 198) {
            codigo += "8 ";
            cantCodigo++;
        }
        if (cursorx > 362 && cursorx < 449 && cursory > 214 && cursory < 302) {
            codigo += "9 ";
            cantCodigo++;
        }
        if (cursorx > 567 && cursorx < 655 && cursory > 213 && cursory < 302) {
            codigo += "10 ";
            cantCodigo++;
        }

        std::cout << "Codigo Actual: " << codigo << "\n";

        if (cantCodigo == 4) {
            /*
            comparar codigo con respuesta
            */

            cantCodigo = 0;
            codigo = "";
        }
        break;
    }
}

void Game::MesaSintesis()
{
    //parte == 6
    const int WIDTH = 1000; //Ancho de pantalla
    const int HEIGHT = 564; // altura de pantallla
    const int SPRITE_SIZE = 900; //TAMA;O D ELA ORCA
    const int SizeMessaje = 900; // tama�o de mensaje de carta eleguida
    const int FPS = 60;
    const int frameDaley = 1000 / FPS;

    Uint32 frameStart;
    int frameTIme;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;


    //Imagenes
    SDL_Surface* Fondo;
    SDL_Surface* superficieVentana;

    SDL_Surface* Izquierda;
    SDL_Surface* PARTESa;
    SDL_Surface* AniLab;


    //envento para salir
    SDL_Event EventoSalir;

    int vida = vidas;
    int vidaIa = 3;
    int salir = 0;
    //POsiciones de las imagenes
    SDL_Rect    rcInicial;
    SDL_Rect    gdFinal;

    bool animation = false;
    int frame = 2;
    int speed = 500;

    int movi = 1;

    int x = 0;
    int y = 0;
    //evento 
    int p = 0;
    
    SDL_Event Event;

    int escena = 0;

    int codiAle = 0;
    srand(time(NULL));

    std::string codigo = "";
    std::string codigocorrec = "";
    int intentos = 0;
    int intentos2 = 0;

    Ventana = SDL_CreateWindow("Combate por la verdad", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    if (Ventana == NULL)
    {
        std::cout << "Error";

    }
    else 
    {
        rcInicial.x = 0; rcInicial.y = 0; rcInicial.w = 28; rcInicial.h = SPRITE_SIZE;

        gdFinal.x = 382; gdFinal.y = 210; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;

        Fondo = IMG_Load("MesaSintesis/Fondo.png");
        SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

        Izquierda = IMG_Load("Edificio/derecha.png");
        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

        SDL_FreeSurface(Fondo);

        SDL_UpdateWindowSurface(Ventana);
        int ani = 0;
        while (p == 0)
        {
            //tiempo++;
          
            
            frameStart = SDL_GetTicks();
            if (SDL_PollEvent(&Event))
            {
                std::cout << "\nx - " << Event.motion.x;
                std::cout << "\ny- " << Event.motion.y;

                x = Event.motion.x;
                y = Event.motion.y;
                

                if (gdFinal.x >= 507 && gdFinal.y >= 226 && gdFinal.x < 537 && gdFinal.y < 270 && escena == 0 && ani == 0)
                {
                    std::cout << "Esfera";
                        escena = 1;
                        
                }
                else if (gdFinal.x >= 445 && gdFinal.y >= 67 && gdFinal.x < 506 && gdFinal.y < 98 && escena == 0 &&ani == 1)
                {
                    std::cout << "Botones";
                    escena = 2;
                   
                }else if (gdFinal.x >= 507 && gdFinal.y >= 226 && gdFinal.x < 537 && gdFinal.y < 270 && escena == 0 && ani == 3)
                {
                    std::cout << "Esfera";
                    escena = 4;

                }
                else if (gdFinal.x >= 355 && gdFinal.y >= 205 && gdFinal.x < 386 && gdFinal.y < 267 && escena == 0 && ani ==5)
                {
                    std::cout << "Salir";
                   

                }
                

                
                //frameStart = SDL_GetTicks();
                else if(escena == 0){
                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_KEYDOWN:

                        switch (Event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            salir = 1;
                            break;
                        case SDLK_DOWN:
                            
                            gdFinal.y += 1;
                            

                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("MesaSintesis/Fondo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                               
                                Izquierda = IMG_Load("Edificio/Abajo.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                
                                SDL_UpdateWindowSurface(Ventana);
                            }
                            break;
                        case SDLK_UP:
                            gdFinal.y -= 1;
                            
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("MesaSintesis/Fondo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                
                                Izquierda = IMG_Load("Edificio/Arriba.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                
                                SDL_UpdateWindowSurface(Ventana);
                            }
                          

                            break;
                        case SDLK_LEFT:
                           

                            gdFinal.x -= movi;
                            

                            
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("MesaSintesis/Fondo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                               
                                Izquierda = IMG_Load("Edificio/Izquierda.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                                
                                SDL_UpdateWindowSurface(Ventana);
                            }
                           
                            break;

                        case SDLK_RIGHT:
                            
                            gdFinal.x += (1 * movi);

                            std::cout << "\n Aquia X- " << gdFinal.x;
                            animation = true;
                            if (animation) {
                                Fondo = IMG_Load("MesaSintesis/Fondo.png");
                                SDL_BlitSurface(Fondo, NULL, superficieVentana, NULL);

                                rcInicial.x = rcInicial.w * static_cast<int>((SDL_GetTicks() / speed) % frame);
                                
                                Izquierda = IMG_Load("Edificio/derecha.png");
                                SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);

                               
                                SDL_UpdateWindowSurface(Ventana);
                            }
                           

                            break;

                            

                        }
                    }

                    
                }
                else if (escena == 1)
                {

                    gdFinal.x = 507; gdFinal.y = 226;
                    AniLab = IMG_Load("MesaSintesis/Fondo.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(1000);


                    AniLab = IMG_Load("MesaSintesis/M1.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/M2.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/M3.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/M3.1.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/M3.2.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/M3.3.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/M4.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);


                    AniLab = IMG_Load("MesaSintesis/Fondo.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(1000);
                    ani = 1;
                    escena = 0;
                }
                else if (escena == 2)
                {

                    //gdFinal.x = 445; gdFinal.y = 67;
                    if (ani != 3) {
                        AniLab = IMG_Load("MesaSintesis/Fondo.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        Izquierda = IMG_Load("Edificio/Arriba.png");
                        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(500);


                        AniLab = IMG_Load("MesaSintesis/M5.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(1500);

                        AniLab = IMG_Load("MesaSintesis/M6.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(2000);
                    }

                    while( intentos < 5) {
                        codiAle = 1 + rand() % 3;

                        if (codiAle == 3) {

                            codigocorrec += "3";
                            intentos++;
                            AniLab = IMG_Load("MesaSintesis/M7.png");
                            SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                            SDL_FreeSurface(AniLab);
                            SDL_Delay(1000);

                            AniLab = IMG_Load("MesaSintesis/M6.png");
                            SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                            SDL_FreeSurface(AniLab);
                            SDL_Delay(1000);
                           

                        }
                        else if (codiAle == 2) {

                            codigocorrec += "2";
                            intentos++;
                            AniLab = IMG_Load("MesaSintesis/M8.png");
                            SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                            SDL_FreeSurface(AniLab);
                            SDL_Delay(1000);


                            AniLab = IMG_Load("MesaSintesis/M6.png");
                            SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                            SDL_FreeSurface(AniLab);
                            SDL_Delay(1000);
                        }
                        else if (codiAle == 1) {

                            codigocorrec += "1";
                            intentos++;
                            AniLab = IMG_Load("MesaSintesis/M9.png");
                            SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                            SDL_FreeSurface(AniLab);
                            SDL_Delay(1000);


                            AniLab = IMG_Load("MesaSintesis/M6.png");
                            SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                            SDL_UpdateWindowSurface(Ventana);
                            SDL_FreeSurface(AniLab);
                            SDL_Delay(1000);
                        }


                    }



                    AniLab = IMG_Load("MesaSintesis/M6.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(2000);


                    ani = 2;
                    escena = 3;
                }
                else if (escena == 3 && ani == 2) {

                    

                    switch (Event.type)
                    {

                    case SDL_QUIT:
                        salir = 1;
                        break;

                    case SDL_MOUSEBUTTONDOWN:


                        if (intentos2 < 5) {

                            if (x >= 280 && y >= 208 && x < 407 && y < 319)
                            {

                                intentos2++;
                                codigo += "1";
                                AniLab = IMG_Load("MesaSintesis/M9.png");
                                SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                                SDL_FreeSurface(AniLab);
                                SDL_Delay(200);

                                AniLab = IMG_Load("MesaSintesis/M6.png");
                                SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                                SDL_FreeSurface(AniLab);

                            }

                            if (x >= 428 && y >= 208 && x < 559 && y < 319)
                            {

                                intentos2++;
                                codigo += "2";
                                AniLab = IMG_Load("MesaSintesis/M8.png");
                                SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                                SDL_FreeSurface(AniLab);
                                SDL_Delay(200);

                                AniLab = IMG_Load("MesaSintesis/M6.png");
                                SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                                SDL_FreeSurface(AniLab);

                            }

                            if (x >= 577 && y >= 208 && x < 707 && y < 319)
                            {

                                intentos2++;
                                codigo += "3";
                                AniLab = IMG_Load("MesaSintesis/M7.png");
                                SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                                SDL_FreeSurface(AniLab);
                                SDL_Delay(200);

                                AniLab = IMG_Load("MesaSintesis/M6.png");
                                SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);

                                SDL_UpdateWindowSurface(Ventana);
                                SDL_FreeSurface(AniLab);

                            }
                        }


                    }

                    if (codigo == codigocorrec && intentos2 == 5)
                    {
                        std::cout << "correc";
                        AniLab = IMG_Load("MesaSintesis/Fondo.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        Izquierda = IMG_Load("Edificio/Arriba.png");
                        SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(1000);

                        escena = 0;
                        ani = 3;
                       

                    }
                    else if(codigo != codigocorrec && intentos2 == 5)
                    {
                        std::cout << "incorrecto";

                        AniLab = IMG_Load("MesaSintesis/I3.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(1000);

                        AniLab = IMG_Load("MesaSintesis/I2.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(1000);

                        AniLab = IMG_Load("MesaSintesis/I1.png");
                        SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_FreeSurface(AniLab);
                        SDL_Delay(1000);

                        codigo = "";
                        codigocorrec = "";
                        intentos2 = 0;
                        intentos = 0;

                        escena = 2;
                        ani = 3;

                    }

                    



                }
                else if (escena == 4)
                {

                    AniLab = IMG_Load("MesaSintesis/Fondo.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(500);


                    AniLab = IMG_Load("MesaSintesis/C1.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/C2.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/C3.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/C4.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/C5.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(4000);

                    AniLab = IMG_Load("MesaSintesis/Fondo.png");
                    SDL_BlitSurface(AniLab, NULL, superficieVentana, NULL);
                    Izquierda = IMG_Load("Edificio/derecha.png");
                    SDL_BlitSurface(Izquierda, &rcInicial, superficieVentana, &gdFinal);
                    SDL_UpdateWindowSurface(Ventana);
                    SDL_FreeSurface(AniLab);
                    SDL_Delay(100);



                    escena = 0;
                    ani = 5;


                }

                frameTIme = SDL_GetTicks() - frameStart;
                if (frameDaley > frameTIme)
                {
                    SDL_Delay(frameDaley - frameTIme);
                }




               
                //std::cout << tiempo;
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
                    salir = 1;
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




}


void Game::mesadeAnalisis()
{

    const int WIDTH = 1000;
    const int HEIGHT = 600;

    const int SizeMessaje = 50;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;
    SDL_Renderer* renderizado; // render de ventana

    //Imagenes
    SDL_Surface* Fondo1;
    SDL_Texture* Tfondo;
    SDL_Surface* superficieVentana;
    SDL_Surface* table = nullptr;


    SDL_Surface* clue1 = nullptr;
    SDL_Surface* clue2 = nullptr;
    SDL_Surface* clue3 = nullptr;
    SDL_Surface* clue4 = nullptr;

    SDL_Surface* elegir = nullptr;
    SDL_Surface* animSpoon1 = nullptr;
    SDL_Surface* animSpoon2 = nullptr;
    SDL_Surface* animSpoon3 = nullptr;
    SDL_Surface* animSpoon4 = nullptr;
    SDL_Surface* animRed1 = nullptr;
    SDL_Surface* animRed2 = nullptr;
    SDL_Surface* animRed3 = nullptr;
    SDL_Surface* animRed4 = nullptr;
    SDL_Surface* animRed5 = nullptr;

    SDL_Surface* flame1 = nullptr;
    SDL_Surface* flame2 = nullptr;
    SDL_Surface* flame3 = nullptr;
    SDL_Surface* flame4 = nullptr;
    SDL_Surface* Book = nullptr;
    SDL_Surface* crossOut = nullptr;
    SDL_Surface* mortero1 = nullptr;
    SDL_Surface* mortero2 = nullptr;
    SDL_Surface* mortero3 = nullptr;
    SDL_Surface* mortero4 = nullptr;
    SDL_Surface* mortero5 = nullptr;
    SDL_Surface* mortero6 = nullptr;
    SDL_Surface* right = nullptr;
    SDL_Surface* wrong1 = nullptr;
    SDL_Surface* wrong2 = nullptr;
    SDL_Surface* wrong3 = nullptr;
    SDL_Surface* wrong4 = nullptr;
    SDL_Surface* wrong5 = nullptr;
    SDL_Surface* wrong6 = nullptr;
    SDL_Surface* wrong7 = nullptr;
    SDL_Surface* tablebttn = nullptr;
    SDL_Texture* Fondo;



    SDL_Surface* Continuar;




    SDL_Event EventoSalir;

    const Uint32* m;
    int salir = 0;
    //POsiciones de los vasos
    SDL_Rect    rcMI;
    SDL_Rect    rcInicial; //posicion inicial
    SDL_Rect    gdPosCartas; //posicion con el toque
    SDL_Rect    gdMensaje;

    SDL_Renderer* renderer;
    //evento para el toque de el vaso

    SDL_Event eleccion;
    int SPRITE_SIZE = 1 / 5;

    Ventana = SDL_CreateWindow("Mesa de Analisis", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    superficieVentana = SDL_GetWindowSurface(Ventana);

    Uint32 Color = SDL_MapRGB(superficieVentana->format, 222, 235, 247);
    SDL_FillRect(superficieVentana, NULL, Color);

    renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* numScore;
    SDL_Rect    gdPosScore;

    table = IMG_Load("Analisis/ptn1.png");
    tablebttn = IMG_Load("Analisis/ptn2.png");
    elegir = IMG_Load("Analisis/2.png");
    clue1 = IMG_Load("Analisis/3.png");
    clue2 = IMG_Load("Analisis/4.png");
    clue3 = IMG_Load("Analisis/5.png");
    //  clue1 = IMG_Load("Img/5puzzle.png");


    clue4 = IMG_Load("Analisis/6.png");
    // animSpoon1 = IMG_Load("Analisis/7.png");
    animSpoon1 = IMG_Load("Analisis/8.png");
    animSpoon2 = IMG_Load("Analisis/9.png");
    animSpoon3 = IMG_Load("Analisis/10.png");
    animSpoon4 = IMG_Load("Analisis/11.png");
    animRed1 = IMG_Load("Analisis/12.png");
    animRed2 = IMG_Load("Analisis/13.png");
    animRed3 = IMG_Load("Analisis/14.png");
    animRed4 = IMG_Load("Analisis/15.png");
    animRed5 = IMG_Load("Analisis/16.png");
    flame1 = IMG_Load("Analisis/17.png");
    flame2 = IMG_Load("Analisis/18.png");
    flame3 = IMG_Load("Analisis/19.png");
    flame4 = IMG_Load("Analisis/20.png");
    Book = IMG_Load("Analisis/21.png");
    crossOut = IMG_Load("Analisis/crossout.png");
    mortero1 = IMG_Load("Analisis/22.png");
    mortero2 = IMG_Load("Analisis/23.png");
    mortero3 = IMG_Load("Analisis/24.png");
    mortero4 = IMG_Load("Analisis/25.png");
    mortero5 = IMG_Load("Analisis/26.png");
    right = IMG_Load("Analisis/right.png");
    //wrong1 = IMG_Load("Analisis/wrong1.png");
    wrong1 = IMG_Load("Analisis/wrong2.png");
    wrong2 = IMG_Load("Analisis/wrong3.png");
    wrong3 = IMG_Load("Analisis/wrong4.png");
    wrong4 = IMG_Load("Analisis/wrong5.png");
    wrong5 = IMG_Load("Analisis/wrong6.png");
    wrong6 = IMG_Load("Analisis/wrong7.png");


    SDL_Surface* currentImg = table;

    std::vector<int> v;
    SDL_Event evento;
    SDL_Event evento2;
    //SDL_MouseButtonEvent b = b;
    SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
    SDL_UpdateWindowSurface(Ventana);
    int count = 0;

    bool libro = false;
    bool elegirbool = false;
    bool crossOutbool = false;
    int taskComplete = 0;
    int correct = 0;
    /*
      while (elegirbool == true) {


            SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento2) != 0) {





                if (std::count(v.begin(), v.end(), 1)) {
                    std::cout << "yes its hereee bitchhhhhhhh";

                    gdPosScore.x = 335; gdPosScore.y = 179;
                    SDL_RenderClear(renderer);
                    crossOut = IMG_Load("Analisis/crossout.png");

                    SDL_BlitSurface(crossOut, NULL, superficieVentana, &gdPosScore);
                    SDL_FreeSurface(crossOut);

                }
                currentImg = Book;
                if (evento2.type == SDL_MOUSEBUTTONUP) {

                    libro = false;


                }
            }
        }
         */
    while (isRunning) {




        if (elegirbool == false) {

            SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento) != 0) {



                // ********** C L U E 1 ************
                if (evento.button.x >= 66 && evento.button.x <= 155 && evento.button.y >= 107 && evento.button.y <= 167) {



                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue4;
                        ///count = 1;


                    }

                }
                // ********** C L U E 2 ************
                else if (evento.button.x >= 489 && evento.button.x <= 541 && evento.button.y >= 291 && evento.button.y <= 431) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue3;
                    }

                }

                // ********** C L U E 3 ************

                else if (evento.button.x >= 709 && evento.button.x <= 755 && evento.button.y >= 60 && evento.button.y <= 174) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue1;

                    }

                }
                // ********** C L U E 4 ************

                else if (evento.button.x >= 784 && evento.button.x <= 871 && evento.button.y >= 78 && evento.button.y <= 172) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = clue2;

                    }

                }
                // ********** BOOK  ************

                else if (evento.button.x >= 741 && evento.button.x <= 965 && evento.button.y >= 231 && evento.button.y <= 415) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = Book;

                        libro = true;
                    }

                }
                // ********** R e d ************

                else if (evento.button.x >= 684 && evento.button.x <= 787 && evento.button.y >= 416 && evento.button.y <= 482) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = animRed1;

                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);

                        SDL_Delay(200);

                        currentImg = animRed2;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);

                        SDL_Delay(200);
                        currentImg = animRed3;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);

                        SDL_Delay(200);
                        currentImg = animRed4;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_Delay(200);
                        currentImg = animRed5;
                        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                        SDL_Delay(200);
                        v.push_back(1);
                    }

                }
                // ********** S P O O N ************

                else if (evento.button.x >= 852 && evento.button.x <= 950 && evento.button.y >= 434 && evento.button.y <= 462) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = animSpoon1;

                        SDL_Delay(200);
                        currentImg = animSpoon2;
                        SDL_Delay(200);
                        currentImg = animSpoon3;
                        SDL_Delay(200);
                        currentImg = animSpoon4;
                        SDL_Delay(300);
                        v.push_back(2);

                    }

                }
                //*************  M O R T E R O  ***************
                else if (evento.button.x >= 14 && evento.button.x <= 137 && evento.button.y >= 348 && evento.button.y <= 477) {


                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = mortero1;

                        SDL_Delay(200);
                        currentImg = mortero2;
                        SDL_Delay(200);
                        currentImg = mortero3;
                        SDL_Delay(200);
                        currentImg = mortero4;
                        SDL_Delay(200);
                        currentImg = mortero5;
                        SDL_Delay(300);
                        v.push_back(3);

                    }
                }
                else if (evento.button.x >= 248 && evento.button.x <= 368 && evento.button.y >= 529 && evento.button.y <= 570) {

                    //currentImg = tablebttn;
                    if (evento.type == SDL_MOUSEBUTTONDOWN) {

                        currentImg = elegir;
                        std::cout << "*";
                        elegirbool = true;
                    }
                }
                else {

                    currentImg = table;



                }
            }

        }
        if (elegirbool == true) {


            SDL_UpdateWindowSurface(Ventana);
            while (SDL_PollEvent(&evento2) != 0) {
                if (evento2.button.x >= 46 && evento2.button.x <= 290 && evento2.button.y >= 155 && evento2.button.y <= 418) {


                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "1";
                        correct = 1;
                        flame1 = IMG_Load("Analisis/17.png");
                        flame2 = IMG_Load("Analisis/18.png");
                        flame3 = IMG_Load("Analisis/19.png");
                        flame4 = IMG_Load("Analisis/20.png");
                        right = IMG_Load("Analisis/right.png");
                        SDL_BlitSurface(flame1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);
                        flame1 = IMG_Load("Analisis/17.png");
                        flame2 = IMG_Load("Analisis/18.png");
                        flame3 = IMG_Load("Analisis/19.png");
                        flame4 = IMG_Load("Analisis/20.png");
                        SDL_BlitSurface(flame1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);
                        flame1 = IMG_Load("Analisis/17.png");
                        flame2 = IMG_Load("Analisis/18.png");
                        flame3 = IMG_Load("Analisis/19.png");
                        flame4 = IMG_Load("Analisis/20.png");
                        SDL_BlitSurface(flame1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(right, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(right);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(50000);

                    }
                }
                else if (evento2.button.x >= 336 && evento2.button.x <= 455 && evento2.button.y >= 122 && evento2.button.y <= 454) {


                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "2";
                        correct = 2;
                        flame1 = IMG_Load("Analisis/17.png");
                        flame2 = IMG_Load("Analisis/18.png");
                        flame3 = IMG_Load("Analisis/19.png");
                        flame4 = IMG_Load("Analisis/20.png");
                        // right = IMG_Load("Analisis/right.png");
                        wrong1 = IMG_Load("Analisis/wrong2.png");
                        wrong2 = IMG_Load("Analisis/wrong3.png");
                        wrong3 = IMG_Load("Analisis/wrong4.png");
                        wrong4 = IMG_Load("Analisis/wrong5.png");
                        wrong5 = IMG_Load("Analisis/wrong6.png");
                        wrong6 = IMG_Load("Analisis/wrong7.png");

                        SDL_BlitSurface(flame1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);



                        SDL_BlitSurface(flame2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(wrong1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(wrong5, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong5);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);
                        SDL_BlitSurface(wrong6, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong6);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(5000);


                    }
                }
                else if (evento2.button.x >= 561 && evento2.button.x <= 676 && evento2.button.y >= 142 && evento2.button.y <= 451) {


                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "3";
                        correct = 3;
                        flame1 = IMG_Load("Analisis/17.png");
                        flame2 = IMG_Load("Analisis/18.png");
                        flame3 = IMG_Load("Analisis/19.png");
                        flame4 = IMG_Load("Analisis/20.png");
                        // right = IMG_Load("Analisis/right.png");
                        wrong1 = IMG_Load("Analisis/wrong2.png");
                        wrong2 = IMG_Load("Analisis/wrong3.png");
                        wrong3 = IMG_Load("Analisis/wrong4.png");
                        wrong4 = IMG_Load("Analisis/wrong5.png");
                        wrong5 = IMG_Load("Analisis/wrong6.png");
                        wrong6 = IMG_Load("Analisis/wrong7.png");

                        SDL_BlitSurface(flame1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);



                        SDL_BlitSurface(flame2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(wrong1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(wrong5, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong5);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);
                        SDL_BlitSurface(wrong6, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong6);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(5000);
                    }
                }
                else if (evento2.button.x >= 758 && evento2.button.x <= 948 && evento2.button.y >= 153 && evento2.button.y <= 434) {


                    if (evento2.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout << "4";
                        correct = 4;
                        flame1 = IMG_Load("Analisis/17.png");
                        flame2 = IMG_Load("Analisis/18.png");
                        flame3 = IMG_Load("Analisis/19.png");
                        flame4 = IMG_Load("Analisis/20.png");
                        // right = IMG_Load("Analisis/right.png");
                        wrong1 = IMG_Load("Analisis/wrong2.png");
                        wrong2 = IMG_Load("Analisis/wrong3.png");
                        wrong3 = IMG_Load("Analisis/wrong4.png");
                        wrong4 = IMG_Load("Analisis/wrong5.png");
                        wrong5 = IMG_Load("Analisis/wrong6.png");
                        wrong6 = IMG_Load("Analisis/wrong7.png");

                        SDL_BlitSurface(flame1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(1000);



                        SDL_BlitSurface(flame2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(flame4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(flame4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(wrong1, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong1);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong2, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong2);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong3, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong3);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);



                        SDL_BlitSurface(wrong4, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong4);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);


                        SDL_BlitSurface(wrong5, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong5);
                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(100);
                        SDL_BlitSurface(wrong6, NULL, superficieVentana, NULL);
                        SDL_FreeSurface(wrong6);

                        SDL_UpdateWindowSurface(Ventana);
                        SDL_Delay(5000);
                    }
                }
                else {

                    currentImg = elegir;
                }


            }

            SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
        }

        //************************************************************************************************************************************************************************************************


        SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
        //SDL_UpdateWindowSurface(Ventana);
        //SDL_UpdateWindowSurface(superficieVentana);
    }



    SDL_Quit();
};

