
#include <iostream>
#include "jugador.h"
#include "ruleta.h"
#include "presentacion.h"
#include <iomanip>
using namespace std;

/**
* ****************************************************************************************
* Función: cargarJugadores
*
* Parámetros:
* - Jugador jugadores[] : Arreglo de estructuras Jugador donde se almacenarán los participantes.
* - int &cant           : Referencia a entero donde se guarda la cantidad total de jugadores ingresada.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Solicita por consola la cantidad de jugadores y valida que se encuentre
* entre 2 y 6 participantes. Luego pide el nombre de cada jugador e
* inicializa sus fichas en 2000, la cantidad de apuestas, victorias y
* derrotas en cero.
* ****************************************************************************************
*/

void cargarJugadores(Jugador jugadores[], int &cant){
    color(15);
	do{
		cout << "Cantidad de jugadores: ";
		cin >> cant;
		if(cant < 2 || cant > 6){
			color(12);
			cout << "La cantidad de jugadores debe estar entre 2 y 6" << endl;
			color(15);
		}
	} while(cant < 2 || cant >6);
	
    for(int i=0;i<cant;i++){
        cout << "Nombre jugador " << i+1 << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].fichas = 2000;
		jugadores[i].tlApuestas = 0;
		jugadores[i].victorias = 0;
		jugadores[i].derrotas = 0;
    }
}

/****************************************************
* Función: mostrarEstadoJugadores
* Parámetros:
* - Jugador jugadores[] : Arreglo con la información de los jugadores.
* - int cant : Cantidad de jugadores.
* Retorna:
* - void : No retorna ningun valor.
* Descripción:
* Muestra el saldo actual de fichas, victorias y derrotas de cada participante.
****************************************************/

void mostrarEstadoJugadores(Jugador jugadores[], int cant){
	color(15);
	cout << "==ESTADO DE JUGADORES==" << endl;
	
	cout << left << setw(15) << "Nombre" << setw(15) << "Fichas"
		<< setw(15) << "Victorias" << setw(15) << "Derrotas" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	
	for(int i=0; i < cant; i++){
		cout << left << setw(15) << jugadores[i].nombre << setw(15) << jugadores[i].fichas
			<< setw(15) << jugadores[i].victorias << setw(15) << jugadores[i].derrotas << endl;
	}
	cout << "-----------------------------------------------------------------" << endl;
}

/****************************************************
* Función: jugadorSinFichas
* Parámetros:
* - const Jugador jugadores[] : Arreglo de participantes.
* - int cant : Cantidad total de participantes.
* Retorna:
* - bool : true si algún jugador tiene 0 fichas, false si todos tienen saldo.
* Descripción:
* Evalúa si algún jugador agotó su pozo de fichas.
****************************************************/
bool jugadorSinFichas(Jugador jugadores[], int cant) {
	for (int i = 0; i < cant; i++) {
		if (jugadores[i].fichas <= 0) {
			color(12);
			cout << "El participante " << jugadores[i].nombre << " se quedo sin fichas" << endl;
			return true;
		}
	}
	color(15);
	return false;
}
	

/****************************************************
* Función: inicioSesion
* Parámetros:
* - Jugador jugadores[] : Arreglo de jugadores.
* - int &cant : Cantidad de jugadores.
* - Numero ruleta[37] : Arreglo que representa la ruleta.
* Retorna:
* - void : No retorna ningún valor.
* Descripción:
* Inicializa la ruleta y carga los jugadores de la sesión.
*****************************************************/	
void inicioSesion(Jugador jugadores[], int &cant, Numero ruleta[]){
	inicializarRuleta(ruleta);
	cargarJugadores(jugadores, cant);
}
