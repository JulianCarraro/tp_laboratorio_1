/*
 * ArrayFlight.c
 *
 *  Created on: 12 may. 2022
 *      Author: carra
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bibliotecaUtn.h"
#include "ArrayPassenger.h"
#include "ArrayFlights.h"

int initFlight(eFlight* list, int len)
{
	int retorno = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
			retorno = 0;
		}
	}

	return retorno;
}

//int buscarStatusFlightByFlyCode(Passenger list[], int len, char flyCode[], eFlight statusFlight[]) {
//	int retorno = -1;
//	if (list != NULL && len > 0 && statusFlight != NULL)
//	{
//		for (int i = 0; i < len; i++)
//		{
////			if(buscarArrayCharEnArray(list[i].flycode, flyCode)==0)
//			if(buscarArrayCharEnArray(&list[i], len, flyCode)==0)
//			{
//				printf("HOLA2\n");
//				retorno = statusFlight[i].statusFlight;
//				break;
//			}
//		}
//	}
//	return retorno;
//}


//{
//
//}

int buscarStatusFlightByFlyCode(Passenger list[], int len, char flyCode[], eFlight statusFlight[]) {
	int retorno = -1;
	if (list != NULL && len > 0 && statusFlight != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			for(int j = 0; j < len; j++)
			{
				if(strncmp(list[i].flycode, flyCode, len) == 0)
				{
					retorno = statusFlight[i].statusFlight;
					break;
				}
			}

		}
	}
	return retorno;
}

