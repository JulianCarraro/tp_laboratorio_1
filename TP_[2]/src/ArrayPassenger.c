/*
 * passenger.c
 *
 *  Created on: 8 may. 2022
 *      Author: Julian
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bibliotecaUtn.h"
#include "ArrayPassenger.h"
#include "ArrayFlights.h"

#define LEN_FORCELOAD 5
#define LEN_STATUSFLIGHT 2000
#define LEN_PASSENGER 2000
#define PRIMERA_CLASE 1
#define BUSSINES 2
#define ECONOMICA_PREMIUM 3
#define ECONOMICA 4

int incrementarId()
{
    static int id = 1000;
    id++;
    return id;
}

int initPassengers(Passenger* list, int len)
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

int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[], eFlight * status)
{
	int retorno = -1;
	int indexLibre;
//	int otroIndexLibre;
	char auxName[51];
	char auxLastName[51];
	float auxPrice;
	int auxTypePassenger;
	char auxFlyCode[10];
	int auxStatus;
//	eFlight status[LEN_STATUSFLIGHT];
	int flag;

	if (list != NULL && len > 0 && name != NULL && lastName != NULL && flycode != NULL)
	{
		indexLibre = buscarIndexPorIsEmpty(list, len);
//		otroIndexLibre = buscarIndexPorIsEmpty(status, len);
		if (indexLibre != -1)
		{
			if(getChars(auxName, sizeof(auxName), "Ingrese un nombre: ", "ERROR. Ingreso un nombre invalido\n\n",
					3)==0)
			{
				strncpy(list[indexLibre].name, auxName, sizeof(list[indexLibre].name));
				flag = 1;
			}
		}
		else
		{
			printf("Se ocuparon todos los espacios de pasajeros disponibles\n");
		}
		if(flag == 1)
		{
			flag = 0;
			if(getChars(auxLastName, sizeof(auxLastName), "Ingrese un apellido: ", "ERROR. Ingreso un apellido invalido\n\n",
					3)==0)
			{
				strncpy(list[indexLibre].lastName, auxLastName, sizeof(list[indexLibre].lastName));
				flag = 1;
			}
		}
		if(flag == 1)
		{
			flag = 0;
			if(getFloat(&auxPrice, "Ingrese el precio del vuelo ($5000 - $1500000): $", "ERROR. Ingreso un precio invalido\n\n",
					1500000, 5000, 3)==0)
			{
				list[indexLibre].price = auxPrice;
				flag = 1;
			}

		}
		if(flag == 1)
		{
			flag = 0;
			if(getInt(&auxTypePassenger, "\nTipo de Pasajero\n\n1. Primera Clase \n2. Clase Business\n3. Clase Economica Premium\n4. Clase Turista\n"
					"Ingrese una opcion: ", "ERROR. Ingreso una opcion incorrecta.\n\n",
					4, 1, 3)==0)
			{
				list[indexLibre].typePassenger = auxTypePassenger;
				flag = 1;
			}
		}
		if(flag == 1)
		{
			flag = 0;
			if(getCodeChar(auxFlyCode, sizeof(auxFlyCode), "\nIngrese el codigo de vuelo (max 10 caracteres): ", "ERROR. Ingreso un codigo de vuelo invalido\n\n" , 3)==0)
			{
//				if(buscarArrayCharEnArray(list->flycode, auxFlyCode)==1)
				if(buscarArrayCharEnArray(list, len, auxFlyCode)==1)
				{
					if(getInt(&auxStatus, "\nEstado del vuelo\n1. ACTIVO \n2. DEMORADO\n3. CANCELADO\n"
							"Ingrese una opcion: ", "ERROR. Ingreso una opcion incorrecta.\n",
							3, 1, 5)==0)
					{
						status[indexLibre].statusFlight = auxStatus;
						flag = 1;
					}
				}
				else
				{
					auxStatus = buscarStatusFlightByFlyCode(list, LEN_STATUSFLIGHT, auxFlyCode, status);
					status[indexLibre].statusFlight = auxStatus;
					flag = 1;
				}
				if(flag == 1)
				{
					strncpy(list[indexLibre].flycode, auxFlyCode, sizeof(list[indexLibre].flycode));
					list[indexLibre].id = incrementarId();
					list[indexLibre].isEmpty = 0;
					status[indexLibre].isEmpty = 0;
					printTitle();
					printPassenger(list[indexLibre], status[indexLibre]);
					retorno = 0;
					printf("\n¡¡¡¡¡CARGA EXITOSA!!!!!\n\n");
				}
			}
		}
	}


	return retorno;
}

int buscarIndexPorIsEmpty(Passenger* list, int len)
{
	int retorno = -1;

		if(list != NULL && len > 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == 1)
				{
					retorno = i;
					break;
				}
			}
		}

	return retorno;
}

int modifyPassenger(Passenger* list, int len, int idPassenger, eFlight * status)
{
	int retorno = -1;
	int index;
	int opcionMenu;
	int auxId;
	char auxName[51];
	char auxLastName[51];
	float auxPrice;
	int auxTypePassenger;
	int auxStatus;
	char auxFlyCode[10];
//	eFlight status[LEN_STATUSFLIGHT];
	int flag;

	flag = 0;

	if (list != NULL && len > 0 && idPassenger > 0)
	{

		printPassengers(list, LEN_PASSENGER, status, LEN_STATUSFLIGHT);

		if(getInt(&auxId, "\nIngrese el id del asociado que desea modificar: ",
				"Error, el id no es valido", 4000,
				1000, 3)==0)
		{
			idPassenger = auxId;
		}

		index = findPassengerById(list, len, idPassenger);

    	if (index != -1)
    	{
			do
			{
				printTitle();
				printPassenger(list[index], status[index]);
				if(menuModificaciones(&opcionMenu)==0)
				{
					switch(opcionMenu)
					{
						case 1:
							if(getChars(auxName, sizeof(auxName), "Ingrese un nombre: ", "ERROR. Ingreso un nombre invalido\n\n",
									3)==0)
							{
								strncpy(list[index].name, auxName, sizeof(list[index].name));
							}
							break;
						case 2:
							if(getChars(auxLastName, sizeof(auxLastName), "Ingrese un apellido: ", "ERROR. Ingreso un apellido invalido\n\n",
									3)==0)
							{
								strncpy(list[index].lastName, auxLastName, sizeof(list[index].lastName));
							}
							break;
						case 3:
							if(getFloat(&auxPrice, "Ingrese el precio del vuelo ($5000 - $1500000): $ ", "ERROR. Ingreso un precio invalido\n\n",
									1500000, 5000, 3)==0)
							{
								list[index].price = auxPrice;
							}
							break;
						case 4:
							if(getInt(&auxTypePassenger, "\nTipo de Pasajero\n\n1. Primera Clase \n2. Clase Business\n3. Clase Economica Premium\n4. Clase Turista\n"
									"Ingrese una opcion: ", "ERROR. Ingreso una opcion incorrecta.\n\n",
									4, 1, 3)==0)
							{
								list[index].typePassenger = auxTypePassenger;
							}
							break;
						case 5:
							if(getCodeChar(auxFlyCode, sizeof(auxFlyCode), "Ingrese el codigo de vuelo (max 10 caracteres): ", "ERROR. Ingreso un codigo de vuelo invalido\n\n" , 3)==0)
							{
								if(buscarArrayCharEnArray(list, len, auxFlyCode)==1)
								{
									if(getInt(&auxStatus, "\nEstado del vuelo\n1. ACTIVO \n2. DEMORADO\n3. CANCELADO\n"
											"Ingrese una opcion: ", "ERROR. Ingreso una opcion incorrecta.\n",
											3, 1, 5)==0)
									{
										status[index].statusFlight = auxStatus;
										flag = 1;
									}
								}
								else
								{
									auxStatus = buscarStatusFlightByFlyCode(list, LEN_STATUSFLIGHT, auxFlyCode, status);
									status[index].statusFlight = auxStatus;
									flag = 1;
								}
								if(flag == 1)
								{
									strncpy(list[index].flycode, auxFlyCode, sizeof(list[index].flycode));
								}
							}
							break;
						case 6:
							retorno = 0;
							printf("\n¡¡¡¡¡MODIFICACION EXITOSA!!!!!\n\n");
							break;
					}
				}

			}while(opcionMenu != 6);
	    }
    	else
    	{
    		printf("No hay asociado con ese ID\n");
    	}
	}
	return retorno;
}

int findPassengerById(Passenger* list, int len, int id)
{
	int retorno = -1;
	if (list != NULL && len > 0 && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].id == id && list[i].isEmpty == 0)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

void printPassenger(Passenger unPassenger, eFlight unStatus)
{
	char tiposDePasajero[5][51] = {"", "PRIMERA CLASE", "BUSSINES", "PREMIUM", "TURISTA"};
	char statusFlight[4][51] = {"HOLA", "ACTIVO", "DEMORADO", "CANCELADO"};

	if(unPassenger.isEmpty == 0)
	{
		printf("|%*d|%*s|%*s|%*.2f|%*s|%*s|%*s|\n", -15, unPassenger.id, -15, unPassenger.name, -15, unPassenger.lastName, -16, unPassenger.price, -16, tiposDePasajero[unPassenger.typePassenger], -15,
				unPassenger.flycode, -15, statusFlight[unStatus.statusFlight]);
	}
}

void printTitle(){


	printf("+-----------------------------------------------------------------------------------------------------------------+");
	printf("\n|%*s|%*s|%*s|%*s|%*s|%*s|%*s|\n", -15,"ID DEL PASAJERO", -15, "NOMBRE", -15, "APELLIDO", -15, "PRECIO DEL VUELO", -15, "TIPO DE PASAJERO", -15, "CODIGO DE VUELO", -15, "ESTADO DE VUELO");
	printf("+---------------+---------------+---------------+----------------+----------------+-------------------------------+\n");
}

int printPassengers(Passenger* list, int len, eFlight * status, int lenFlight)
{
	int retorno = -1;

	if(list != NULL && len >0)
	{
		printTitle();
		for(int i = 0; i < LEN_PASSENGER; i++)
		{
			printPassenger(list[i], status[i]);
		}
		printf("+-----------------------------------------------------------------------------------------------------------------+\n");
		retorno = 0;
	}
	return retorno;
}


int removePassenger(Passenger* list, int len, int id, eFlight * status)
{
	int retorno = -1;
	int auxId;
	int index;
//	eFlight unStatus[LEN_STATUSFLIGHT];

	if (list != NULL && len > 0 && id > 0)
	{

		printPassengers(list, len, status, LEN_STATUSFLIGHT);

		if(getInt(&auxId, "\nIngrese el id del asociado que desea modificar: ",
				"Error, el id no es valido", 4000,
				1000, 3)==0)
		{
			id = auxId;
		}

		index = findPassengerById(list, len, id);

		if (index != -1)
		{
			printTitle();
			printPassenger(list[index], status[index]);
			list[index].isEmpty = 1;
			retorno = 0;
			printf("\n¡¡¡¡¡BAJA EXITOSA!!!!!\n\n");
		}
    	else
    	{
    		printf("No hay asociado con ese ID\n");
    	}
	}

	return retorno;
}

int sortPassengers(Passenger* list, int len, int order)
{
	int retorno = -1;
	int i;
	Passenger aux;
	int auxOrder;
	int estaOrdenado;

	if (list != NULL && len > 0)
	{
		if(getInt(&auxOrder, "\n1) Descendente\n2) Ascendente \nDe que forma desea ordenar sus pasajeros?: ",
				"\nError, ingreso una opcion incorrecta", 2,
				1, 3)==0)
		{
			auxOrder--;
			order = auxOrder;
			retorno = 0;
		}

		do
		{
			estaOrdenado = 1;
			len--;
			for (i = 0; i < len; i++)
			{
				if(order == 1)
				{
					if(stricmp(list[i].lastName, list[i + 1].lastName) > 0)
					{
						aux = list[i];
						list[i] = list[i + 1];
						list[i + 1] = aux;
						estaOrdenado = 0;
					}
					else
					{
						if(stricmp(list[i].lastName, list[i + 1].lastName) == 0
								&& list[i].typePassenger > list[i + 1].typePassenger)
						{
							aux = list[i];
							list[i] = list[i + 1];
							list[i + 1] = aux;
							estaOrdenado = 0;
						}
					}
				}
				else
				{
					if(stricmp(list[i].lastName, list[i + 1].lastName) < 0)
					{
						aux = list[i];
						list[i] = list[i + 1];
						list[i + 1] = aux;
						estaOrdenado = 0;
					}
					else
					{
						if(stricmp(list[i].lastName, list[i + 1].lastName) == 0
								&& list[i].typePassenger < list[i + 1].typePassenger)
						{
							aux = list[i];
							list[i] = list[i + 1];
							list[i + 1] = aux;
							estaOrdenado = 0;
						}
					}
				}
			}
		}while(estaOrdenado == 0);
	}

	return retorno;
}

int sortPassengersByCode(Passenger* list, int len, int order)
{
	int retorno = -1;
	int i;
	Passenger aux;
	int auxOrder;
	int estaOrdenado;

	if (list != NULL && len > 0)
	{
		if(getInt(&auxOrder, "\n1) Descendente\n2) Ascendente \nDe que forma desea ordenar sus pasajeros?: ",
				"\nError, ingreso una opcion incorrecta", 2,
				1, 3)==0)
		{
			auxOrder--;
			order = auxOrder;
			retorno = 0;
		}

		do
			{
				estaOrdenado = 1;
				len--;
				for (i = 0; i < len; i++)
				{
					if(order == 1)
					{
						if(stricmp(list[i].flycode, list[i + 1].flycode) > 0)
						{
							aux = list[i];
							list[i] = list[i + 1];
							list[i + 1] = aux;
							estaOrdenado = 0;
						}
					}
					else
					{
						if(stricmp(list[i].flycode, list[i + 1].flycode) < 0)
						{
							aux = list[i];
							list[i] = list[i + 1];
							list[i + 1] = aux;
							estaOrdenado = 0;
						}
					}
				}
			}while(estaOrdenado == 0);
	}

	return retorno;
}

int forceLoad(Passenger * list, eFlight * array)
{
	int retorno = -1;
	int i;
	int indexLibre;

	indexLibre = buscarIndexPorIsEmpty(list, LEN_PASSENGER);

	Passenger lista[LEN_FORCELOAD] = {{3001, "Marcelo", "Gutierrez", 15000, "HF2378", 2, 0},
			{3002, "Lionel", "Scaloni", 20000, "213203", 3, 0}, {3003, "Lionel", "Messi", 100000, "FL2YD3", 1, 0},
			{3004, "Cristiano", "Ronaldo", 500000, "2FDS20", 1, 0}, {3005, "Julian", "Carraro", 20000, "213ASD", 2, 0}};
	eFlight status[LEN_FORCELOAD] = {{"HF2378", 1, 0}, {"213203", 2, 0}, {"FL2YD3", 3, 0}, {"2FDS20", 2, 0}, {"213ASD", 1, 0}};

	if(list != NULL && LEN_FORCELOAD > 0)
	{
		for(i = 0; i < LEN_FORCELOAD; i++)
		{
			if (indexLibre != -1)
			{
				list[i] = lista[i];
				array[i] = status[i];
				retorno = 0;
			}
		}
	}

	return retorno;
}

int contadorAltas(Passenger list[], int len)
{
	int contadorAltas = 0;
	int i;

	for(i = 0; i < len; i++)
	{
		if(list[i].isEmpty == 0)
		{
			contadorAltas++;
		}
	}

	return contadorAltas;
}

float calcularPrecioTotal(Passenger list[], int len)
{
	float total=0;
	int i;

	for(i = 0; i < len; i++)
	{
		if(list[i].isEmpty == 0)
		{
			total += list[i].price;
		}
	}

	return total;
}

float calcularPromedio(Passenger list[], int len)
{
	float promedio;
	int datosCargados;
	float total;

	total = calcularPrecioTotal(list, len);
	datosCargados= contadorAltas(list, len);
	promedio = total / datosCargados;

	return promedio;
}

int superanElPromedio(Passenger list[], int len)
{
	int contador = 0;
	float promedio;
	int i;

	promedio = calcularPromedio(list, len);

	for(i = 0; i < len; i++)
	{
		if(list[i].isEmpty == 1 && list[i].price > promedio)
		{
			contador++;
		}
	}

	return contador;
}

int informarPasajeros(Passenger list[], int len)
{
	int retorno = -1;
	int opcionMenu;
	int order = 0;
	float precioTotal;
	float promedio;
	int encimaDelPromedio;
	eFlight unStatus[LEN_STATUSFLIGHT];

	if(menuInformar(&opcionMenu)==0)
	{
		switch(opcionMenu)
		{
			case 1:
				if(sortPassengers(list, len, order)==0)
				{
					printPassengers(list, len, unStatus, LEN_STATUSFLIGHT);
				}
				break;
			case 2:
				precioTotal = calcularPrecioTotal(list, len);
				printf("El precio total de los pasajes es: $%.2f\n", precioTotal);
				promedio = calcularPromedio(list, len);
				printf("El promedio total de los pasajes es: $%.2f\n", promedio);
				encimaDelPromedio = superanElPromedio(list, len);
				printf("Hay %d pasajero/s que superan el precio promedio\n", encimaDelPromedio);
				break;
			case 3:
				if(sortPassengersByCode(list, len, order)==0)
				{
					printPassengers(list, len, unStatus, LEN_STATUSFLIGHT);
				}
				break;
		}
	}

	return retorno;

}






