#include "apuesta.h"
#include "jugador.h"
#include "presentacion.h"
#include <iostream>
using namespace std;

/************************************************************
* Función: cargarApuestas
*
* Parámetros:
* - Jugador jugadores[] : Arreglo de jugadores donde se almacenan
*   las apuestas realizadas.
* - int cant : Cantidad de jugadores participantes.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Recorre el arreglo de jugadores y solicita a cada uno la cantidad
* de fichas que desea apostar, validando que sea mayor a cero y no
* supere las fichas disponibles.
*
* Luego solicita el tipo de apuesta:
* 1 - Número
* 2 - Color
* 3 - Par
* 4 - Impar
*
* Si la apuesta es a un número, valida que esté comprendido entre
* 0 y 36. Si la apuesta es a un color, valida que sea rojo ('R')
* o negro ('N').
*
* Finalmente almacena los datos de la apuesta e incrementa la
* cantidad total de apuestas realizadas por el jugador.
*************************************************************/

void cargarApuestas(Jugador jugadores[], int cant){
	
	for(int i = 0; i < cant; i++) { 
		color(15);
		cout << "El apostador: " << jugadores[i].nombre << endl;
		cout << "Tiene " << jugadores[i].fichas << "  fichas." << endl;
		int apuesta = 0;
		do{ 
			cout << "¿Cuantas fichas desea apostar?" << endl;
			color(10);//verde claro
			cin >> apuesta;
			color(15);//blanco brillante
		} while( apuesta <= 0 || apuesta > jugadores[i].fichas );
		
		jugadores[i].apuestas[jugadores[i].tlApuestas].fichasJugadas = apuesta;
		
		do {
		cout << "¿Que tipo de apuesta desea realizar?" << endl;
		cout << "1 - Numero" << endl;
		cout << "2 - Color" << endl;
		cout << "3 - Par" << endl;
		cout << "4 - Impar" << endl;
		
		cin >> jugadores[i].apuestas[jugadores[i].tlApuestas].tipoApuesta;
		
		switch(jugadores[i].apuestas[jugadores[i].tlApuestas].tipoApuesta) {
			
		case 1:
			cout << "Elegiste apostar a un numero" << endl;
			do{
				cout << "Selecciona un numero" << endl;
				cin >> jugadores[i].apuestas[jugadores[i].tlApuestas].numeroApostado;
				if(jugadores[i].apuestas[jugadores[i].tlApuestas].numeroApostado < 0 || jugadores[i].apuestas[jugadores[i].tlApuestas].numeroApostado > 36){
					cout << "El numero debe estar entre 0 y 36" << endl;
				}
			} while(jugadores[i].apuestas[jugadores[i].tlApuestas].numeroApostado < 0 || jugadores[i].apuestas[jugadores[i].tlApuestas].numeroApostado > 36);
			break;
			
		case 2:
			cout << "Elegiste apostar a un color" << endl;
			do{
				cout << "Selecciona un color:(";
				color(4);//rojo
				cout <<"R = Rojo";
				color(15);//blanco brillante
				cout<<", N = Negro)" << endl;
				cin >> jugadores[i].apuestas[jugadores[i].tlApuestas].colorApostado;
				if(jugadores[i].apuestas[jugadores[i].tlApuestas].colorApostado != 'N' &&
				   jugadores[i].apuestas[jugadores[i].tlApuestas].colorApostado != 'R'){
					cout << "Selecciona un color valido (R = Rojo, N = Negro)" << endl; 
				}
			} while(jugadores[i].apuestas[jugadores[i].tlApuestas].colorApostado != 'N' &&
					jugadores[i].apuestas[jugadores[i].tlApuestas].colorApostado != 'R');
			break;
			
		case 3:
			cout << "Elegiste apostar a par" << endl;
			break;
			
		case 4:
			cout << "Elegiste apostar a impar" << endl;
			break;
			
		default:
			cout << "Opcion invalida" << endl;
			break;
		}
		}while (jugadores[i].apuestas[jugadores[i].tlApuestas].tipoApuesta < 1 || jugadores[i].apuestas[jugadores[i].tlApuestas].tipoApuesta > 4);
		
		jugadores[i].tlApuestas++;
	}
	colorNormal();
}

	
