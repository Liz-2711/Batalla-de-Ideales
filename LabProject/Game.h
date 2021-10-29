#pragma once

#include "SDL.h"
#include <iostream>
#include"SDL_image.h"
#include <stdio.h>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
    void ventanaMenuPrincipal(const char*, int, int, int, int, bool);
    void eventosMenuPrincipal();
    void elementosMenuPrincipal();
    void menuPrincipal();
    void isRunning() { return isRunning(); };

private:
	bool isRunning;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
    SDL_Surface* background;
    SDL_Surface* superficieVentana;
    SDL_Surface* boton1;
    SDL_Surface* boton2;
    SDL_Surface* boton3;
    SDL_Surface* boton4;
    SDL_Rect posInicial;
    SDL_Rect posFinal;
};




/*
* 
* 
* 
* SPRITE KEYBOARD CONTROLS
* 
* 
*   // SDL_Surface* temp = NULL;
      //  SDL_Surface* sprite = NULL;
       // SDL_Surface* SDL_DisplayFormat(SDL_Surface * surface);
       // SDL_Rect    rcSprite;
       // SDL_Rect    gdSprite;
       // SDL_Event windowEvent;
       // SDL_Event   event;

        // sprite = IMG_Load("motoVerde.png");

        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite);

  rcSprite.x = 0;
        rcSprite.y = 0;
        rcSprite.w = SPRITE_SIZE;
        rcSprite.h = SPRITE_SIZE;

        gdSprite.x = xPosition;
        gdSprite.y = yPosition;
        gdSprite.w = SPRITE_SIZE;
        gdSprite.h = SPRITE_SIZE;

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
                }
            }

            keystate = SDL_GetKeyboardState(NULL);

            // When key pressed, update the destination rectangle
            if (keystate[SDL_SCANCODE_LEFT]) {
                gdSprite.x -= 2;
            }
            if (keystate[SDL_SCANCODE_RIGHT]) {
                gdSprite.x += 2;
            }
            if (keystate[SDL_SCANCODE_UP]) {
                gdSprite.y -= 2;
            }
            if (keystate[SDL_SCANCODE_DOWN]) {
                gdSprite.y += 2;
            }


            //Render the window
            SDL_RenderClear(renderer);
           // SDL_RenderCopy(renderer, texture, NULL, &gdSprite);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderCopy(renderer, spriteTexture, &rcSprite, &gdSprite);
            SDL_RenderPresent(renderer);



            //update the source rectangle to move with the sprite??
          //  rcSprite.x = gdSprite.x;
          //  rcSprite.y = gdSprite.y;

        }*/