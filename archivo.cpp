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


void convertirApuestaArchivo(Apuesta origen, ApuestaArchivo &destino) {
	destino.fichasJugadas = getFichasJugadas(origen);
	destino.numeroApostado = getNumeroApostado(origen);
	destino.colorApostado = getColorApostado(origen);
	destino.tipoApuesta = getTipoApuesta(origen);
}

void convertirApuesta(ApuestaArchivo origen, Apuesta &destino) {
	setFichasJugadas(destino, origen.fichasJugadas);
	setNumeroApostado(destino, origen.numeroApostado);
	setColorApostado(destino, origen.colorApostado);
	setTipoApuesta(destino, origen.tipoApuesta);
}

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
void convertirNumeroArchivo(Numero origen, NumeroArchivo &destino) {
	destino.valor = obtenerValor(origen);
	destino.color = obtenerColor(origen);
}
  
void convertirNumero(NumeroArchivo origen,Numero &destino) {
  inicializarNumero(destino, origen.valor,origen.color);
}

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

void liberarLista(ptrNodo &lista) {
	while (lista != NULL) {
		ptrNodo aux = lista;
		lista = lista->sig;
		delete aux;
	}
}

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
