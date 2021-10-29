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