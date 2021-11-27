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
	void pantallaCartas();

	void minjuegoHistoria();
	void ventanaMinijuegoHistoria(const char*, int, int, int, int, bool);
	void minijuegoHistoriaElementos();
	void minijuegoHistoriaEventos();

	void miniJuegopolitica();

	void Map();

	void bandosCoinFlip();
	
	void CombateporlaVerdad(int);
	void CombateTrancendental(int);

	void musicaHallowedBeThyName();

	void musicaCarminaBurana();


	void combateSujeto();
	void ventanaCombateSujeto(const char*, int, int, int, int, bool);
	void elementosCombateSujeto();
	void eventosCombateSujeto();

	void EscapeRoom();

	SDL_Surface* Vidas(int);

	
	//funciones de juegos de la parte de eleccion
	void juegoArte();
	void miniJuegoCiencia();
   //void  isRunning() { return isRunning(); };

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int numeroAdivinar;
	int vidas;
    SDL_Surface* background;
    SDL_Surface* superficieVentana;
    SDL_Surface* boton1;
    SDL_Surface* boton2;
    SDL_Surface* boton3;
    SDL_Surface* boton4;
	SDL_Surface* personaje1;
	SDL_Surface* globodetexto1;
	SDL_Surface* mensaje1;
	SDL_Surface* tablajuego;
	SDL_Surface* pregunta1;
	SDL_Surface* pulsaespacio;
	SDL_Surface* imagen;
	SDL_Surface* lingote;
	SDL_Surface* correcto;
    SDL_Rect posInicial;
    SDL_Rect posFinal;



	int bando=1;
};




