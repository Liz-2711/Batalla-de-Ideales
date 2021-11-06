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
                        SDL_Quit();
                        juegoArte();
                        
                    }
                    else if (numeroAdivinar == 2)
                    {
                        std::cout << "Carta Historia";
                        SDL_Quit();
                        //juegoHistoria();
                       
                    }
                    else if (numeroAdivinar == 3)
                    {
                        std::cout << "Carta POLITICA";
                        
                        SDL_Quit();

                        //juegoPolitica();
                       
                    }
                    else if (numeroAdivinar == 4)
                    {
                        std::cout << "Carta CIENCIA";
                        SDL_Quit();
                        miniJuegoCiencia();
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

void Game::juegoArte()
{

    const int WIDTH = 1000; //Ancho de pantalla
    const int HEIGHT =  564; // altura de pantallla
    const int SPRITE_SIZE = 600; //TAMA;O D ELA ORCA
    const int SizeMessaje = 600; // tamaño de mensaje de carta eleguida

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* Ventana;


    //Imagenes
    SDL_Surface* Fondo;
    SDL_Surface* superficieVentana;

    SDL_Surface* Orca1;
    
    SDL_Surface* Pregunta1;

    SDL_Surface* Respuesta1;



    //enveno para salir
    SDL_Event EventoSalir;


    int salir = 0;
    //POsiciones de las imagenes
    SDL_Rect    rcInicial;
    SDL_Rect    gdFinal;
  

    //evento para el toque de la carta
    SDL_Event eleccion;

    Ventana = SDL_CreateWindow("Pantalla Cartas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
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

        gdFinal.x = 380; gdFinal.y = 80;
        Pregunta1 = IMG_Load("Imagenes/Pregunta00.png");
        SDL_BlitSurface(Pregunta1, &rcInicial, superficieVentana, &gdFinal);

        gdFinal.x = 430; gdFinal.y = 150;
        Respuesta1 = IMG_Load("Imagenes/Respuesta0.png");
        SDL_BlitSurface(Respuesta1, &rcInicial, superficieVentana, &gdFinal);
       


        SDL_FreeSurface(Fondo);
        SDL_FreeSurface(Orca1);
        SDL_FreeSurface(Pregunta1);
        SDL_FreeSurface(Respuesta1);
        int i = 0;
        int M = 0, I = 0, G = 0, U = 0, E = 0, L = 0, A = 0, N = 0, G2 = 0, E2 = 0, L2 = 0;
        int errores = 0; // solo tiene 6 intentos
        int reintentos = 2;

        SDL_UpdateWindowSurface(Ventana);

        while (!i) {
            if (SDL_PollEvent(&eleccion))
            {
                int posicionClick = 0;
                switch (eleccion.type)
                {
                case SDL_QUIT:
                    i = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (eleccion.key.keysym.sym)
                    {
                    case SDLK_m:

                        if (M == 0)
                        {
                            M++;
                            gdFinal.x = 150; gdFinal.y = 100; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;
                            std::cout << "\n\nPresionaste M\n\n";
                            

                        }
                        else 
                        {
                            std::cout << "Ya la habias presionado una vez";
                        }

                        break;

                    case SDLK_i:

                        if (M == 1)
                        {
                            M++;
                           
                            std::cout << "\n\nPresionaste i\n\n";


                        }
                        else
                        {
                            std::cout << "Ya la habias presionado una vez";
                        }

                        break;
                    

                    case SDLK_q:
                        i = 1;
                        break;

                   

                    default:
                        std::cout << "Esta letra no esta";
                        gdFinal.x = 150; gdFinal.y = 100; gdFinal.w = SPRITE_SIZE; gdFinal.h = SPRITE_SIZE;
                        if (errores == 0)
                        {
                            errores++;

                            Orca1 = IMG_Load("Imagenes/orca2.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (errores == 1)
                        {
                            errores++;

                            Orca1 = IMG_Load("Imagenes/orca3.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (errores == 2)
                        {
                            errores++;
                            Orca1 = IMG_Load("Imagenes/orca4.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (errores == 3)
                        {
                            errores++;
                            Orca1 = IMG_Load("Imagenes/Orca5.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (errores == 4)
                        {
                            errores++;
                            Orca1 = IMG_Load("Imagenes/orca6.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (errores == 5)
                        {
                            errores++;
                            Orca1 = IMG_Load("Imagenes/orca7.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                        }
                        else if (errores == 6)
                        {
                            errores++;
                            Orca1 = IMG_Load("Imagenes/orca8.png");
                            SDL_BlitSurface(Orca1, &rcInicial, superficieVentana, &gdFinal);
                            SDL_UpdateWindowSurface(Ventana);
                            i = 1;
                            
                        }
                        else if (errores == 7)
                        {
                          
                            std::cout << "\n\nPerdiste!!\n\n";

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

    int Puntuacion = 0;
    int bk = 0;
    int prtnum = 1;
    SDL_Surface* currentImg = prt1;
    SDL_Event evento;
    while (isRunning) {


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

            //************************************************************************************************************************************************************************************************

        }

        if (prtnum == 2) {

            while (SDL_PollEvent(&evento) != 0) {
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
                SDL_UpdateWindowSurface(Ventana);
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
        //************************************************************************************************************************************************************************************************
        if (prtnum == 3) {
            while (SDL_PollEvent(&evento) != 0) {
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
                SDL_UpdateWindowSurface(Ventana);


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


        //************************************************************************************************************************************************************************************************
        if (prtnum == 4) {
            while (SDL_PollEvent(&evento) != 0) {
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
                SDL_UpdateWindowSurface(Ventana);

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




        //************************************************************************************************************************************************************************************************
        if (prtnum == 5) {
            while (SDL_PollEvent(&evento) != 0) {
                if (bk == 3) {
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
                    bk = 4;
                }

                SDL_BlitSurface(currentImg, NULL, superficieVentana, NULL);
                SDL_UpdateWindowSurface(Ventana);
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

        //************************************************************************************************************************************************************************************************
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
        SDL_UpdateWindowSurface(Ventana);
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