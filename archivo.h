#ifndef ARCHIVO_H
#define ARCHIVO_H
	
#include "sesion.h"
	
#define MAX_NOMBRE_ARCHIVO 50
#include <string>
	
	struct ApuestaArchivo {
	int fichasJugadas;
	int numeroApostado;
	char colorApostado;
	int tipoApuesta;
};

struct JugadorArchivo {
	char nombre[MAX_NOMBRE_ARCHIVO];
	int fichas;
	ApuestaArchivo apuestas[MAX_APUESTAS];
	int tlApuestas;
	int victorias;
	int derrotas;
};

struct NumeroArchivo {
	int valor;
	char color;
};

struct SesionArchivo {
	int idSesion;
	NumeroArchivo historial[MAX_JUGADAS];
	int totalGiros;
	JugadorArchivo jugadores[MAX_JUGADORES];
	int jugadoresSesion;
};



void convertirApuestaArchivo(Apuesta origen, ApuestaArchivo &destino);

void convertirJugadorArchivo(Jugador origen, JugadorArchivo &destino);

void convertirNumeroArchivo(Numero origen, NumeroArchivo &destino);

void convertirSesionArchivo(Sesion origen, SesionArchivo &destino);

void convertirApuesta(ApuestaArchivo origen, Apuesta &destino);

void convertirJugador(JugadorArchivo origen, Jugador &destino);

void convertirNumero(NumeroArchivo origen, Numero &destino);

void convertirSesion(SesionArchivo origen, Sesion &destino);


bool guardarSesiones(ptrNodo lista, const char *nombreArchivo);

bool cargarSesiones(ptrNodo &lista, const char *nombreArchivo);

void liberarLista(ptrNodo &lista);

void opcionCargarArchivo(ptrNodo &listaSesiones, std::string &nombreArchivo);

bool guardarAlSalir(ptrNodo lista, std::string &nombreArchivo);

bool opcionSalir(ptrNodo lista, std::string &nombreArchivo);

#endif
