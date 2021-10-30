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
   //void  isRunning() { return isRunning(); };

private:
	bool isRunning = false;
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




