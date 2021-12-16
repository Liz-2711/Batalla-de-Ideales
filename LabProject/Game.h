#pragma once

#include "SDL.h"
#include <iostream>
#include"SDL_image.h"
#include <stdio.h>
#include <string>

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
	//menu
    void ventanaMenuPrincipal(const char*, int, int, int, int, bool);
    void eventosMenuPrincipal();
    void elementosMenuPrincipal();
    void menuPrincipal();

	//cartas
	void pantallaCartas();

	//minijuego Historia
	void minjuegoHistoria();
	void ventanaMinijuegoHistoria(const char*, int, int, int, int, bool);
	void minijuegoHistoriaElementos();
	void minijuegoHistoriaEventos();

	//minijuego Politica
	void miniJuegopolitica();

	//minijuego Arte
	void juegoArte();

	//minujuego CIencia
	void miniJuegoCiencia();


	//Eleccion de bandos
	void bandosCoinFlip();

	//map
	void Map(int);

	//Combates

	//Combate por la verdad
	 void CombateporlaVerdad(int);
	//combate por el sujeto
	 void combateSujeto();
	 void ventanaCombateSujeto(const char*, int, int, int, int, bool);
	 void elementosCombateSujeto();
	 void eventosCombateSujeto();

	//combate trancendental
	 void CombateTrancendental(int);


	//musica ganador
	//bando 1
	//1 - Racionalistas
	//!= 1 - Empirsta
	//racionalista
	 void musicaHallowedBeThyName();

	 //Empirista
	 void musicaCarminaBurana();

	 //funcion vidas
	 SDL_Surface* Vidas(int);




	 //Edificio
	 //en este caso los cambios de pantalla tienen que hacerse desde dentro de esta funcion casis solo e scuando se llamasn a los juegos d elas salas
	 void EdificioUni(int);

	 //aula IManuel KANT
	 void EscapeRoom(); //juego


	 //Laboratorio ReneDescartes
	 //salas
	 //salas enumeracion
	 void mesaEnumeracion();
	 void ventanaMesaEnumeracion(const char*, int, int, int, int, bool);
	 void elementosMesaEnumeracion();
	 void eventosMesaEnumeracion();//juego
	 void mensajePared();
	 void eventosMensajePared();

	 void MesaEnumeracion2(); // sala con animaciones
	
	 //sala Sintesis
	 void MesaSintesis();

	 //sala Evidencia
	 void MesaEvidencia(int); // sala
	 void mesadeEvidenciaMinijuego();// juego


	 //sala Analisis
	 void mesadeAnalisis(); //juego
	 void AniMesAna(int); //sala
	
	//gameover solo si vidas es 0

	void GameOver(int vidas);


	//Logros

	void Logros();
	

private:
	bool isRunning = true;
	int cnt = 0;
	SDL_Window* window;
	SDL_Window* Ventana;
	
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



	std::string salascomplet;

	int bando=1;
	//1 - Racionalistas
	//!= 1 - Empirsta
};




