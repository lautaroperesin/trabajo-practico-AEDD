#include "sesion.h"
#include "presentacion.h"
#include <iostream>
#include <iomanip>
#include <sstream>
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
	cout <<centrar ("==JUGADOR CON MAS VICTORIAS POR SESION==",150)<<endl;
	cout<< centrar("Sesion",50)<<centrar("Jugador",50)<<centrar("Victorias",50)<<endl;
	
	borde(8);

	
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
			cout<< centrar(("Sesion #" + to_string(sesion.idSesion)),50)
				<<centrar(sesion.jugadores[posicionMejor].nombre,50)
				<<centrar(to_string(sesion.jugadores[posicionMejor].victorias),50)
				<<endl;
			
		}
		
		actual = actual->sig;
	}
	
	borde(8);
}

/**
* ****************************************************************************************
* Función: mostrarJugadorMasApostador
*
* Parámetros:
* - ptrNodo lista : Cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Recorre la lista enlazada, comparando en cada sesion cual es el jugador que
* mas fichas arriesgo. La comparación se hace con la sumatorio de fichas que 
* arriesgo cada usuario, se guarda la posicion del mismo y se muestra su 
* informción. Posteriormente, se sigue a la siguiente nodo de la lista enlazada
* para analizar la siguiente sesion, hasta que se termine la lista. (Que apunte
* a NULL)
* ****************************************************************************************
*/
void mostrarJugadorMasApostador(ptrNodo lista) {
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	
	cout <<centrar ("==JUGADOR CON MAS APOSTADOR POR SESION==",150)<<endl;
	cout<< centrar("Sesion",50)<<centrar("Jugador",50)<<centrar("Apuestas",50)<<endl;
	
	borde(8);
	
	ptrNodo actual = lista;
	while (actual != NULL) {
		Sesion &sesion = actual->info;
		
		if (sesion.jugadoresSesion <= 0) {
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< "Sin jugadores registrados" << endl;
		}
		else {
			int Mayor = 0;
			int pos =0;
			for (int i = 0; i < sesion.jugadoresSesion; i++) {
				int sumatoria=0;
				int TL=getTlApuestas(sesion.jugadores[i]);
				for(int j=0;j<TL;j++) { 
					sumatoria+=getFichasJugadas(getApuestaEnPosicion(sesion.jugadores[i],j));
				}
				if(Mayor<sumatoria){
					Mayor=sumatoria;
					pos=i;
				}
			}
			
			cout<< centrar(("Sesion #" + to_string(sesion.idSesion)),50)<<centrar(sesion.jugadores[pos].nombre,50)<<centrar(to_string(Mayor),50)<<endl;
			
		}
		
		actual = actual->sig;
	}
	
	borde(8);
}
/**
* ****************************************************************************************
* Función: tiposDeApuestas
*
* Parámetros:
* - ptrNodo lista : Cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Recorre la lista enlazada, cuenta los tipos de apuesta que se realizaron en 
* cada sesion y los muestra por pantalla. Posteriormente, se sigue a la 
* siguiente nodo de la lista enlazada para analizar la siguiente sesion, hasta 
* que se termine la lista. (Que apuntea NULL)
* ****************************************************************************************
*/
void tiposDeApuestas(ptrNodo lista) {
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	cout <<centrar ("==TIPOS DE JUGADA POR SESION==",150)<<endl;
	cout<< centrar("Sesion",37)<<centrar("Numero",38)<<centrar("Color",37)<<centrar("Paridad",38)<<endl;
	borde(8);
	
	ptrNodo actual = lista;
	while (actual != NULL) {
		Sesion &sesion = actual->info;
		
		if (sesion.jugadoresSesion <= 0) {
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< "Sin jugadores registrados" << endl;
		}
		else {
			int contadorColor=0;
			int contadorParidad=0;
			int contadorNumero=0;
			for (int i = 0; i < sesion.jugadoresSesion; i++) {
				int TL=getTlApuestas(sesion.jugadores[i]);
				for(int j=0;j<TL;j++) { 
					int tipo=getTipoApuesta(getApuestaEnPosicion(sesion.jugadores[i],j));
					if(tipo==1)
						contadorNumero++;
					else if(tipo==2)
						contadorColor++;
					else
						contadorParidad++;
				}
			}
			
			cout<< centrar(("Sesion #" + to_string(sesion.idSesion)),37)
				<<centrar(to_string(contadorNumero),38)
				<<centrar(to_string(contadorColor),37)
				<<centrar(to_string(contadorParidad),38)<<endl;
			borde(8);
		}
		
		actual = actual->sig;
	}
	
	cout << "----------------------------------------------" << endl;
}

/**
* ****************************************************************************************
* Función: efectividadDeJugadores
*
* Parámetros:
* - ptrNodo lista : Cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Recorre la lista enlazada, suma la cantidad de victorias y derrotas de cada 
* jugador y en base a esto se hace el calculo de la efectividad promedio de los
* jugadores en esa sesion y se muestra por pantalla. Esto se repite hasta que se
* llega a NULL.
* ****************************************************************************************
*/	


void efectividadDeJugadores(ptrNodo lista){
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	cout <<centrar ("==EFECTIVIDAD DE LOS JUGADORES==",150)<<endl;
	cout<< centrar("Sesion",50)<<centrar("Cantidad de jugadores",50)<<centrar("Efectividad",50)<<endl;
	borde(8);
	
	ptrNodo actual = lista;
	while (actual != NULL) {
		Sesion &sesion = actual->info;
		
		if (sesion.jugadoresSesion <= 0) {
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< "Sin jugadores registrados" << endl;
		}
		else {
			int acumuladorDerrotas=0;
			int acumuladorVictorias=0;
			for (int i = 0; i < sesion.jugadoresSesion; i++) {
				acumuladorDerrotas+=getDerrotas(sesion.jugadores[i]);
				acumuladorVictorias+=getVictorias(sesion.jugadores[i]);
				
			}
			int totalResultados = acumuladorVictorias + acumuladorDerrotas;
			
			string texto;
			
			if (totalResultados > 0) {
				float efectividad =
					acumuladorVictorias * 100.0 / totalResultados;
				
				stringstream ss;
				ss << fixed << setprecision(2) << efectividad;
				
				texto = ss.str() + "%";
			}
			else {
				texto = "Sin apuestas resueltas";
			}
			
			cout << centrar(("Sesion #" + to_string(sesion.idSesion)), 50)
				<< centrar(to_string(sesion.jugadoresSesion), 50)
				<< centrar(texto, 50) << endl;
		}
		
		actual = actual->sig;
	}
	
	borde(8);
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
