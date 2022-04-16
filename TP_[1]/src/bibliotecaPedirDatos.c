/*
 * bibliotecaPedirDatos.c
 *
 *  Created on: 7 abr. 2022
 *      Author: carra
 */

#include <stdio.h>
#include <stdlib.h>
#include "bibliotecaPedirDatos.h"

/// @brief --> Esta funcion pide y valida numeros enteros
///
/// @param --> pNumeroIngresado Este parametro retorna el numero ingresado por puntero
/// @param --> mensaje El mensaje cuando el usuario ingresa datos validos
/// @param --> mensajeError El mensaje erroneo, en caso de que ingrese datos no validos
/// @param --> maximo Indica el numero minimo que se puede ingresar
/// @param --> minimo Indica el numero maximo que se puede ingresar
/// @param --> maximoDeReintentos Indica el maximo de reintentos de validacion
/// @return --> Esta funcion retorna un 0 si se ingresaron datos validos, y un -1 si no son validos
int getInt(int * pNumeroIngresado,char * mensaje,char * mensajeError,
		int maximo, int minimo, int maximoDeReintentos){

	int auxNumeroIngresado;
	int retorno;
	retorno = -1;

	if(pNumeroIngresado != NULL && maximo >= minimo && maximoDeReintentos>= 0){
		do{
			printf("%s", mensaje);
			scanf("%d", &auxNumeroIngresado);
			maximoDeReintentos--;

			if(auxNumeroIngresado >= minimo && auxNumeroIngresado <= maximo){
						*pNumeroIngresado = auxNumeroIngresado;
						retorno = 0;
						break;
			}else{
				printf("%s", mensajeError);
			}

		}while(maximoDeReintentos > 0);
	}

	if(retorno == -1)
	{
		printf("Te quedaste sin intentos\n");
		system("pause");
		system("cls");
	}

	return retorno;
}

/// @brief --> Esta funcion pide y valida numeros flotantes
///
/// @param --> pNumeroIngresado Este parametro retorna el numero ingresado por puntero
/// @param --> mensaje El mensaje cuando el usuario ingresa datos validos
/// @param --> mensajeError El mensaje erroneo, en caso de que ingrese datos no validos
/// @param --> maximo Indica el numero minimo que se puede ingresar
/// @param --> minimo Indica el numero maximo que se puede ingresar
/// @param --> maximoDeReintentos Indica el maximo de reintentos de validacion
/// @return --> Esta funcion retorna un 0 si se ingresaron datos validos, y un -1 si no son validos
int getFloat(float * pNumeroIngresado,char * mensaje,char * mensajeError,
		float maximo, float minimo, int maximoDeReintentos){

	float auxNumeroIngresado;
	int retorno;
	retorno = -1;

	if(pNumeroIngresado != NULL && maximo >= minimo && maximoDeReintentos>= 0){
		do{
			printf("%s", mensaje);
			scanf("%f", &auxNumeroIngresado);
			maximoDeReintentos--;

			if(auxNumeroIngresado >= minimo && auxNumeroIngresado <= maximo){
						*pNumeroIngresado = auxNumeroIngresado;
						retorno = 0;
						break;
			}else{
				printf("%s", mensajeError);
			}

		}while(maximoDeReintentos > 0);
	}

	if(retorno == -1)
	{
		printf("Te quedaste sin intentos\n");
		system("pause");
		system("cls");
	}

	return retorno;
}






