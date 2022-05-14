/*
 ============================================================================
 Name        : TrabajoPractico_Borrador.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "bibliotecaUtn.h"
#include "ArrayPassenger.h"
#include "ArrayFlights.h"

#define LEN_PASSENGER 2000
#define LEN_NAME 51
#define LEN_LASTNAME 51
#define LEN_FLYCODE 10
#define LEN_FORCELOAD 5
#define LEN_STATUSFLIGHT 51

int main(void) {
	setbuf(stdout, NULL);

	int opcionMenu;
	int id = 1000;
	char name[LEN_NAME];
	char lastName[LEN_LASTNAME];
	float price = 0;
	int typePassenger = 0;
	char flyCode[LEN_FLYCODE];
	int flag = 0;
	Passenger passenger[LEN_PASSENGER];
	eFlight statusFlight[LEN_STATUSFLIGHT];

	initPassengers(passenger, LEN_PASSENGER);
	initFlight(statusFlight, LEN_PASSENGER);

	do
	{
		if(menuPrincipal(&opcionMenu)==0)
		{
			if(opcionMenu == 1 || opcionMenu == 5 || opcionMenu == 6 || flag == 1)
			{
				switch(opcionMenu)
				{
					case 1:
						printf("\nALTAS\n");
						if(addPassenger(passenger, LEN_PASSENGER, id, name,
								lastName, price, typePassenger, flyCode, statusFlight)==0)
						{
							flag = 1;
						}
						else
						{
							printf("No se guardaron los datos ingresados");
						}
						break;
					case 2:
						printf("\nMODIFICAR\n");
						modifyPassenger(passenger, LEN_PASSENGER, id, statusFlight);
						break;
					case 3:
						printf("\nBAJA\n");
						removePassenger(passenger, LEN_PASSENGER, id, statusFlight);
						break;
					case 4:
						printf("\nINFORMAR\n\n");
						informarPasajeros(passenger, LEN_PASSENGER);
						break;
					case 5:
						printf("\nCARGA FORZADA\n");
						if(forceLoad(passenger, statusFlight)==0)
						{
							printPassengers(passenger, LEN_PASSENGER, statusFlight, LEN_PASSENGER);
							flag = 1;
						}
						break;
					case 6:
						break;
				}
			}
			else
			{
				printf("Primero debe ingresar un alta\n\n");
			}
		}

	}while(opcionMenu != 6);


	return EXIT_SUCCESS;
}

