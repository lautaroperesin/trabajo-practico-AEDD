#include "numero.h"
#include "presentacion.h"
#include <iomanip>
using namespace std;

/**
* ****************************************************************************************
* Función: inicializarNumero
*
* Parámetros:
* - Numero &n : Referencia al objeto Numero que será inicializado.
* - int valor : Valor numérico que se asignará al objeto.
* - char color : Carácter que representa el color del número.
*
* Retorna:
* - void : No retorna ningún valor.
*
* Descripción:
* Inicializa los atributos del parameto Numero con los valores recibidos y valida
* la consistencia de los datos ingresados.
* ****************************************************************************************
*/

void inicializarNumero(Numero &n, int valor, char color){
	if((valor >= 0 && valor <= 36) && (color == 'R' || color == 'V' || color == 'N')){
		n.valor = valor;
		n.color = color;
	}
	return; 
}

/**
* ****************************************************************************************
* Función: obtenerValor
*
* Parámetros:
* - Numero n : Objeto Numero del cual se desea obtener el valor numérico.
*
* Retorna:
* - int : Valor numérico almacenado en el objeto Numero.
*
* Descripción:
* Accede al atributo que contiene el valor numérico del objeto y lo retorna.
* ****************************************************************************************
*/

int obtenerValor(Numero n){ 
	return n.valor; 
}
	
/**
* ****************************************************************************************
* Función: obtenerColor
*
* Parámetros:
* - Numero n : Objeto Numero del cual se desea obtener el color.
*
* Retorna:
* - char : Carácter que representa el color almacenado en el objeto Numero.
*
* Descripción:
* Accede al atributo que contiene el color del objeto y lo retorna.
* ****************************************************************************************
*/
char obtenerColor(Numero n){ 
	return n.color; 
}
	
/**
* ****************************************************************************************
* Función: obtenerParidad
*
* Parámetros:
* - Numero n : Objeto Numero cuyo valor numérico será analizado.
*
* Retorna:
* - int : 0 si el valor no es par ni impar, 1 si es par y 2 si es impar.
*
* Descripción:
* Analiza el valor numérico almacenado en el objeto y determina su paridad,
* retornando 1 para valores pares, 2 para valores impares y 0 cuando el valor
* no corresponde a una de estas categorías.
* ****************************************************************************************
*/
int obtenerParidad(Numero n){
	int valor = 0;
	if((n.valor % 2) == 0 && n.valor != 0) {
		valor = 1;
	} else if((n.valor % 2)!= 0){
		valor = 2;
	}
	return valor; 
}
	
/**
* ****************************************************************************************
* Función: guardarGiro
*
* Parámetros:
* - Numero numero[]: Pasaje por referncia al vector numeros.
* - Numero nuevo: Copia del numero al cual guardar en el vector.
* - int pos: Valor numerico de la posision en la que se coloca el numero nuevo.
*
* Retorna:
* - void : No retorna ningun valor.
*
* Descripción:
* Guarda los valores que salieron en el ultimo giro.
* ****************************************************************************************
*/
void guardarGiro(Numero numeros[], Numero nuevo, int pos){
	numeros[pos]=nuevo;
}
/**
* ****************************************************************************************
* Función: mostrarHistorial
*
* Parámetros:
* - Numero numeros[]: Pasaje por referncia al vector numeros.
* - int totalGiros: Valor numerico que refiere a la cantidad de giros totales.
*
* Retorna:
* - void : No retorna ningun valor.
*
* Descripción:
* Muestra en pantalla la secuencia numeros ganadores en orden.
* ****************************************************************************************
*/
void mostrarHistorial(Numero numeros[],int totalGiros){
	color(15);
	cout<<centrar("Historial de giros",150);
	cout<<endl;
	borde(8);
	colorNormal();
	
	cout<<centrar ("Numero de giro", 37);
	cout<<centrar ("Valor", 37);
	cout<<centrar ("color", 37);
	cout<<centrar ("paridad", 37);
	cout<<endl;
	for(int i=0;i<totalGiros;i++) { 
		string valor= to_string(obtenerValor(numeros[i]));
		char colorN=obtenerColor(numeros[i]);
		int paridad=obtenerParidad(numeros[i]);
		cout<<centrar (to_string(i+1), 37);
		cout<<centrar (valor, 37);
		
		if(colorN=='V'){
			color(2);
			cout<<centrar ("Verde", 37);
			colorNormal();
		}
		else if(colorN=='N'){
			color(15);
			cout<<centrar ("Negro",37);
			colorNormal();
		}
		else{
			color(4);
			cout<<centrar ("Rojo", 37);
			colorNormal();
		}
		
		if(paridad==0){
			cout<<centrar("No par, no impar", 37);
		}
		else if(paridad==1){
			cout<<centrar("Par", 37);
		}
		else{
			cout<<centrar("Impar", 37);
		}
		cout<<endl;
	}
}
	
/**
* ****************************************************************************************
* Función: mostrarEstadisticas
*
* Parámetros:
* - Numero numeros[]: Pasaje por referncia al vector numeros.
* - int totalGiros: Valor numerico que refiere a la cantidad de giros totales.
*
* Retorna:
* - void : No retorna ningun valor.
*
* Descripción:
* Muestra en pantalla las estadisticas generales del juego.
* ****************************************************************************************
*/
void mostrarEstadisticas(Numero numeros[],int totalGiros){
	float pares=0, impares=0, ceros=0, rojos=0, negros=0;
	
	for(int i=0;i<totalGiros;i++) { 
		char colorN=obtenerColor(numeros[i]);
		int paridad=obtenerParidad(numeros[i]);
		if(paridad==0){
			ceros++;
		}
		else if(paridad==1){
			pares++;
			if(colorN=='R'){
				rojos++;
			}
			else if(colorN=='N'){
				negros++;
			}
		}
		else{
			impares++;
			if(colorN=='R'){
				rojos++;
			}
			else if(colorN=='N'){
				negros++;
			}
		}
	}
	cout<<fixed<<setprecision(2);
	color(15);
	cout<<"Total de giros: "<<totalGiros<<endl;
	cout<<"Porcentaje de pares: "<<(100*pares)/totalGiros<<"%"<<endl;
	cout<<"Porcentaje de impares: "<<(100*impares)/totalGiros<<"%"<<endl;
	color(2);
	cout<<"Porcentaje de ceros: "<<(100*ceros)/totalGiros<<"%"<<endl;
	color(4);
	cout<<"Cantidad de rojos: "<<rojos<<endl;
	color(15);
	cout<<"Cantidad de negros: "<<negros<<endl;
}
