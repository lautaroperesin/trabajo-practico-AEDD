#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "numero.h"

using namespace std;

const int MAX_APUESTAS = 1200;

struct Apuesta {
	int fichasJugadas;
	int numeroApostado;
	char colorApostado;
	int tipoApuesta; 
};

struct Jugador {
	string nombre;
	int fichas;
	Apuesta apuestas[MAX_APUESTAS];
	int tlApuestas;
	int victorias;
	int derrotas;
};

void cargarJugadores(Jugador jugadores[], int &cant);
void mostrarEstadoJugadores(Jugador jugadores[], int cant);
bool jugadorSinFichas(Jugador jugadores[], int cant);
void inicioSesion(Jugador jugadores[], int &cant, Numero ruleta[37]);
int getFichasJugadas(Apuesta a);
int getNumeroApostado(Apuesta a);
char getColorApostado(Apuesta a);
int getTipoApuesta(Apuesta a);
string getNombre(Jugador j);
int getFichas(Jugador j);
Apuesta getApuestaEnPosicion(Jugador j, int pos);
int getTlApuestas(Jugador j);
int getVictorias(Jugador j);
int getDerrotas(Jugador j);
void setFichasJugadas(Apuesta &a, int fichas);
void setNumeroApostado(Apuesta &a, int numero);
void setColorApostado(Apuesta &a, char color);
void setTipoApuesta(Apuesta &a, int tipo);
void setNombre(Jugador &j, string nombre);
void setFichas(Jugador &j, int fichas);
void setApuestaEnPosicion(Jugador &j, Apuesta ap, int pos);
void setTlApuestas(Jugador &j, int tl);
void setVictorias(Jugador &j, int victorias);
void setDerrotas(Jugador &j, int derrotas);
void agregarApuesta(Jugador &j, Apuesta ap);

#endif
