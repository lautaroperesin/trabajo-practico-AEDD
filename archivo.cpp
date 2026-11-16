#include "archivo.h"
#include "sesion.h"
#include "jugador.h"
#include "numero.h"
#include <fstream>
#include <cstring>
#include <ctime>
#include <string>
	
#include <iostream>
#include "jugador.h"
#include "presentacion.h"
using namespace std;

/****************************************************
* Funcion: sesionValida
* Parametros:
* - Sesion s: Sesion que se quiere comprobar.
* Retorna:
* - bool: true si las cantidades son validas; false si no lo son.
* Descripcion:
* Comprueba que la cantidad de giros, jugadores y apuestas
* de cada jugador este dentro de los limites permitidos.
****************************************************/
bool sesionValida(Sesion s) {
	bool valida = true;
	
	if (s.totalGiros < 0 || s.totalGiros > MAX_JUGADAS) {
		valida = false;
	}
	
	if (s.jugadoresSesion < 0 ||
		s.jugadoresSesion > MAX_JUGADORES) {
		valida = false;
	}
	
	for (int i = 0; valida && i < s.jugadoresSesion; i++) {
		int tl = getTlApuestas(s.jugadores[i]);
		
		if (tl < 0 || tl > MAX_APUESTAS) {
			valida = false;
		}
	}
	
	return valida;
}

/****************************************************
* Funcion: sesionArchivoValida
* Parametros:
* - SesionArchivo s: Registro leido del archivo.
* Retorna:
* - bool: true si las cantidades son validas; false si no lo son.
* Descripcion:
* Comprueba los limites de giros, jugadores y apuestas antes
* de convertir el registro en una sesion del programa.
****************************************************/
bool sesionArchivoValida(SesionArchivo s) {
	bool valida = true;
	
	if (s.totalGiros < 0 || s.totalGiros > MAX_JUGADAS) {
		valida = false;
	}
	
	if (s.jugadoresSesion < 0 ||
		s.jugadoresSesion > MAX_JUGADORES) {
		valida = false;
	}
	
	for (int i = 0; valida && i < s.jugadoresSesion; i++) {
		if (s.jugadores[i].tlApuestas < 0 ||
			s.jugadores[i].tlApuestas > MAX_APUESTAS) {
			valida = false;
		}
	}
	
	return valida;
}


/****************************************************
* Funcion: convertirApuestaArchivo
* Parametros:
* - Apuesta origen: Apuesta del programa que se quiere convertir.
* - ApuestaArchivo &destino: Registro que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Obtiene las fichas, el numero, el color y el tipo de apuesta
* y los copia a la estructura utilizada para el archivo.
****************************************************/
void convertirApuestaArchivo(Apuesta origen, ApuestaArchivo &destino) {
	destino.fichasJugadas = getFichasJugadas(origen);
	destino.numeroApostado = getNumeroApostado(origen);
	destino.colorApostado = getColorApostado(origen);
	destino.tipoApuesta = getTipoApuesta(origen);
}

/****************************************************
* Funcion: convertirApuesta
* Parametros:
* - ApuestaArchivo origen: Apuesta recuperada del archivo.
* - Apuesta &destino: Apuesta del programa que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Copia los datos del registro a una apuesta del programa
* utilizando sus funciones de modificacion.
****************************************************/
void convertirApuesta(ApuestaArchivo origen, Apuesta &destino) {
	setFichasJugadas(destino, origen.fichasJugadas);
	setNumeroApostado(destino, origen.numeroApostado);
	setColorApostado(destino, origen.colorApostado);
	setTipoApuesta(destino, origen.tipoApuesta);
}

/****************************************************
* Funcion: convertirJugadorArchivo
* Parametros:
* - Jugador origen: Jugador que se quiere convertir.
* - JugadorArchivo &destino: Registro que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Copia el nombre a un arreglo de caracteres, limitando su
* longitud y agregando el caracter de fin de texto.
* Copia los demas datos y convierte las apuestas del jugador.
* La cantidad de apuestas debe estar previamente validada.
****************************************************/
void convertirJugadorArchivo(Jugador origen, JugadorArchivo &destino) {
   JugadorArchivo aux = {};
   
   string nombre = getNombre(origen);
   
   strncpy(aux.nombre, nombre.c_str(), MAX_NOMBRE_ARCHIVO - 1);
   aux.nombre[MAX_NOMBRE_ARCHIVO - 1] = '\0';
   aux.fichas = getFichas(origen);
   aux.tlApuestas = getTlApuestas(origen);
   aux.victorias = getVictorias(origen);
   aux.derrotas = getDerrotas(origen);
   
   for (int i = 0; i < aux.tlApuestas; i++) {
	   Apuesta ap = getApuestaEnPosicion(origen, i);
	   convertirApuestaArchivo(ap, aux.apuestas[i]);
   }
   
   destino = aux;
}

/****************************************************
* Funcion: convertirJugador
* Parametros:
* - JugadorArchivo origen: Jugador recuperado del archivo.
* - Jugador &destino: Jugador del programa que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Recupera el nombre, las fichas, las victorias y las derrotas.
* Convierte las apuestas y las coloca en sus posiciones.
* Recibe un registro previamente validado y con el nombre
* terminado en el caracter de fin de texto.
****************************************************/
void convertirJugador(JugadorArchivo origen, Jugador &destino) {
	setNombre(destino, string(origen.nombre));
	setFichas(destino, origen.fichas);
	setVictorias(destino, origen.victorias);
	setDerrotas(destino, origen.derrotas);
	setTlApuestas(destino, origen.tlApuestas);
	
	for (int i = 0; i < origen.tlApuestas; i++) {
		Apuesta ap = {};
		
		convertirApuesta(origen.apuestas[i], ap);
		
		setApuestaEnPosicion(destino, ap, i);
	}
}

/****************************************************
* Funcion: convertirNumeroArchivo
* Parametros:
* - Numero origen: Numero del historial que se quiere convertir.
* - NumeroArchivo &destino: Registro que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Obtiene el valor y el color del numero y los copia
* a la estructura utilizada para el archivo.
****************************************************/
void convertirNumeroArchivo(Numero origen, NumeroArchivo &destino) {
	destino.valor = obtenerValor(origen);
	destino.color = obtenerColor(origen);
}
  
/****************************************************
* Funcion: convertirNumero
* Parametros:
* - NumeroArchivo origen: Numero recuperado del archivo.
* - Numero &destino: Numero del programa que se inicializa.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Inicializa un numero del programa con el valor y el color
* que se recuperaron del archivo.
****************************************************/
void convertirNumero(NumeroArchivo origen,Numero &destino) {
  inicializarNumero(destino, origen.valor,origen.color);
}

/****************************************************
* Funcion: convertirSesionArchivo
* Parametros:
* - Sesion origen: Sesion del programa que se quiere guardar.
* - SesionArchivo &destino: Registro que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Copia el identificador y las cantidades de la sesion.
* Convierte los numeros del historial y los jugadores
* a las estructuras utilizadas para el archivo.
* Recibe una sesion con sus cantidades previamente validadas.
****************************************************/
void convertirSesionArchivo(Sesion origen, SesionArchivo &destino) {
   SesionArchivo aux = {};
   
   aux.idSesion = origen.idSesion;
   aux.totalGiros = origen.totalGiros;
   aux.jugadoresSesion = origen.jugadoresSesion;
   
   for (int i = 0; i < aux.totalGiros; i++) {
	   convertirNumeroArchivo(origen.historial[i], aux.historial[i]);
   }
   
   for (int i = 0; i < aux.jugadoresSesion; i++) {
	   convertirJugadorArchivo(origen.jugadores[i], aux.jugadores[i]);
   }
   
   destino = aux;
}
   
/****************************************************
* Funcion: convertirSesion
* Parametros:
* - SesionArchivo origen: Sesion recuperada del archivo.
* - Sesion &destino: Sesion del programa que recibe los datos.
* Retorna:
* - void: No devuelve un valor; modifica destino.
* Descripcion:
* Copia el identificador y las cantidades de la sesion.
* Reconstruye el historial y los jugadores mediante
* las funciones de conversion.
* Recibe un registro previamente validado.
****************************************************/
void convertirSesion(SesionArchivo origen, Sesion &destino) {
   destino.idSesion = origen.idSesion;
   destino.totalGiros = origen.totalGiros;
   destino.jugadoresSesion = origen.jugadoresSesion;
   
   for (int i = 0; i < origen.totalGiros; i++) {
	   convertirNumero(origen.historial[i], destino.historial[i]);
   }
   
   for (int i = 0; i < origen.jugadoresSesion; i++) {
	   convertirJugador(origen.jugadores[i],destino.jugadores[i]);
   }
}

/****************************************************
* Funcion: liberarLista
* Parametros:
* - ptrNodo &lista: Cabeza de la lista que se quiere vaciar.
* Retorna:
* - void: No devuelve un valor; deja lista en NULL.
* Descripcion:
* Guarda el nodo actual, avanza al siguiente y elimina
* el anterior con delete. Repite hasta vaciar la lista.
****************************************************/
void liberarLista(ptrNodo &lista) {
	while (lista != NULL) {
		ptrNodo aux = lista;
		lista = lista->sig;
		delete aux;
	}
}

/****************************************************
* Funcion: guardarSesiones
* Parametros:
* - ptrNodo lista: Cabeza de la lista de sesiones.
* - const char *nombreArchivo: Nombre o ruta del archivo destino.
* Retorna:
* - bool: true si el guardado termina sin errores detectados;
*   false si falla la validacion, apertura, escritura o cierre.
* Descripcion:
* Valida las cantidades de las sesiones y abre el archivo
* binario reemplazando su contenido anterior.
* Recorre la lista, convierte cada sesion y la escribe.
* Si la lista esta vacia, genera un archivo vacio.
* Una falla durante la escritura puede dejarlo incompleto.
****************************************************/
bool guardarSesiones(ptrNodo lista, const char *nombreArchivo) {
	bool exito = true;	
	ptrNodo actual = lista;
	
	while(actual != NULL){
		if(!sesionValida(actual->info)){
			exito = false;
		}
		actual = actual->sig;
	}
	
	if(exito){
		ofstream archivo;
		archivo.open(nombreArchivo, ios::binary);
	
		if(!archivo.is_open()){
			exito = false;
		} else{
			actual = lista;
			
			while(actual != NULL && exito){
				SesionArchivo datos = {};
				
				convertirSesionArchivo(actual->info, datos);
				
				archivo.write((char*)&datos, sizeof(datos));
				
				if (archivo.fail()) {
					exito = false;
				}
				
				actual = actual->sig;
			}
			archivo.close();
			
			if (archivo.fail()) {
				exito = false;
			}
		}
		
	}
	
	return exito;
	
}

/****************************************************
* Funcion: obtenerIdSinRepetir
* Parametros:
* - ptrNodo lista: Sesiones que ya estan en memoria.
* - ptrNodo temporal: Sesiones leidas durante esta carga.
* - int idOriginal: Identificador que viene del archivo.
* Retorna:
* - int: Identificador que no se repite entre ambas listas.
* Descripcion:
* Busca si el identificador ya existe y obtiene la ID mayor.
* Si esta repetido, devuelve la mayor mas uno.
* Si no esta repetido, conserva el identificador original.
****************************************************/
int obtenerIdSinRepetir(ptrNodo lista, ptrNodo temporal, int idOriginal) {
	bool repetida = false;
	int mayorId = 0;
	
	ptrNodo actual = lista;
	
	while (actual != NULL) {
		if (actual->info.idSesion == idOriginal) {
			repetida = true;
		}
		
		if (actual->info.idSesion > mayorId) {
			mayorId = actual->info.idSesion;
		}
		
		actual = actual->sig;
	}
	
	actual = temporal;
	
	while (actual != NULL) {
		if (actual->info.idSesion == idOriginal) {
			repetida = true;
		}
		
		if (actual->info.idSesion > mayorId) {
			mayorId = actual->info.idSesion;
		}
		
		actual = actual->sig;
	}
	
	int idElegida = idOriginal;
	
	if (repetida) {
		idElegida = mayorId + 1;
	}
	
	return idElegida;
}

/****************************************************
* Funcion: cargarSesiones
* Parametros:
* - ptrNodo &lista: Lista a la que se agregan las sesiones.
* - const char *nombreArchivo: Nombre o ruta del archivo a leer.
* Retorna:
* - bool: true si la lectura termina correctamente;
*   false si no puede abrirse o contiene registros invalidos
*   o incompletos, o se produce un error de lectura.
* Descripcion:
* Lee los registros, valida sus cantidades y los convierte
* en nodos de una lista temporal.
* Si termina correctamente, une la temporal al final
* de la lista actual. Si falla, elimina la temporal
* y conserva la lista original.
* Un archivo vacio se acepta sin agregar nodos.
* Si una ID ya existe, asigna una nueva mediante
* obtenerIdSinRepetir. No evita cargar sesiones duplicadas.
****************************************************/
bool cargarSesiones(ptrNodo &lista, const char *nombreArchivo) {
	
	bool exito = true;
	
	ptrNodo temporal = NULL;
	ptrNodo ultimo = NULL;
	
	ifstream archivo;
	archivo.open(nombreArchivo, ios::binary);
	
	if(!archivo.is_open()){
		exito = false;
	} else {
		SesionArchivo datos = {};
		
		while(exito && archivo.read((char*)&datos, sizeof(datos))){
			if (!sesionArchivoValida(datos)) {
				exito = false;
			} else{
				for(int i=0;i<datos.jugadoresSesion;i++) { 
					datos.jugadores[i].nombre[
					MAX_NOMBRE_ARCHIVO - 1
					] = '\0';
				}
				ptrNodo nuevo = new Nodo;
				convertirSesion(datos, nuevo->info);
				
				nuevo->info.idSesion = obtenerIdSinRepetir(lista, temporal, nuevo->info.idSesion);
				
				nuevo->sig = NULL;
				
				if (temporal == NULL) {
					temporal = nuevo;
				} else {
					ultimo->sig = nuevo;
				}
				
				ultimo = nuevo;
			}
		}
		if (archivo.bad() || !archivo.eof() || archivo.gcount() != 0) {
			exito = false;
		}
		
		archivo.close();
	}
	if (exito) {
		if(lista == NULL){
			lista = temporal;
		} else {
			ptrNodo actual = lista;
			
			while (actual ->sig != NULL){
				actual = actual->sig;
			}
			actual->sig = temporal;
		}
	} else {
		liberarLista(temporal);
	}
	return exito;
}


/****************************************************
* Funcion: opcionCargarArchivo
* Parametros:
* - ptrNodo &listaSesiones: Lista que recibe las sesiones.
* - string &nombreArchivo: Archivo que se utilizara al guardar.
* Retorna:
* - void: No devuelve un valor.
* Descripcion:
* Pide el nombre o ruta del archivo y llama a cargarSesiones.
* Si la carga funciona, recuerda el archivo elegido como
* destino del guardado. Muestra un mensaje con el resultado.
****************************************************/
void opcionCargarArchivo(ptrNodo &listaSesiones, string &nombreArchivo) {
	string archivoElegido;
	
	cout << "Nombre o ruta del archivo: ";
	getline(cin >> ws, archivoElegido);
	
	bool cargado = cargarSesiones(listaSesiones, archivoElegido.c_str());
	
	if (cargado) {
		nombreArchivo = archivoElegido;
		
		Mensaje("Carga completada. Las sesiones del archivo se agregaron a la lista.");
	}
	else {
		Mensaje("No se pudo cargar el archivo. Se conservaron las sesiones actuales.");
	}
}

/****************************************************
* Funcion: guardarAlSalir
* Parametros:
* - ptrNodo lista: Lista completa de sesiones a guardar.
* - string &nombreArchivo: Nombre o ruta del archivo destino.
* Retorna:
* - bool: true si pudo guardar; false si no pudo generar
*   el nombre automatico o fallo el guardado.
* Descripcion:
* Si el nombre esta vacio, genera uno con fecha y hora
* en formato AAAA-MM-DD-HH-MM-SS.bin.
* Llama a guardarSesiones y muestra el resultado.
* Guarda los datos, pero no termina el programa.
****************************************************/
bool guardarAlSalir(ptrNodo lista, string &nombreArchivo) {
	bool exito = true;
	
	if (nombreArchivo.empty()) {
		time_t ahora;
		time(&ahora);
		
		struct tm *fecha = localtime(&ahora);
		
		if (fecha == NULL) {
			exito = false;
		} else {
			char nombreAutomatico[32];
			
			size_t cantidad = strftime(nombreAutomatico, sizeof(nombreAutomatico), 
									   "%Y-%m-%d-%H-%M-%S.bin", fecha);
			
			if (cantidad == 0) {
				exito = false;
			} else {
				nombreArchivo = nombreAutomatico;
			}
		}
	}
	
	if (exito) {
		exito = guardarSesiones(lista, nombreArchivo.c_str());
	}
	
	if (exito) {
		Mensaje("Sesiones guardadas correctamente");
	} else {
		Mensaje("No se pudo guardar. El programa seguira abierto");
	}
	
	cout << "Presiona ENTER para continuar...";
	cin.ignore();
	cin.get();
	
	return exito;
}

/****************************************************
* Funcion: opcionSalir
* Parametros:
* - ptrNodo lista: Sesiones que se guardaran al confirmar.
* - string &nombreArchivo: Archivo que se utilizara al guardar.
* Retorna:
* - bool: true si se confirma la salida y el guardado funciona;
*   false si se cancela o falla el guardado.
* Descripcion:
* Pide confirmar la salida con X o x.
* Si se confirma, llama a guardarAlSalir.
* Devuelve el resultado para que main decida si termina
* el programa o vuelve al menu.
****************************************************/
bool opcionSalir(ptrNodo lista, string &nombreArchivo){
	const int ANCHO_VENTANA = 150;
	bool salir = false;
	char confirmacion;
	
	cout << centrar("¿Estas seguro que queres salir?", ANCHO_VENTANA) << endl;
	cout << centrar("Escribi X para confirmar u otra letra para volver: ", ANCHO_VENTANA);
	
	cin >> confirmacion;
	
	if(confirmacion == 'x' || confirmacion == 'X'){
		salir = guardarAlSalir(lista, nombreArchivo);
	}
	return salir;
}
