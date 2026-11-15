#include "sesion.h"
#include <iostream>
#include <iomanip>
using namespace std;

/**
* ****************************************************************************************
* Función: crearNodo
*
* Parámetros:
* - Sesion s : Sesión que será copiada dentro del nodo nuevo.
*
* Retorna:
* - ptrNodo : Puntero al nodo recién creado, con el campo sig en NULL.
*
* Descripción:
* Reserva memoria para un nodo de la lista enlazada y almacena en él una copia
* de la sesión recibida, dejándolo apuntando a NULL (último elemento).
* ****************************************************************************************
*/
ptrNodo crearNodo(Sesion s) {
	ptrNodo nuevo = new Nodo;
	nuevo->info = s;
	nuevo->sig = NULL;
	return nuevo;
}

/**
* ****************************************************************************************
* Función: agregarSesion
*
* Parámetros:
* - ptrNodo &lista : Referencia a la cabeza de la lista enlazada de sesiones.
* - Sesion s : Sesión que se desea incorporar a la lista.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Crea un nodo con la sesión recibida y lo enlaza al final de la lista,
* recorriendo la misma desde la cabeza hasta el último nodo. Si la lista está
* vacía, el nuevo nodo pasa a ser la cabeza.
* ****************************************************************************************
*/
void agregarSesion(ptrNodo &lista, Sesion s) {
	ptrNodo nuevo = crearNodo(s);
	
	if (lista == NULL) {
		lista = nuevo;
		return;
	}
	
	ptrNodo actual = lista;
	while (actual->sig != NULL) {
		actual = actual->sig;
	}
	actual->sig = nuevo;
}

/**
* ****************************************************************************************
* Función: contarSesiones
*
* Parámetros:
* - ptrNodo lista : Cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - int : Cantidad de sesiones (nodos) que contiene la lista.
*
* Descripción:
* Recorre la lista enlazada contando cuántos nodos hay, retornando 0 si la
* lista está vacía.
* ****************************************************************************************
*/
int contarSesiones(ptrNodo lista) {
	int contador = 0;
	ptrNodo actual = lista;
	
	while (actual != NULL) {
		contador++;
		actual = actual->sig;
	}
	
	return contador;
}

/**
* ****************************************************************************************
* Función: ordenarSesiones
*
* Parámetros:
* - ptrNodo &lista : Referencia a la cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Ordena las sesiones de la lista de forma ascendente según la cantidad total
* de giros (totalGiros) mediante un algoritmo de burbujeo que compara pares de
* nodos adyacentes e intercambia su contenido (info) cuando están desordenados.
* Al intercambiar solo los datos, los enlaces de la lista no se modifican y no
* es necesario rearmar los punteros. No se establece criterio de desempate.
* ****************************************************************************************
*/
void ordenarSesiones(ptrNodo &lista) {
	if (lista == NULL) {
		return;
	}
	
	bool huboIntercambio = true;
	
	while (huboIntercambio) {
		huboIntercambio = false;
		ptrNodo actual = lista;
		
		while (actual->sig != NULL) {
			if (actual->info.totalGiros > actual->sig->info.totalGiros) {
				Sesion aux = actual->info;
				actual->info = actual->sig->info;
				actual->sig->info = aux;
				huboIntercambio = true;
			}
			actual = actual->sig;
		}
	}
}

/**
* ****************************************************************************************
* Función: mostrarSesiones
*
* Parámetros:
* - ptrNodo &lista : Referencia a la cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Ordena previamente la lista por cantidad de giros de forma ascendente y
* muestra por pantalla el número de sesión y la cantidad total de giros de
* cada una. Si la lista está vacía, informa que no hay sesiones cargadas.
* ****************************************************************************************
*/
void mostrarSesiones(ptrNodo &lista) {
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	
	ordenarSesiones(lista);
	
	cout << "==SESIONES HISTORICAS==" << endl;
	cout << left << setw(15) << "Sesion" << "Giros totales" << endl;
	cout << "------------------------------------" << endl;
	
	ptrNodo actual = lista;
	while (actual != NULL) {
		cout << left << setw(15)
			<< ("Sesion #" + to_string(actual->info.idSesion))
			<< actual->info.totalGiros << " giros" << endl;
		actual = actual->sig;
	}
	
	cout << "------------------------------------" << endl;
	cout << "Total de sesiones: " << contarSesiones(lista) << endl;
}

/**
* ****************************************************************************************
* Función: mostrarJugadorMasVictorias
*
* Parámetros:
* - ptrNodo lista : Cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Recorre cada sesión de la lista y, entre sus jugadores, determina quién tiene
* la mayor cantidad de victorias. Muestra por pantalla el número de sesión, el
* nombre de ese jugador y la cantidad de victorias obtenidas. Las sesiones sin
* jugadores se saltean con un aviso.
* ****************************************************************************************
*/
void mostrarJugadorMasVictorias(ptrNodo lista) {
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	
	cout << "==JUGADOR CON MAS VICTORIAS POR SESION==" << endl;
	cout << left << setw(15) << "Sesion" << setw(20) << "Jugador"
		<< "Victorias" << endl;
	cout << "----------------------------------------------" << endl;
	
	ptrNodo actual = lista;
	while (actual != NULL) {
		Sesion &sesion = actual->info;
		
		if (sesion.jugadoresSesion <= 0) {
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< "Sin jugadores registrados" << endl;
		}
		else {
			int posicionMejor = 0;
			
			for (int i = 1; i < sesion.jugadoresSesion; i++) {
				if (sesion.jugadores[i].victorias >
					sesion.jugadores[posicionMejor].victorias) {
					posicionMejor = i;
				}
			}
			
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< setw(20) << sesion.jugadores[posicionMejor].nombre
				<< sesion.jugadores[posicionMejor].victorias << endl;
		}
		
		actual = actual->sig;
	}
	
	cout << "----------------------------------------------" << endl;
}

/****************************************************
* Funcion: registrarSesionTerminada
* Parametros:
* - ptrNodo &lista: lista de sesiones.
* - Jugador jugadores[]: jugadores de la partida.
* - int cant: cantidad de jugadores.
* - Numero historial[]: resultados de los giros.
* - int giros: cantidad de giros realizados.
* Retorna:
* - void: no devuelve un valor.
* Descripcion:
* Arma una sesion con los datos de la partida y la
* agrega al final de la lista con un numero nuevo.
****************************************************/
void registrarSesionTerminada(
							  ptrNodo &lista,
							  Jugador jugadores[],
							  int cant,
							  Numero historial[],
							  int giros
							  ) {
	Sesion nueva = {};
	
	int mayorId = 0;
	ptrNodo actual = lista;
	
	while (actual != NULL) {
		if (actual->info.idSesion > mayorId) {
			mayorId = actual->info.idSesion;
		}
		
		actual = actual->sig;
	}
	
	nueva.idSesion = mayorId + 1;
	nueva.totalGiros = giros;
	nueva.jugadoresSesion = cant;
	
	for (int i = 0; i < giros; i++) {
		nueva.historial[i] = historial[i];
	}
	
	for (int i = 0; i < cant; i++) {
		nueva.jugadores[i] = jugadores[i];
	}
	
	agregarSesion(lista, nueva);
}
