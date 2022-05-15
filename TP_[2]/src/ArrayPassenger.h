/*
 * passenger.h
 *
 *  Created on: 8 may. 2022
 *      Author: Julian
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

struct
{
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10];
	int typePassenger;
	int statusFlight;
	int isEmpty;
}typedef Passenger;

int incrementarId();

int initPassengers(Passenger* list, int len);

int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[]);

int buscarIndexPorIsEmpty(Passenger* list, int len);

void printPassenger(Passenger unPassenger);

int printPassengers(Passenger* list, int len);

int modifyPassenger(Passenger* list, int len, int idPassenger);

int findPassengerById(Passenger* list, int len, int id);

int removePassenger(Passenger* list, int len, int id);

int bajaPasajero(Passenger* list, int len, int id);

int sortPassengers(Passenger* list, int len, int order);

int sortPassengersByCode(Passenger* list, int len, int order);

void printPassengerActives(Passenger unPassenger);

int printPassengersActive(Passenger* list, int len);

void printTitle();

int forceLoad(Passenger * list);

int contadorAltas(Passenger list[], int len);

float totalPrice(Passenger list[], int len);

float calculateAverage(Passenger list[], int len);

int aboveAverage(Passenger list[], int len);

int informarPasajeros(Passenger list[], int len);

int buscarStatusFlightByFlyCode(Passenger list[], int len, char flyCode[]);


#endif /* PASSENGER_H_ */
