
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

/****************************************************
* Funcion: getFichas
* Parametros:
* - Jugador j: Jugador que se consulta.
* Retorna:
* - int: Cantidad de fichas del jugador.
* Descripcion:
* Devuelve el valor del campo fichas.
****************************************************/
int getFichas(Jugador j) {
	return j.fichas;
}


/****************************************************
* Funcion: getFichasJugadas
* Parametros:
* - Apuesta a: Apuesta que se consulta.
* Retorna:
* - int: Cantidad de fichas apostadas.
* Descripcion:
* Devuelve el valor del campo fichasJugadas.
****************************************************/
int getFichasJugadas(Apuesta a) {
	return a.fichasJugadas;
}

/****************************************************
* Funcion: getNumeroApostado
* Parametros:
* - Apuesta a: Apuesta que se consulta.
* Retorna:
* - int: Numero elegido en la apuesta.
* Descripcion:
* Devuelve el valor del campo numeroApostado.
****************************************************/
int getNumeroApostado(Apuesta a) {
	return a.numeroApostado;
}

/****************************************************
* Funcion: getColorApostado
* Parametros:
* - Apuesta a: Apuesta que se consulta.
* Retorna:
* - char: Color elegido en la apuesta.
* Descripcion:
* Devuelve el valor del campo colorApostado.
****************************************************/
char getColorApostado(Apuesta a) {
	return a.colorApostado;
}

/****************************************************
* Funcion: getTipoApuesta
* Parametros:
* - Apuesta a: Apuesta que se consulta.
* Retorna:
* - int: Tipo de apuesta registrado.
* Descripcion:
* Devuelve el valor del campo tipoApuesta.
****************************************************/
int getTipoApuesta(Apuesta a) {
	return a.tipoApuesta;
}


/****************************************************
* Funcion: getNombre
* Parametros:
* - Jugador j: Jugador que se consulta.
* Retorna:
* - string: Nombre del jugador.
* Descripcion:
* Devuelve el texto guardado en el campo nombre.
****************************************************/
string getNombre(Jugador j) {
	return j.nombre;
}

/****************************************************
* Funcion: getApuestaEnPosicion
* Parametros:
* - Jugador j: Jugador cuyas apuestas se consultan.
* - int pos: Posicion de la apuesta que se quiere obtener.
* Retorna:
* - Apuesta: Copia de la apuesta ubicada en esa posicion.
* Descripcion:
* Devuelve un elemento del arreglo de apuestas.
* La posicion recibida debe corresponder a una apuesta
* registrada, porque la funcion no comprueba sus limites.
****************************************************/
Apuesta getApuestaEnPosicion(Jugador j, int pos) {
	return j.apuestas[pos];
}

/****************************************************
* Funcion: getTlApuestas
* Parametros:
* - Jugador j: Jugador que se consulta.
* Retorna:
* - int: Cantidad de apuestas registradas.
* Descripcion:
* Devuelve el valor del campo tlApuestas, que indica
* cuantas posiciones del arreglo de apuestas se utilizan.
****************************************************/
int getTlApuestas(Jugador j) {
	return j.tlApuestas;
}

/****************************************************
* Funcion: getVictorias
* Parametros:
* - Jugador j: Jugador que se consulta.
* Retorna:
* - int: Cantidad de victorias del jugador.
* Descripcion:
* Devuelve el valor del campo victorias.
****************************************************/
int getVictorias(Jugador j) {
	return j.victorias;
}

/****************************************************
* Funcion: getDerrotas
* Parametros:
* - Jugador j: Jugador que se consulta.
* Retorna:
* - int: Cantidad de derrotas del jugador.
* Descripcion:
* Devuelve el valor del campo derrotas.
****************************************************/
int getDerrotas(Jugador j) {
	return j.derrotas;
}

/****************************************************
* Funcion: setFichasJugadas
* Parametros:
* - Apuesta &a: Apuesta que se modifica.
* - int fichas: Cantidad de fichas que se quiere asignar.
* Retorna:
* - void: No devuelve un valor; modifica a.
* Descripcion:
* Asigna el dato recibido al campo fichasJugadas.
****************************************************/
void setFichasJugadas(Apuesta &a, int fichas) {
	a.fichasJugadas = fichas;
}

/****************************************************
* Funcion: setNumeroApostado
* Parametros:
* - Apuesta &a: Apuesta que se modifica.
* - int numero: Numero que se quiere asignar.
* Retorna:
* - void: No devuelve un valor; modifica a.
* Descripcion:
* Asigna el dato recibido al campo numeroApostado.
****************************************************/
void setNumeroApostado(Apuesta &a, int numero) {
	a.numeroApostado = numero;
}

/****************************************************
* Funcion: setColorApostado
* Parametros:
* - Apuesta &a: Apuesta que se modifica.
* - char color: Color que se quiere asignar.
* Retorna:
* - void: No devuelve un valor; modifica a.
* Descripcion:
* Asigna el dato recibido al campo colorApostado.
****************************************************/
void setColorApostado(Apuesta &a, char color) {
	a.colorApostado = color;
}

/****************************************************
* Funcion: setTipoApuesta
* Parametros:
* - Apuesta &a: Apuesta que se modifica.
* - int tipo: Tipo de apuesta que se quiere asignar.
* Retorna:
* - void: No devuelve un valor; modifica a.
* Descripcion:
* Asigna el dato recibido al campo tipoApuesta.
****************************************************/
void setTipoApuesta(Apuesta &a, int tipo) {
	a.tipoApuesta = tipo;
}

/****************************************************
* Funcion: setNombre
* Parametros:
* - Jugador &j: Jugador que se modifica.
* - string nombre: Nombre que se quiere asignar.
* Retorna:
* - void: No devuelve un valor; modifica j.
* Descripcion:
* Copia el texto recibido al campo nombre del jugador.
****************************************************/
void setNombre(Jugador &j, string nombre) {
	j.nombre = nombre;
}

/****************************************************
* Funcion: setFichas
* Parametros:
* - Jugador &j: Jugador que se modifica.
* - int fichas: Cantidad de fichas que se quiere asignar.
* Retorna:
* - void: No devuelve un valor; modifica j.
* Descripcion:
* Asigna el dato recibido al campo fichas del jugador.
****************************************************/
void setFichas(Jugador &j, int fichas) {
	j.fichas = fichas;
}

/****************************************************
* Funcion: setApuestaEnPosicion
* Parametros:
* - Jugador &j: Jugador cuyo arreglo se modifica.
* - Apuesta ap: Apuesta que se quiere copiar.
* - int pos: Posicion donde se coloca la apuesta.
* Retorna:
* - void: No devuelve un valor; modifica j.
* Descripcion:
* Copia la apuesta en la posicion indicada del arreglo.
* No modifica tlApuestas ni comprueba los limites.
* La posicion debe estar dentro del arreglo.
****************************************************/
void setApuestaEnPosicion(Jugador &j, Apuesta ap, int pos) {
	j.apuestas[pos] = ap;
}

/****************************************************
* Funcion: setTlApuestas
* Parametros:
* - Jugador &j: Jugador que se modifica.
* - int tl: Cantidad de apuestas registradas que se asigna.
* Retorna:
* - void: No devuelve un valor; modifica j.
* Descripcion:
* Asigna el dato recibido al campo tlApuestas.
* No agrega ni elimina apuestas del arreglo.
****************************************************/
void setTlApuestas(Jugador &j, int tl) {
	j.tlApuestas = tl;
}

/****************************************************
* Funcion: setVictorias
* Parametros:
* - Jugador &j: Jugador que se modifica.
* - int victorias: Cantidad de victorias que se asigna.
* Retorna:
* - void: No devuelve un valor; modifica j.
* Descripcion:
* Asigna el dato recibido al campo victorias.
****************************************************/
void setVictorias(Jugador &j, int victorias) {
	j.victorias = victorias;
}

/****************************************************
* Funcion: setDerrotas
* Parametros:
* - Jugador &j: Jugador que se modifica.
* - int derrotas: Cantidad de derrotas que se asigna.
* Retorna:
* - void: No devuelve un valor; modifica j.
* Descripcion:
* Asigna el dato recibido al campo derrotas.
****************************************************/
void setDerrotas(Jugador &j, int derrotas) {
	j.derrotas = derrotas;
}
