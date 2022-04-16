/*
 * bibliotecaPedirDatos.h
 *
 *  Created on: 7 abr. 2022
 *      Author: carra
 */

#ifndef BIBLIOTECAPEDIRDATOS_H_
#define BIBLIOTECAPEDIRDATOS_H_

int getInt(int * pNumeroIngresado,char * mensaje,char * mensajeError,
		int maximo, int minimo, int maximoDeReintentos);

int getFloat(float * pNumeroIngresado,char * mensaje,char * mensajeError,
		float maximo, float minimo, int maximoDeReintentos);

#endif /* BIBLIOTECAPEDIRDATOS_H_ */
