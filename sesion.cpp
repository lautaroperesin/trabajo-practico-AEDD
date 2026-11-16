#include "sesion.h"
#include "presentacion.h"
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
	
	cout << "==JUGADOR CON MAS APOSTADOR POR SESION==" << endl;
	cout << left << setw(15) << "Sesion" << setw(20) << "Jugador"
		<< "Apuestas" << endl;
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
			
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< setw(20) << sesion.jugadores[pos].nombre
				<< Mayor << endl;
		}
		
		actual = actual->sig;
	}
	
	cout << "----------------------------------------------" << endl;
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
	
	cout << "==TIPOS DE JUGADA POR SESION==" << endl;
	cout << left << setw(15) << "Sesion" << setw(20) << " Numero " << " Color " <<" Paridad ";
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
			
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< setw(20) << contadorNumero << contadorColor << contadorParidad<< endl;
		}
		
		actual = actual->sig;
	}
	
	cout << "----------------------------------------------" << endl;
}
/**
* ****************************************************************************************
* Función: efectividadDeApuestas
*
* Parámetros:
* - ptrNodo lista : Cabeza de la lista enlazada de sesiones.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Recorre la lista enlazada, obtiene el tipo de apuesta de cada ronda de cada 
* jugador en una ronda y su valor y lo compara con el numero que salio en esa 
* misma ronda, si es correcto, se suma en victorias de ese tipo, en caso 
* contrario, en derrotas. Una vez contado, se toma el porcentaje de efectividad
* y se sigue con el siguiente elemento de la lista hasta que se llegue a NULL.
* ****************************************************************************************
*/
void efectividadDeApuestas(ptrNodo lista){
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	
	cout << "==EFECTIVIDAD DE APUESTAS==" << endl;
	cout << left << setw(15) << "Sesion" << setw(20) << "Cantidad de jugadores" << "Efectividad (%)";
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
			int derrotasNumero=0;
			int victoriasNumero=0;
			int derrotasColor=0;
			int victoriasColor=0;
			int derrotasParidad=0;
			int victoriasParidad=0;
			
			for(int i=0;i<sesion.totalGiros;i++) { 
				Numero n=sesion.historial[i];
				for (int j = 0; j < sesion.jugadoresSesion; j++) {
					int tipo=getTipoApuesta(getApuestaEnPosicion(sesion.jugadores[j],i));
					if(tipo==1){
						if(getNumeroApostado(getApuestaEnPosicion(sesion.jugadores[j],i))==obtenerValor(n)){
							victoriasNumero++;
						}
						else{
							derrotasNumero++;
						}
					}
					else if(tipo==2){
						if(getColorApostado(getApuestaEnPosicion(sesion.jugadores[j],i))==obtenerColor(n)){
							victoriasColor++;
						}
						else{
							derrotasColor++;
						}
					}
					else if(tipo==3){
						if(obtenerParidad(n)==1){
							victoriasParidad++;
						}
						else{
							derrotasParidad++;
						}
					}
					else{
						if(obtenerParidad(n)==2){
							victoriasParidad++;
						}
						else{
							derrotasParidad++;
						}
					}
				}
			}
			
			float efectividadNumero=victoriasNumero;
			float efectividadColor=victoriasColor;
			float efectividadParidad=victoriasParidad;
			
			efectividadNumero=(efectividadNumero*100)/(derrotasNumero+efectividadNumero);
			efectividadColor=(efectividadColor*100)/(derrotasColor+efectividadColor);
			efectividadParidad=(efectividadParidad*100)/(derrotasParidad+efectividadParidad);
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< setw(20) << sesion.jugadoresSesion << efectividadNumero <<efectividadColor<<efectividadParidad<< endl;
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
	
void efectividadDeJugadores(ptrNodo lista) {
	if (lista == NULL) {
		cout << "No hay sesiones cargadas en memoria." << endl;
		return;
	}
	
	cout << "==EFECTIVIDAD DE LOS JUGADORES==" << endl;
	cout << left << setw(15) << "Sesion" << setw(20) << " Cantidad de jugadores " << " Efectividad ";
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
			int acumuladorDerrotas=0;
			int acumuladorVictorias=0;
			for (int i = 0; i < sesion.jugadoresSesion; i++) {
				acumuladorDerrotas+=getDerrotas(sesion.jugadores[i]);
				acumuladorVictorias+=getVictorias(sesion.jugadores[i]);
				
			}
			float efectividad=acumuladorVictorias;
			efectividad=(efectividad*100)/(acumuladorDerrotas+acumuladorVictorias);
			cout << left << setw(15)
				<< ("Sesion #" + to_string(sesion.idSesion))
				<< setw(20) << sesion.jugadoresSesion << efectividad <<"%" << endl;
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
