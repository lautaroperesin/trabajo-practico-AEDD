#include <stdlib.h>
#include <windows.h>
#include <string>

#include <iostream>
#include "archivo.h"
#include "numero.h"
#include "ruleta.h"
#include "jugador.h"
#include "presentacion.h"
#include "sesion.h"

using namespace std;

int main() {
	const int ANCHO_VENTANA = 150;
	//Presentacion
	pantallaCompleta();
	ocultarCursor();
	tamanioVentana(ANCHO_VENTANA, 55);
	Presentacion();
	cout<<endl<<centrar("Presione ENTER para continuar...", ANCHO_VENTANA);
	mostrarCursor();
	cin.get();
	limpiarPantalla();
	
	//Variables
	int cant = 0;
	Jugador jugadores[6];
	Numero ruleta[37];
	char eleccion;
	bool condicion=false;
	Numero registroNumeros[1200];
	int giros = 0;
	ptrNodo listaSesiones = NULL;
	string nombreArchivo;
	do{
		Selector(condicion);
		cin>>eleccion;
		limpiarPantalla();
		
		switch (eleccion){
		case '1':
			if(!condicion){
				inicioSesion(jugadores,cant, ruleta);
				
				condicion=true;
				
				limpiarPantalla();
				
				ejecutarCicloPartidas(ruleta, jugadores, cant, registroNumeros, giros);
				
				registrarSesionTerminada(listaSesiones, jugadores, cant, registroNumeros, giros);
			}
			else{
				Mensaje("Ya se ha iniciado sesion");
			}
			break;
		case '2':
			if(condicion){
				mostrarEstadoJugadores(jugadores, cant);
				cin.ignore();
				cin.get();
			}
			else{
				Mensaje("Debes iniciar sesion para acceder a esta funcion");
			}
			break;
		case '3':
			if(condicion){
				mostrarHistorial(registroNumeros,giros);
				cin.ignore();
				cin.get();
			}
			else{
				Mensaje("Debes iniciar sesion para acceder a esta funcion");
			}
			break;
		case '4':
			if(condicion){
				mostrarEstadisticas(registroNumeros,giros);
				cin.ignore();
				cin.get();
			}
			else{
				Mensaje("Debes iniciar sesion para acceder a esta funcion");
			}
			break;
		case '5':
			mostrarSesiones(listaSesiones);
			
			cout << "Presiona ENTER para continuar...";
			cin.ignore();
			cin.get();
			break;
			
		case '6':
			Mensaje("Funcionalidad en Desarrollo");
			break;
		case '7':
			opcionCargarArchivo(listaSesiones, nombreArchivo);
			break;
		case 'X':
		case 'x':
			if (!opcionSalir(listaSesiones, nombreArchivo)) {
				eleccion = '0';
			}
			break;
		default:
			Mensaje("Funcion desconocida");
		};
		
		limpiarPantalla();
		
	}while(eleccion!='x' and eleccion!='X') ;
	
	liberarLista(listaSesiones);
	Despedida();
	
	return 0;
}
