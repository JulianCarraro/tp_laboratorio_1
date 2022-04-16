/*
 * bibliotecaCalculos.c
 *
 *  Created on: 15 abr. 2022
 *      Author: carra
 */

#include <stdio.h>
#include <stdlib.h>
#include "bibliotecaCalculos.h"


/// @brief --> Esta funcion calcula el producto de dos numeros flotantes
///
/// @param --> numeroUno Numero flotante para calcular
/// @param --> numeroDos Numero flotante para calcular
/// @return --> Esta funcion retorna el resultado del calculo del producto
float producto(float numeroUno, float numeroDos)
{
	float resultado;

	resultado = numeroUno * numeroDos;

	return resultado;
}

/// @brief --> Esta funcion calcula 3 numeros flotantes utilizando la regla de tres simples
///
/// @param --> numeroUno Numero flotante para calcular
/// @param --> numeroDos Numero flotante para calcular
/// @param --> numeroTres Numero flotante para calcular
/// @return --> Esta funcion retorna el resultado del calculo de la regla de tres simples
float reglaDeTresSimples(float numeroUno, float numeroDos, float numeroTres)
{
	float resultado;

	resultado = numeroUno * numeroDos;
	resultado = resultado / numeroTres;

	return resultado;
}

/// @brief --> Esta funcion calcula la diferencia entre dos numeros
///
/// @param --> numeroUno Numero flotante para calcular
/// @param --> numeroDos Numero flotante para calcular
/// @return --> Esta funcion retorna el resultado del calculo de la diferencia
float calculoDiferencia(float numeroUno, float numeroDos)
{
	float diferencia;

	if(numeroUno > numeroDos)
	{
		diferencia = numeroUno - numeroDos;
	}
	else
	{
		diferencia = numeroDos - numeroUno;
	}

	return diferencia;
}

