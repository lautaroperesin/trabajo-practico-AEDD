#ifndef PRESENTACION_H
#define PRESENTACION_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
void color(int textoColor);
void colorFondo(int textoColor, int fondoColor);
void colorNormal();
void tamanioVentana(int columnas, int filas);
void tamanioPixeles(int ancho, int alto);
void maximizar() ;
void pantallaCompleta();
void ocultarCursor();
void mostrarCursor();
void esperar(int milisegundos);
void limpiarPantalla();
string centrar(string texto, int ancho);
void gotoxy(int x, int y);
void linea(string texto, int colorTexto, int colorMarco);
void borde(int colorMarco);
void Presentacion();
void Selector(bool condicion, bool haySesiones);
void Mensaje(string texto);
void Despedida();
void generarRuleta();
void bola(int ganador);
void submenu();
#endif
