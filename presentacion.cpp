#define _WIN32_WINNT 0x0600
#include "presentacion.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
/**
* ****************************************************************************************
* Constante: colores

* Descripcion:
* Se utilizan para simplificar los cambios de color de caracteres y fondos
* ****************************************************************************************
*/
const int NEGRO         = 0;
const int AZUL          = 1;
const int VERDE         = 2;
const int AGUAMARINA    = 3;
const int ROJO          = 4;
const int PURPURA       = 5;
const int AMARILLO      = 6;
const int BLANCO        = 7;
const int GRIS          = 8;
const int AZUL_CLARO    = 9;
const int VERDE_CLARO   = 10;
const int CIAN_CLARO    = 11;
const int ROJO_CLARO    = 12;
const int MAGENTA       = 13;
const int AMARILLO_CLARO= 14;
const int BLANCO_BRILL  = 15;

/**
* ****************************************************************************************
* Constante: medidas

* Descripcion:
* Es el ancho configurado para la aplicacion. 
* Se utiliza tanto para centrar.
* ****************************************************************************************
*/
const int ANCHO = 148;

/**
* ****************************************************************************************
* Funcion: color
*
* Parametros:
* - int textoColor.
*
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Cambia el color de fuente a partir de la funcion, hasta que se vuelva a utilizar
* ****************************************************************************************
*/
void color(int textoColor) {
	HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consola, textoColor);
}

/**
* ****************************************************************************************
* Funcion: colorFondo
*
* Parametros:
* - int textoColor.
* - int fondoColor.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Cambia el color de fuente y el fondo a partir de la funcion, 
* hasta que se vuelva a utilizar
* ****************************************************************************************
*/
void colorFondo(int textoColor, int fondoColor) {
	HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consola, fondoColor * 16 + textoColor);
}

/**
* ****************************************************************************************
* Funcion: colorNormal
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Reestablece el color del texto y del fondo al predeterminado.
* ****************************************************************************************
*/
void colorNormal() {
	colorFondo(BLANCO, NEGRO);
}

/**
* ****************************************************************************************
* Funcion: tamanioVentana
*
* Parametros:
* - int columnas: El ancho al que se quiere cambiar.
* - int filas: El alto al que se quiere cambiar.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Ajusta el tamanio de la ventana para una mejor presentacion.
* ****************************************************************************************
*/
void tamanioVentana(int columnas, int filas) {
	HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Reduce la ventana al minimo para poder tocar el buffer
	SMALL_RECT minimo = {0, 0, 1, 1};
	SetConsoleWindowInfo(consola, TRUE, &minimo);
	
	// Ajusta el buffer 
	COORD buffer;
	buffer.X = columnas;
	buffer.Y = filas;
	SetConsoleScreenBufferSize(consola, buffer);
	
	//Agranda la ventana al tamanio necesitado
	SMALL_RECT ventana = {0, 0, (SHORT)(columnas - 1), (SHORT)(filas - 1)};
	SetConsoleWindowInfo(consola, TRUE, &ventana);
}

/**
* ****************************************************************************************
* Funcion: tamanioPixeles
*
* Parametros:
* - int ancho: El ancho al que se quiere cambiar.
* - int alto: El alto al que se quiere cambiar.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Cambia el tamanio de la ventana en pixeles y la centra
* ****************************************************************************************
*/
void tamanioPixeles(int ancho, int alto) {
	HWND ventana = GetConsoleWindow();
	int pantallaX = GetSystemMetrics(SM_CXSCREEN);
	int pantallaY = GetSystemMetrics(SM_CYSCREEN);
	int x = (pantallaX - ancho) / 2;
	int y = (pantallaY - alto) / 2;
	MoveWindow(ventana, x, y, ancho, alto, TRUE);
}
/**
* ****************************************************************************************
* Funcion: maximizar
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Maximiza la ventana de la consola
* ****************************************************************************************
*/
void maximizar() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

/**
* ****************************************************************************************
* Funcion: pantallaCompleta
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Simula la combinacion ALT + ENTER.
* ****************************************************************************************
*/
void pantallaCompleta() {
	keybd_event(VK_MENU,   0, 0, 0);              // ALT abajo
	keybd_event(VK_RETURN, 0, 0, 0);              // ENTER abajo
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU,   0, KEYEVENTF_KEYUP, 0);
	Sleep(300);   // le damos tiempo a la consola a redibujarse
}

/**
* ****************************************************************************************
* Funcion: ocultarCursor
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Oculta el cursor parpadeante.
* ****************************************************************************************
*/
void ocultarCursor() {
	HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(consola, &cursor);
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(consola, &cursor);
}

/**
* ****************************************************************************************
* Funcion: mostrarCursor
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Vuelve a mostrar el cursor.
* ****************************************************************************************
*/
void mostrarCursor() {
	HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(consola, &cursor);
	cursor.bVisible = TRUE;
	SetConsoleCursorInfo(consola, &cursor);
}

/**
* ****************************************************************************************
* Funcion: esperar
*
* Parametros:
* - int milisegundos: Tiempo en milisegundos a esperar.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Espera la cantidad de milisegundos ingresada.
* ****************************************************************************************
*/
void esperar(int milisegundos) {
	Sleep(milisegundos);
}
/**
* ****************************************************************************************
* Funcion: limpiarPantalla
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Elimina todos los elementos en pantalla.
* ****************************************************************************************
*/
void limpiarPantalla() {
	system("cls");
}
/**
* ****************************************************************************************
* Funcion: centrar
*
* Parametros:
* - string texto: El texto a centrar.
* - int ancho: El espacio en el que se centra el texto
* Retorna:
* - string : Retorna el texto centrado.
* Descripcion:
* Se utiliza para centrar el texto en pantalla, para una mejor presentacion.
* ****************************************************************************************
*/
string centrar(string texto, int ancho) {
	int largo = texto.length();
	if (largo >= ancho) return texto;
	int izquierda = (ancho - largo) / 2;
	int derecha = ancho - largo - izquierda;
	return string(izquierda, ' ') + texto + string(derecha, ' ');
}

/**
* ****************************************************************************************
* Funcion: gotoxy
*
* Parametros:
* - int x: La columna a la cual mover el cursor.
* - int y: La fila a la cual mover el cursor.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Mueve el cursor a la columna x, fila y.
* ****************************************************************************************
*/
void gotoxy(int x, int y) {
	COORD posicion;
	posicion.X = x;
	posicion.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicion);
}

/**
* ****************************************************************************************
* Funcion: linea
*
* Parametros:
* - string texto: Texto que esta dentro del recuadro.
* - int colorTexto: Color del texto.
* - int colorMarco: Color del marco.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime una linea del marco, los bordes en un color y el texto en otro.
* ****************************************************************************************
*/
void linea(string texto, int colorTexto, int colorMarco) {
	color(colorMarco);   
	cout <<"|";
	color(colorTexto);   
	cout <<centrar(texto, ANCHO);
	color(colorMarco);   
	cout <<"|"<< endl;
}

/**
* ****************************************************************************************
* Funcion: borde
*
* Parametros:
* - int colorMarco: Color del marco.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime los bordes horizontales.
* ****************************************************************************************
*/
void borde(int colorMarco) {
	color(colorMarco);
	cout << "+" << string(ANCHO, '=') << "+" << endl;
}
/**
* ****************************************************************************************
* Funcion: presentacion
*
* Parametros:
* - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime la presentacion del programa.
* ****************************************************************************************
*/
void Presentacion(){
	borde(VERDE);
	linea("",BLANCO,VERDE);
	linea("",BLANCO,VERDE);
	linea("RRRR  U   U L     EEEE TTTTT EEEE  SSS    CCC      A     ",BLANCO_BRILL,VERDE);
	linea("R   R U   U L     E      T   E    S      C        A A    ",BLANCO_BRILL,VERDE);
	linea("RRRR  U   U L     EEEE   T   EEEE  SSS   C       A   A   ",BLANCO_BRILL,VERDE);
	linea("R  R  U   U L     E      T   E        S  C      AAAAAAA  ",BLANCO_BRILL,VERDE);
	linea("R   R  UUU  LLLLL EEEE   T   EEEE  SSS    CCC  A       A ",BLANCO_BRILL,VERDE);
	linea("",BLANCO,VERDE);
	linea("",BLANCO,VERDE);
	borde(VERDE);
	linea("",BLANCO,VERDE);
	linea("Desarrollado por Cian Federico, Oggier Fabricio y Peresin Lautaro",CIAN_CLARO,VERDE);
	linea("grupo: cout<< \" idea nombre\";",CIAN_CLARO,VERDE);
	linea("",BLANCO,VERDE);
	linea("",BLANCO,VERDE);
	linea("UTN FRSF",AZUL,VERDE);
	linea("Ingenieria en sistemas Comision B",AZUL,VERDE);
	linea("Algoritmos y Estructuras de Datos",AZUL,VERDE);
	linea("",BLANCO,VERDE);
	borde(VERDE);
}

/**
* ****************************************************************************************
* Funcion: Selector
*
* Parametros:
* - bool condicion: Condicion de acceso.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime el menu de seleccion de opciones.
* ****************************************************************************************
*/
void Selector(bool condicion){
	borde(GRIS);
	linea("",BLANCO,GRIS);
	linea("RULETESCA",BLANCO,GRIS);
	linea("",BLANCO,GRIS);
	borde(GRIS);
	if(!condicion){
		linea("1.- Iniciar nueva sesion de ruleta",CIAN_CLARO,GRIS);
		linea("2.- Consultar estado de jugadores",GRIS,GRIS);
		linea("3.- Mostrar historial de giros",GRIS,GRIS);
		linea("4.- Mostrar estadisticas de la sesion",GRIS,GRIS);
	}
	else{
		linea("1.- Iniciar nueva sesion de ruleta",GRIS,GRIS);
		linea("2.- Consultar estado de jugadores",CIAN_CLARO,GRIS);
		linea("3.- Mostrar historial de giros",CIAN_CLARO,GRIS);
		linea("4.- Mostrar estadisticas de la sesion",CIAN_CLARO,GRIS);
	}
	linea("5.- Ordenar sesiones segun cantidad de giros",GRIS,GRIS);
	linea("6.- Analizar sesiones historicas",GRIS,GRIS);
	linea("7.- Carga de Archivo",GRIS,GRIS);
	linea("X.- Salir de la aplicacion",ROJO,GRIS);
	linea("",BLANCO,GRIS);
	linea("Ingrese una opcion:",BLANCO_BRILL,GRIS);
	gotoxy(150 / 2 + 10 ,14);
}
	
/**
* ****************************************************************************************
* Funcion: Mensaje
*
* Parametros:
* - string texto: Texto a imprimir.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime el mensaje centrado, espera un enter y limpia la pantalla.
* ****************************************************************************************
*/
void Mensaje(string texto){
	texto=centrar(texto,ANCHO);
	color(BLANCO_BRILL);
	cout<<texto;
	cin.ignore();
	cin.get();
	limpiarPantalla();
	colorNormal();
}
	
/**
* ****************************************************************************************
* Funcion: Despedida
*
* Parametros:
*  - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime la despedida del programa.
* ****************************************************************************************
*/
	
void Despedida(){
	cout<<endl<<endl;
	color(VERDE);
	cout<<centrar("RRRR  U   U L     EEEE TTTTT EEEE  SSS    CCC      A     ",ANCHO)<<endl;
	cout<<centrar("R   R U   U L     E      T   E    S      C        A A    ",ANCHO)<<endl;
	cout<<centrar("RRRR  U   U L     EEEE   T   EEEE  SSS   C       A   A   ",ANCHO)<<endl;
	cout<<centrar("R  R  U   U L     E      T   E        S  C      AAAAAAA  ",ANCHO)<<endl;
	cout<<centrar("R   R  UUU  LLLLL EEEE   T   EEEE  SSS    CCC  A       A ",ANCHO)<<endl;
	cout<<endl<<endl;
	color(BLANCO_BRILL);
	cout<<centrar("Gracias por jugar :)",ANCHO);
	
}
	
/**
* ****************************************************************************************
* Funcion: generarRuleta
*
* Parametros:
*  - vacio, no lo requiere.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime la ruleta, para su uso en el programa.
* ****************************************************************************************
*/
void generarRuleta(){
	
	color(BLANCO_BRILL);
	
	cout << centrar("#####", ANCHO) << endl;
	cout << centrar("##########################", ANCHO) << endl;
	cout << centrar("######                            ######", ANCHO) << endl;
	cout << centrar("####                                        ####", ANCHO) << endl;
	cout << centrar("###                                                ###", ANCHO) << endl;
	cout << centrar("##                                                        ##", ANCHO) << endl;
	cout << centrar("###                                                            ###", ANCHO) << endl;
	cout << centrar("##                                                                  ##", ANCHO) << endl;
	cout << centrar("###                                                                      ###", ANCHO) << endl;
	cout << centrar("##                                                                          ##", ANCHO) << endl;
	cout << centrar("##                                                                              ##", ANCHO) << endl;
	cout << centrar("##                                                                                  ##", ANCHO) << endl;
	cout << centrar("##                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                        ##", ANCHO) << endl;
	cout << centrar("##                                                                                          ##", ANCHO) << endl;
	cout << centrar("##                                                                                            ##", ANCHO) << endl;
	cout << centrar("##                                                                                              ##", ANCHO) << endl;
	cout << centrar("##                                                                                                ##", ANCHO) << endl;
	cout << centrar("##                                                                                                  ##", ANCHO) << endl;
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                                  ##", ANCHO) << endl;
	cout << centrar("##                                                                                                ##", ANCHO) << endl;
	cout << centrar("##                                                                                              ##", ANCHO) << endl;
	cout << centrar("##                                                                                            ##", ANCHO) << endl;
	cout << centrar("##                                                                                          ##", ANCHO) << endl;
	cout << centrar("##                                                                                        ##", ANCHO) << endl;
	cout << centrar("##                                                                                    ##", ANCHO) << endl;
	cout << centrar("##                                                                                  ##", ANCHO) << endl;
	cout << centrar("##                                                                              ##", ANCHO) << endl;
	cout << centrar("##                                                                          ##", ANCHO) << endl;
	cout << centrar("###                                                                      ###", ANCHO) << endl;
	cout << centrar("##                                                                  ##", ANCHO) << endl;
	cout << centrar("###                                                            ###", ANCHO) << endl;
	cout << centrar("##                                                        ##", ANCHO) << endl;
	cout << centrar("###                                                ###", ANCHO) << endl;
	cout << centrar("####                                        ####", ANCHO) << endl;
	cout << centrar("######                            ######", ANCHO) << endl;
	cout << centrar("##########################", ANCHO) << endl;
	cout << centrar("#####", ANCHO) << endl;	
	
	
	colorFondo(BLANCO_BRILL, VERDE_CLARO);
	gotoxy(74, 4);
	cout << "0";
	
	colorFondo(BLANCO_BRILL, ROJO);
	
	gotoxy(80, 5);
	cout << "32";
	
	gotoxy(94, 7);
	cout << "19";
	
	gotoxy(105, 10);
	cout << "21";
	
	gotoxy(113, 15);
	cout << "25";
	
	gotoxy(116, 21);
	cout << "34";
	
	gotoxy(114, 27);
	cout << "27";
	
	gotoxy(108, 32);
	cout << "36";
	
	gotoxy(97, 36);
	cout << "30";
	
	gotoxy(84, 39);
	cout << "23";
	
	gotoxy(70, 39);
	cout << "5";
	
	gotoxy(55, 38);
	cout << "16";
	
	gotoxy(44, 35);
	cout << "1";
	
	gotoxy(35, 30);
	cout << "14";
	
	gotoxy(31, 24);
	cout << "9";
	
	gotoxy(31, 18);
	cout << "18";
	
	gotoxy(37, 13);
	cout << "7";
	
	gotoxy(46, 8);
	cout << "12";
	
	gotoxy(59, 5);
	cout << "3";
	
	
	colorFondo(BLANCO_BRILL, NEGRO);
	
	gotoxy(87, 5);
	cout << "15";
	
	gotoxy(101, 8);
	cout << "4";
	
	gotoxy(110, 13);
	cout << "2";
	
	gotoxy(115, 18);
	cout << "17";
	
	gotoxy(116, 24);
	cout << "6";
	
	gotoxy(111, 30);
	cout << "13";
	
	gotoxy(103, 35);
	cout << "11";
	
	gotoxy(91, 38);
	cout << "8";
	
	gotoxy(77, 39);
	cout << "10";
	
	gotoxy(62, 39);
	cout << "24";
	
	gotoxy(49, 36);
	cout << "33";
	
	gotoxy(38, 32);
	cout << "20";
	
	gotoxy(32, 27);
	cout << "31";
	
	gotoxy(30, 21);
	cout << "22";
	
	gotoxy(33, 15);
	cout << "29";
	
	gotoxy(41, 10);
	cout << "28";
	
	gotoxy(52, 7);
	cout << "35";
	
	gotoxy(66, 5);
	cout << "26";
	
	colorNormal();
	
	gotoxy(69, 22);
	cout << "RULETESCA";
}

/**
* ****************************************************************************************
* Funcion: bola
*
* Parametros:
*  - int ganador: El numero en el que finaliza el programa.
* Retorna:
* - void : No retorna ningun valor.
* Descripcion:
* Imprime la bola, y muestra el numero ganador.
* ****************************************************************************************
*/
	void bola(int ganador){
		
		srand(time(0));
		int velocidad = 100 + rand() % 80;
		bool condicion = true;
		color(BLANCO_BRILL);
		
		while(condicion){
			
			switch(velocidad % 37){
				
			case 0:
				gotoxy(74, 2);   // 0
				cout << "O";
				
				if(velocidad < 38 and ganador == 0){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(74, 2);
					cout << " ";
				}
				break;
				
			case 1:
				gotoxy(82, 2);   // 32
				cout << "O";
				
				if(velocidad < 38 and ganador == 32){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(82, 2);
					cout << " ";
				}
				break;
				
			case 2:
				gotoxy(89, 3);   // 15
				cout << "O";
				
				if(velocidad < 38 and ganador == 15){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(89, 3);
					cout << " ";
				}
				break;
				
			case 3:
				gotoxy(97, 5);   // 19
				cout << "O";
				
				if(velocidad < 38 and ganador == 19){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(97, 5);
					cout << " ";
				}
				break;
				
			case 4:
				gotoxy(104, 6);   // 4
				cout << "O";
				
				if(velocidad < 38 and ganador == 4){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(104, 6);
					cout << " ";
				}
				break;
				
			case 5:
				gotoxy(110, 9);   // 21
				cout << "O";
				
				if(velocidad < 38 and ganador == 21){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(110, 9);
					cout << " ";
				}
				break;
				
			case 6:
				gotoxy(114, 12);   // 2
				cout << "O";
				
				if(velocidad < 38 and ganador == 2){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(114, 12);
					cout << " ";
				}
				break;
				
			case 7:
				gotoxy(118, 15);   // 25
				cout << "O";
				
				if(velocidad < 38 and ganador == 25){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(118, 15);
					cout << " ";
				}
				break;
				
			case 8:
				gotoxy(120, 18);   // 17
				cout << "O";
				
				if(velocidad < 38 and ganador == 17){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(120, 18);
					cout << " ";
				}
				break;
				
			case 9:
				gotoxy(121, 21);   // 34
				cout << "O";
				
				if(velocidad < 38 and ganador == 34){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(121, 21);
					cout << " ";
				}
				break;
				
			case 10:
				gotoxy(121, 25);   // 6
				cout << "O";
				
				if(velocidad < 38 and ganador == 6){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(121, 25);
					cout << " ";
				}
				break;
				
			case 11:
				gotoxy(119, 28);   // 27
				cout << "O";
				
				if(velocidad < 38 and ganador == 27){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(119, 28);
					cout << " ";
				}
				break;
				
			case 12:
				gotoxy(116, 31);   // 13
				cout << "O";
				
				if(velocidad < 38 and ganador == 13){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(116, 31);
					cout << " ";
				}
				break;
				
			case 13:
				gotoxy(112, 34);   // 36
				cout << "O";
				
				if(velocidad < 38 and ganador == 36){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(112, 34);
					cout << " ";
				}
				break;
				
			case 14:
				gotoxy(107, 36);   // 11
				cout << "O";
				
				if(velocidad < 38 and ganador == 11){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(107, 36);
					cout << " ";
				}
				break;
				
			case 15:
				gotoxy(100, 39);   // 30
				cout << "O";
				
				if(velocidad < 38 and ganador == 30){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(100, 39);
					cout << " ";
				}
				break;
				
			case 16:
				gotoxy(93, 40);   // 8
				cout << "O";
				
				if(velocidad < 38 and ganador == 8){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(93, 40);
					cout << " ";
				}
				break;
				
			case 17:
				gotoxy(86, 41);   // 23
				cout << "O";
				
				if(velocidad < 38 and ganador == 23){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(86, 41);
					cout << " ";
				}
				break;
				
			case 18:
				gotoxy(78, 42);   // 10
				cout << "O";
				
				if(velocidad < 38 and ganador == 10){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(78, 42);
					cout << " ";
				}
				break;
				
			case 19:
				gotoxy(69, 42);   // 5
				cout << "O";
				
				if(velocidad < 38 and ganador == 5){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(69, 42);
					cout << " ";
				}
				break;
				
			case 20:
				gotoxy(61, 41);   // 24
				cout << "O";
				
				if(velocidad < 38 and ganador == 24){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(61, 41);
					cout << " ";
				}
				break;
				
			case 21:
				gotoxy(54, 40);   // 16
				cout << "O";
				
				if(velocidad < 38 and ganador == 16){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(54, 40);
					cout << " ";
				}
				break;
				
			case 22:
				gotoxy(47, 39);   // 33
				cout << "O";
				
				if(velocidad < 38 and ganador == 33){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(47, 39);
					cout << " ";
				}
				break;
				
			case 23:
				gotoxy(40, 36);   // 1
				cout << "O";
				
				if(velocidad < 38 and ganador == 1){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(40, 36);
					cout << " ";
				}
				break;
				
			case 24:
				gotoxy(35, 34);   // 20
				cout << "O";
				
				if(velocidad < 38 and ganador == 20){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(35, 34);
					cout << " ";
				}
				break;
				
			case 25:
				gotoxy(31, 31);   // 14
				cout << "O";
				
				if(velocidad < 38 and ganador == 14){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(31, 31);
					cout << " ";
				}
				break;
				
			case 26:
				gotoxy(28, 28);   // 31
				cout << "O";
				
				if(velocidad < 38 and ganador == 31){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(28, 28);
					cout << " ";
				}
				break;
				
			case 27:
				gotoxy(26, 25);   // 9
				cout << "O";
				
				if(velocidad < 38 and ganador == 9){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(26, 25);
					cout << " ";
				}
				break;
				
			case 28:
				gotoxy(26, 21);   // 22
				cout << "O";
				
				if(velocidad < 38 and ganador == 22){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(26, 21);
					cout << " ";
				}
				break;
				
			case 29:
				gotoxy(27, 18);   // 18
				cout << "O";
				
				if(velocidad < 38 and ganador == 18){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(27, 18);
					cout << " ";
				}
				break;
				
			case 30:
				gotoxy(29, 15);   // 29
				cout << "O";
				
				if(velocidad < 38 and ganador == 29){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(29, 15);
					cout << " ";
				}
				break;
				
			case 31:
				gotoxy(33, 12);   // 7
				cout << "O";
				
				if(velocidad < 38 and ganador == 7){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(33, 12);
					cout << " ";
				}
				break;
				
			case 32:
				gotoxy(37, 9);   // 28
				cout << "O";
				
				if(velocidad < 38 and ganador == 28){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(37, 9);
					cout << " ";
				}
				break;
				
			case 33:
				gotoxy(43, 6);   // 12
				cout << "O";
				
				if(velocidad < 38 and ganador == 12){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(43, 6);
					cout << " ";
				}
				break;
				
			case 34:
				gotoxy(50, 5);   // 35
				cout << "O";
				
				if(velocidad < 38 and ganador == 35){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(50, 5);
					cout << " ";
				}
				break;
				
			case 35:
				gotoxy(58, 3);   // 3
				cout << "O";
				
				if(velocidad < 38 and ganador == 3){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(58, 3);
					cout << " ";
				}
				break;
				
			case 36:
				gotoxy(65, 2);   // 26
				cout << "O";
				
				if(velocidad < 38 and ganador == 26){
					condicion = false;
				}
				else{
					esperar(1000 / velocidad);
					gotoxy(65, 2);
					cout << " ";
				}
				break;
			}
			
			velocidad--;
		}
		
		esperar(1000);
	}
