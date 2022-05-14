/*
 * passenger.h
 *
 *  Created on: 8 may. 2022
 *      Author: Julian
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_
#include "ArrayFlights.h"

//struct
//{
//	int id;
//	char name[51];
//	char lastName[51];
//	float price;
//	char flycode[10];
//	int typePassenger;
//	int isEmpty;
//}typedef Passenger;

int incrementarId();

int initPassengers(Passenger* list, int len);

int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[], eFlight * status);

int buscarIndexPorIsEmpty(Passenger* list, int len);

void printPassenger(Passenger unPassenger, eFlight unStatus);

int printPassengers(Passenger* list, int len, eFlight * status, int lenFlight);

//int modifyPassenger(Passenger* list, int len, int idPassenger);

int modifyPassenger(Passenger* list, int len, int idPassenger, eFlight * status);

int findPassengerById(Passenger* list, int len, int id);

//int removePassenger(Passenger* list, int len, int id);

int removePassenger(Passenger* list, int len, int id, eFlight * status);

int sortPassengers(Passenger* list, int len, int order);

int sortPassengersByCode(Passenger* list, int len, int order);

void printTitle();

int forceLoad(Passenger * list, eFlight * array);

int contadorAltas(Passenger list[], int len);

float calcularPrecioTotal(Passenger list[], int len);

float calcularPromedio(Passenger list[], int len);

int informarPasajeros(Passenger list[], int len);

#endif /* PASSENGER_H_ */
