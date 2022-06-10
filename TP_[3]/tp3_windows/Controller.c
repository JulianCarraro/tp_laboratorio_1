#include <stdio.h>
#include <stdlib.h>
#include "bibliotecaUtn.h"
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"


/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */

int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	FILE * pFile;

	if(pArrayListPassenger != NULL && path != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			if(parser_PassengerFromText(pFile , pArrayListPassenger)==0)
			{
				retorno = 0;
			}
		}
	}

	fclose(pFile);

    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
    return 1;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	char idTexto[10];
	Passenger * auxPassenger;

	if(pArrayListPassenger != NULL)
	{
		if(Passenger_findLastId("id.csv", idTexto) == 0 && Passenger_increaseId(idTexto) == 0)
		{
			auxPassenger = requestPassengerData(idTexto);
			if(auxPassenger != NULL)
			{
				printTitle();
				Passenger_printOne(auxPassenger);
				ll_add(pArrayListPassenger, auxPassenger);

				if(Passenger_writeNewId("id.csv", idTexto)==0)
				{
					retorno = 0;
				}
				else
				{
					Passenger_delete(auxPassenger);
				}
			}
		}
	}

    return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int auxId;
	int index;
	Passenger * auxPassenger;

	if(pArrayListPassenger != NULL)
	{
		controller_ListPassenger(pArrayListPassenger);

		if(getInt(&auxId, "\nIngrese el id del asociado que desea modificar: ",
				"Error, el id no es valido", 9000,
				1, 3)==0)
		{
			index = Passenger_findPassengerById(pArrayListPassenger, auxId);

			if(index != -1)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, index);
				Passenger_edit(auxPassenger);
				retorno = 0;
			}
			else
			{
				printf("No se encontro un pasajero con ese ID\n");
			}
		}
	}

    return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int auxId;
	int index;
	char respuesta;
	Passenger * auxPassenger;

	if(pArrayListPassenger != NULL)
	{
		controller_ListPassenger(pArrayListPassenger);

		if(getInt(&auxId, "\nIngrese el id del asociado que desea dar de baja: ",
				"Error, el id no es valido", 9000,
				1, 3)==0)
		{
			index = Passenger_findPassengerById(pArrayListPassenger, auxId);

			if(index != -1)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, index);
				printTitle();
				Passenger_printOne(auxPassenger);
				if(getChars(&respuesta, sizeof(respuesta), "\n¿Esta seguro que desea eliminar al pasajero? s(si) o n(no): ",
											"Ingreso un caracter invalido\n", 3)==0)
				{
					if(respuesta == 's')
					{
						ll_remove(pArrayListPassenger, index);
						Passenger_delete(auxPassenger);
						retorno = 0;
					}
				}
			}
			else
			{
				printf("No se encontro un pasajero con ese ID\n");
			}
		}
	}

    return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	Passenger * auxPassenger;
	int tamanio;

	if(pArrayListPassenger != NULL)
	{
		tamanio = ll_len(pArrayListPassenger);
		printTitle();
		for(int i = 0; i < tamanio; i++)
		{
			auxPassenger = (Passenger*)ll_get(pArrayListPassenger, i);
			Passenger_printOne(auxPassenger);
		}
	}

    return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	int order;
	int opcionMenu;
	char respuesta;

	if(pArrayListPassenger != NULL)
	{
		do
		{
			if(menuOrdenamiento(&opcionMenu)==0)
			{
				if(opcionMenu != 8 && getInt(&order, "\n1. DESCENDENTE\n2. ASCENDENTE\nElige la forma de la cual desea ordenarlo: ",
						"ERROR. Ingreso una opcion incorrecta.", 2, 1, 3)==0)
				{
					order--;
					printf("\n¡¡¡AGUARDE UN MOMENTO!!!\n");
					switch(opcionMenu)
					{
						case 1:
							printf("Ordenando los pasajeros por ID...");
							ll_sort(pArrayListPassenger, Passenger_compareId, order);
							break;
						case 2:
							printf("Ordenando los pasajeros por NOMBRE...");
							ll_sort(pArrayListPassenger, Passenger_compareName, order);
							break;
						case 3:
							printf("Ordenando los pasajeros por APELLIDO...");
							ll_sort(pArrayListPassenger, Passenger_compareLastName, order);
							break;
						case 4:
							printf("Ordenando los pasajeros por PRECIO...");
							ll_sort(pArrayListPassenger, Passenger_comparePrice, order);
							break;
						case 5:
							printf("Ordenando los pasajeros por CODIGO DE VUELO...");
							ll_sort(pArrayListPassenger, Passenger_compareFlyCode, order);
							break;
						case 6:
							printf("Ordenando los pasajeros por TIPO DE PASAJERO...");
							ll_sort(pArrayListPassenger, Passenger_compareTypePassenger, order);
							break;
						case 7:
							printf("Ordenando los pasajeros por ESTADO DEL VUELO...");
							ll_sort(pArrayListPassenger, Passenger_compareStatusFlight, order);
							break;
						case 8:
							if(getChars(&respuesta, sizeof(respuesta), "\n¿Desea volver al menu principal? s(si) o n(no): ",
									"Ingreso un caracter invalido\n", 3)==0)
							{
								retorno = 0;
							}
							break;
					}
				}
			}

		}while(opcionMenu != 8);
	}

    return retorno;
}


/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	Passenger * auxPassenger;
	int tamanio;
	int auxId;
	char auxName[256];
	char auxLastName[256];
	float auxPrice;
	int auxTypePassenger;
	char typePassenger[256];
	char auxFlyCode[256];
	int auxStatusFlight;
	char statusFlight[256];
	FILE * pFile;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pFile = fopen(path, "w");
		if(pFile != NULL)
		{
			tamanio = ll_len(pArrayListPassenger);
			fprintf(pFile, "Id,Nombre,Apellido,Precio,CodigoDeVuelo,TipoDePasajero,EstadoDelVuelo\n");
			for(int i = 0; i < tamanio; i++)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, i);
				if(Passenger_getAll(auxPassenger, &auxId, auxName, auxLastName, &auxPrice, &auxTypePassenger, auxFlyCode, &auxStatusFlight)==0)
				{
					convertTypePassengerToChar(auxTypePassenger,typePassenger);
					convertStatusFlightToChar(auxStatusFlight,statusFlight);
					fprintf(pFile, "%d,%s,%s,%.2f,%s,%s,%s\n", auxId, auxName, auxLastName, auxPrice, auxFlyCode, typePassenger, statusFlight);
				}
			}

			retorno = 0;
		}
	}

	fclose(pFile);

    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	Passenger * auxPassenger;
	int tamanio;
	FILE * pFile;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pFile = fopen(path, "wb");
		if(pFile != NULL)
		{
			tamanio = ll_len(pArrayListPassenger);
			for(int i = 0; i < tamanio; i++)
			{
				auxPassenger = (Passenger*)ll_get(pArrayListPassenger, i);
				fwrite(auxPassenger, sizeof(auxPassenger), 1, pFile);
			}

			retorno = 0;
		}
	}

	fclose(pFile);

    return retorno;
}



