/*
 * ArrayFlights.h
 *
 *  Created on: 12 may. 2022
 *      Author: carra
 */

#ifndef ARRAYFLIGHTS_H_
#define ARRAYFLIGHTS_H_

#include "ArrayPassenger.h"

struct
{
	char flycode[10];
	int statusFlight;
	int isEmpty;
} typedef eFlight;

struct
{
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10];
	int typePassenger;
	int isEmpty;
}typedef Passenger;

int initFlight(eFlight* list, int len);

int buscarStatusFlightByFlyCode(Passenger list[], int len, char flyCode[], eFlight statusFlight[]);

#endif /* ARRAYFLIGHTS_H_ */
