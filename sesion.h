#ifndef SESION_H
#define SESION_H
#define MAX_JUGADAS 1200
#define MAX_JUGADORES 6
#include "numero.h"
#include "jugador.h"
struct Sesion {
	int idSesion;
	Numero historial[MAX_JUGADAS];
	int totalGiros; 
	Jugador jugadores[MAX_JUGADORES];
	int jugadoresSesion;   
};
struct Nodo { 
	Sesion info; 
	struct Nodo *sig; 
};
typedef Nodo *ptrNodo;

ptrNodo crearNodo(Sesion s);
void agregarSesion(ptrNodo &lista, Sesion s);
int contarSesiones(ptrNodo lista);
void ordenarSesiones(ptrNodo &lista);
void mostrarSesiones(ptrNodo &lista);
void mostrarJugadorMasVictorias(ptrNodo lista);

void registrarSesionTerminada(ptrNodo &lista, Jugador jugadores[], int cant,
							  Numero historial[], int giros);

#endif

