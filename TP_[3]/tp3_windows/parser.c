#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	char id[100];
	char name[100];
	char lastName[100];
	char price[100];
	char typePassenger[100];
	char flyCode[100];
	char statusFlight[100];
	Passenger * aPassenger;

	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, name, lastName,
				price, flyCode, typePassenger, statusFlight);

		while(!feof(pFile))
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, name, lastName,
					price, flyCode, typePassenger, statusFlight)==7)
			{
				aPassenger = Passenger_newParametros(id, name, lastName,
						price, typePassenger, flyCode, statusFlight);

				if(aPassenger != NULL)
				{
					ll_add(pArrayListPassenger, aPassenger);
					retorno = 0;
				}
			}
			else
			{
				break;
			}
		}
	}

	fclose(pFile);

    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{

    return 1;
}
