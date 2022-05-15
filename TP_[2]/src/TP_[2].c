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
	int flagForceLoad = 0;
	Passenger passenger[LEN_PASSENGER];

	initPassengers(passenger, LEN_PASSENGER);

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
								lastName, price, typePassenger, flyCode)==0)
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
						modifyPassenger(passenger, LEN_PASSENGER, id);
						break;
					case 3:
						printf("\nBAJA\n");
						bajaPasajero(passenger, LEN_PASSENGER, id);
						break;
					case 4:
						informarPasajeros(passenger, LEN_PASSENGER);
						break;
					case 5:
						if(flagForceLoad == 0)
						{
							printf("\nCARGA FORZADA\n");
							if(forceLoad(passenger)==0)
							{
								printPassengers(passenger, LEN_PASSENGER);
								flag = 1;
								flagForceLoad = 1;
							}
						}
						else
						{
							printf("Ya se ingreso la carga forzada!!\n");
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
