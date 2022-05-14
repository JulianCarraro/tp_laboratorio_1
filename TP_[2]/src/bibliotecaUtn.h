/*
 * bibliotecaUtn.h
 *
 *  Created on: 21 abr. 2022
 *      Author: carra
 */

#ifndef BIBLIOTECAUTN_H_
#define BIBLIOTECAUTN_H_

#include "ArrayPassenger.h"
#include "ArrayFlights.h"

int mostrarArrayChar(char array[], int len);

int ordenarArray(int pArray[], int len);

int mostrarArrayInt(int array[], int len);

int validarNumero(char cadena[]);

int getInt(int *pNumeroIngresado, char *mensaje, char *mensajeError, int maximo,
		int minimo, int maximoDeReintentos);

int menuPrincipal(int * opcionMenu);

int getArrayInt(int array[], int len, char * mensaje, char * mensajeError,int maximoReintentos);

int getArrayChar(char array[], int len, char * mensaje, char * mensajeError,int maximoReintentos);

int getChars(char array[], int len, char * mensaje, char * mensajeError,int maximoReintentos);

int getNumero(int * pResultado);

int getNumeroFlotante(float * pResultado);

int validarNumeroFlotante(char * cadena);

int myGets(char* cadena, int len);

int borrarImpares(int cadena[], int len);

int mostrarNumeros(int array[], int len);

int ordenarArray(int pArray[], int len);

int buscarCharEnArray(char array[], int len, char charABuscar[]);

int validarLetras(char cadena[]);

int validarDni(char cadena[]);

int getDni(int * dni);

int validarFlyCode(char flyCode[]);

int getCodeChar(char array[], int len, char * mensaje, char * mensajeError,int maximoReintentos);

int getFloat(float *pNumeroIngresado, char *mensaje, char *mensajeError, int maximo,
		int minimo, int maximoDeReintentos);

int menuModificaciones(int * opcionMenu);

int menuInformar(int * opcionMenu);

//int buscarArrayCharEnArray(char array[], char charABuscar[]);

int buscarArrayCharEnArray(Passenger * array, int len, char charABuscar[]);

#endif /* BIBLIOTECAUTN_H_ */
