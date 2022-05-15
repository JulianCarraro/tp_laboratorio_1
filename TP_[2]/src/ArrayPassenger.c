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


/// @brief --> Esta funcion va autoincrementando el id
///
/// @return --> Esta funcion retorna el id
int incrementarId()
{
    static int id = 1000;
    id++;
    return id;
}

/// @brief --> Esta funcion inicializa el array de pasajeros
///
/// @param --> list Puntero al espacio de memoria donde se inicializara los datos
/// @return --> Esta funcion retorna un 0 si se ingresaron datos validos, y un -1 si no son validos
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

/// @brief --> Esta funcion añade pasajeros al array
///
/// @param --> list Puntero al espacio de memoria donde se guardaran los datos
/// @param --> len Define el largo de la cadena
/// @param --> id recibe el id
/// @param --> name recibe el nombre
/// @param --> lastName recibe el segundo nombre
/// @param --> price recibe el precio
/// @param --> typePassenger recibe el tipo de pasajero
/// @param --> flycode recibe el codigo de vuelo
/// @return --> Esta funcion retorna un 0 si se ingresaron datos validos, y un -1 si no son validos
int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[])
{
	int retorno = -1;
	int indexLibre;
	char auxName[51];
	char auxLastName[51];
	float auxPrice;
	int auxTypePassenger;
	char auxFlyCode[10];
	int auxStatus;
	int flag;

	if (list != NULL && len > 0 && name != NULL && lastName != NULL && flycode != NULL)
	{
		indexLibre = buscarIndexPorIsEmpty(list, len);
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
				if(buscarArrayCharEnArray(list, len, auxFlyCode)==1)
				{
					if(getInt(&auxStatus, "\nEstado del vuelo\n1. ACTIVO \n2. DEMORADO\n3. CANCELADO\n"
							"Ingrese una opcion: ", "ERROR. Ingreso una opcion incorrecta.\n",
							3, 1, 5)==0)
					{
						list[indexLibre].statusFlight = auxStatus;
						flag = 1;
					}
				}
				else
				{
					auxStatus = buscarStatusFlightByFlyCode(list, LEN_STATUSFLIGHT, auxFlyCode);
					list[indexLibre].statusFlight = auxStatus;
					flag = 1;
				}
				if(flag == 1)
				{
					strncpy(list[indexLibre].flycode, auxFlyCode, sizeof(list[indexLibre].flycode));
					list[indexLibre].id = incrementarId();
					list[indexLibre].isEmpty = 0;
					printTitle();
					printPassenger(list[indexLibre]);
					retorno = 0;
					printf("\n¡¡¡¡¡CARGA EXITOSA!!!!!\n\n");
				}
			}
		}
	}


	return retorno;
}

/// @brief --> Esta funcion busca un espacio libre en el array
///
/// @param --> list Puntero al espacio de memoria donde se buscara el lugar libre
/// @param --> len Define el tamanio de la cadena
/// @return --> Esta funcion retorna un index libre
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

/// @brief --> Esta funcion permite modificar los datos de un pasajero
///
/// @param --> list Puntero al espacio de memoria donde se modificaran los datos
/// @param --> len Define el tamanio de la cadena
/// @param --> idPassenger recibe el id del pasajero a modificar
/// @return --> Esta funcion retorna 0 si se modifico correctamente, o -1 si no fue asi
int modifyPassenger(Passenger* list, int len, int idPassenger)
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

		printPassengers(list, LEN_PASSENGER);

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
				printPassenger(list[index]);
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
										list[index].statusFlight = auxStatus;
										flag = 1;
									}
								}
								else
								{
									auxStatus = buscarStatusFlightByFlyCode(list, LEN_STATUSFLIGHT, auxFlyCode);
									list[index].statusFlight = auxStatus;
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

/// @brief --> Esta funcion busca un pasajero por el id
///
/// @param --> list Puntero al espacio de memoria donde se buscara el pasajero
/// @param --> len Define el tamanio de la cadena
/// @param --> id recibe el id del pasajero a buscar
/// @return --> Esta funcion retorna el index del pasajero encontrado
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

/// @brief --> Esta funcion muestra un pasajero
///
/// @param --> unPassenger Puntero al espacio de memoria donde se buscara el pasajero a mostrar
/// @return --> Esta funcion no retorna nada
void printPassenger(Passenger unPassenger)
{
	char tiposDePasajero[5][51] = {"", "PRIMERA CLASE", "BUSSINES", "PREMIUM", "TURISTA"};
	char statusFlight[4][51] = {"HOLA", "ACTIVO", "DEMORADO", "CANCELADO"};

	if(unPassenger.isEmpty == 0)
	{
		printf("|%*d|%*s|%*s|%*.2f|%*s|%*s|%*s|\n", -15, unPassenger.id, -15, unPassenger.name, -15, unPassenger.lastName, -16, unPassenger.price, -16, tiposDePasajero[unPassenger.typePassenger], -15,
				unPassenger.flycode, -15, statusFlight[unPassenger.statusFlight]);
	}
}

/// @brief --> Esta funcion muestra el titulo
///
/// @return --> Esta funcion no retorna nada
void printTitle(){


	printf("+-----------------------------------------------------------------------------------------------------------------+");
	printf("\n|%*s|%*s|%*s|%*s|%*s|%*s|%*s|\n", -15,"ID DEL PASAJERO", -15, "NOMBRE", -15, "APELLIDO", -15, "PRECIO DEL VUELO", -15, "TIPO DE PASAJERO", -15, "CODIGO DE VUELO", -15, "ESTADO DE VUELO");
	printf("+---------------+---------------+---------------+----------------+----------------+-------------------------------+\n");
}

/// @brief --> Esta funcion muestra todos los pasajeros cargados
///
/// @param --> list Puntero al espacio de memoria donde se buscaran los pasajeros a mostrar
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna 0 si se verifico correctamente o -1 si no fue asi
int printPassengers(Passenger* list, int len)
{
	int retorno = -1;

	if(list != NULL && len >0)
	{
		printTitle();
		for(int i = 0; i < LEN_PASSENGER; i++)
		{
			printPassenger(list[i]);
		}
		printf("+-----------------------------------------------------------------------------------------------------------------+\n");
		retorno = 0;
	}
	return retorno;
}

/// @brief --> Esta funcion permite borrar un pasajero del array
///
/// @param --> list Puntero al espacio de memoria donde se borraran los datos
/// @param --> len Define el tamanio de la cadena
/// @param --> id recibe el id del pasajero a borrar
/// @return --> Esta funcion retorna 0 si se modifico correctamente, o -1 si no fue asi
int removePassenger(Passenger* list, int len, int id)
{
	int retorno = -1;

	if (list != NULL && len > 0 && id > 0)
	{
		for(int i=0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].id == id)
			{
				list[i].isEmpty = 1;
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}

/// @brief --> Esta funcion pide y permite borrar un pasajero del array
///
/// @param --> list Puntero al espacio de memoria donde se borraran los datos
/// @param --> len Define el tamanio de la cadena
/// @param --> id recibe el id del pasajero a borrar
/// @return --> Esta funcion retorna 0 si se modifico correctamente, o -1 si no fue asi
int bajaPasajero(Passenger* list, int len, int id)
{
	int retorno = -1;
	int auxId;
	int index;

	if (list != NULL && len > 0 && id > 0)
	{
		printPassengers(list, len);

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
			printPassenger(list[index]);
			removePassenger(list, len, id);
			retorno = 0;
			printf("\n¡¡¡¡¡BAJA EXITOSA!!!!!\n\n");

		}
		else
		{
			printf("No encontramos ningun pasajero con ese ID");
		}

	}

	return retorno;
}

/// @brief --> Esta funcion ordena los pasajeros por apellido o tipo de pasajero
///
/// @param --> list Puntero al espacio de memoria donde se ordenaran los datos
/// @param --> len Define el tamanio de la cadena
/// @param --> order recibe el orden del cual se quieren ordenar
/// @return --> Esta funcion retorna 0 si se ordeno correctamente, o -1 si no fue asi
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

/// @brief --> Esta funcion ordena los pasajeros codigo de vuelo
///
/// @param --> list Puntero al espacio de memoria donde se ordenaran los datos
/// @param --> len Define el tamanio de la cadena
/// @param --> order recibe el orden del cual se quieren ordenar
/// @return --> Esta funcion retorna 0 si se ordeno correctamente, o -1 si no fue asi
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

/// @brief --> Esta funcion muestra un pasajero con estado de vuelo activo
///
/// @param --> unPassenger Puntero al espacio de memoria donde se buscara el pasajero a mostrar
/// @return --> Esta funcion no retorna nada
void printPassengerActives(Passenger unPassenger)
{
	char tiposDePasajero[5][51] = {"", "PRIMERA CLASE", "BUSSINES", "PREMIUM", "TURISTA"};
	char statusFlight[4][51] = {"HOLA", "ACTIVO", "DEMORADO", "CANCELADO"};

	if(unPassenger.isEmpty == 0 && unPassenger.statusFlight == 1)
	{
		printf("|%*d|%*s|%*s|%*.2f|%*s|%*s|%*s|\n", -15, unPassenger.id, -15, unPassenger.name, -15, unPassenger.lastName, -16, unPassenger.price, -16, tiposDePasajero[unPassenger.typePassenger], -15,
				unPassenger.flycode, -15, statusFlight[unPassenger.statusFlight]);
	}
}

/// @brief --> Esta funcion muestra todos los pasajeros cargados con estado de vuelo activo
///
/// @param --> list Puntero al espacio de memoria donde se buscaran los pasajeros a mostrar
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna 0 si se verifico correctamente o -1 si no fue asi
int printPassengersActive(Passenger* list, int len)
{
	int retorno = -1;

	if(list != NULL && len >0)
	{
		printTitle();
		for(int i = 0; i < LEN_PASSENGER; i++)
		{
			printPassengerActives(list[i]);
		}
		printf("+-----------------------------------------------------------------------------------------------------------------+\n");
		retorno = 0;
	}
	return retorno;
}

/// @brief --> Esta funcion hardcodea los datos del array
///
/// @param --> list Puntero al espacio de memoria donde se cargaran los pasajeros
/// @return --> Esta funcion retorna 0 si se cargo correctamente o -1 si no fue asi
int forceLoad(Passenger * list)
{
	int retorno = -1;
	int i;
	int indexLibre;

	indexLibre = buscarIndexPorIsEmpty(list, LEN_PASSENGER);

	Passenger lista[LEN_FORCELOAD] = {{3001, "Marcelo", "Gutierrez", 15000, "HF2378", 2, 1, 0},
			{3002, "Lionel", "Scaloni", 20000, "213203", 3, 2, 0}, {3003, "Lionel", "Messi", 100000, "FL2YD3", 1, 3, 0},
			{3004, "Cristiano", "Ronaldo", 500000, "2FDS20", 1, 2, 0}, {3005, "Julian", "Carraro", 20000, "213ASD", 2, 1, 0}};
//	eFlight status[LEN_FORCELOAD] = {{"HF2378", 1, 0}, {"213203", 2, 0}, {"FL2YD3", 3, 0}, {"2FDS20", 2, 0}, {"213ASD", 1, 0}};

	if(list != NULL && LEN_PASSENGER > 0)
	{
		for(i = 0; i < LEN_FORCELOAD; i++)
		{
			if(indexLibre != -1)
			{
				list[i] = lista[i];
				retorno = 0;
			}
		}
	}

	return retorno;
}

/// @brief --> Esta funcion cuenta los pasajeros cargados
///
/// @param --> list Puntero al espacio de memoria donde se contaran los pasajeros
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna la cantidad de pasajeros cargados
int loadCount(Passenger list[], int len)
{
	int contadorPasajeros = 0;
	int i;

	for(i = 0; i < len; i++)
	{
		if(list[i].isEmpty == 0)
		{
			contadorPasajeros++;
		}
	}

	return contadorPasajeros;
}

/// @brief --> Esta funcion calcula el precio total
///
/// @param --> list Puntero al espacio de memoria donde se acumularan los precios de los vuelos
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna el precio total de los pasajes
float totalPrice(Passenger list[], int len)
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

/// @brief --> Esta funcion calcula el promedio total
///
/// @param --> list Puntero al espacio de memoria donde se calculara el promedio de los precios de los vuelos
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna el promedio total de los pasajes
float calculateAverage(Passenger list[], int len)
{
	float promedio;
	int datosCargados;
	float total;

	total = totalPrice(list, len);
	datosCargados= loadCount(list, len);
	promedio = total / datosCargados;

	return promedio;
}

/// @brief --> Esta funcion cuenta los precios que estan por encima del promedio total de los pasajes
///
/// @param --> list Puntero al espacio de memoria donde se contara los precios por encima del promedio total
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna la cantidad de precios que estan por encima del promedio total
int aboveAverage(Passenger list[], int len)
{
	int contador = 0;
	float promedio;
	int i;

	promedio = calculateAverage(list, len);

	for(i = 0; i < len; i++)
	{
		if(list[i].isEmpty == 0 && list[i].price > promedio)
		{
			contador++;
		}
	}

	return contador;
}

/// @brief --> Esta funcion informa los pasajeros segun la forma elegida
///
/// @param --> list Puntero al espacio de memoria donde se buscaran los datos a informar
/// @param --> len Define el tamaño de la cadena
/// @return --> Esta funcion retorna 0 si se informaron bien los datos o -1 si no fue asi
int informarPasajeros(Passenger list[], int len)
{
	int retorno = -1;
	int opcionMenu;
	int order = 0;
	float precioTotal;
	float promedio;
	int encimaDelPromedio;

	do
	{
		printf("\nINFORMAR\n\n");
		if(menuInformar(&opcionMenu)==0)
			{
				switch(opcionMenu)
				{
					case 1:
						if(sortPassengers(list, len, order)==0)
						{
							printPassengers(list, len);
						}
						break;
					case 2:
						precioTotal = totalPrice(list, len);
						printf("El precio total de los pasajes es: $%.2f\n", precioTotal);
						promedio = calculateAverage(list, len);
						printf("El promedio total de los pasajes es: $%.2f\n", promedio);
						encimaDelPromedio = aboveAverage(list, len);
						printf("Hay %d pasajero/s que superan el precio promedio\n", encimaDelPromedio);
						break;
					case 3:
						if(sortPassengersByCode(list, len, order)==0)
						{
							printPassengersActive(list, len);
						}
						break;
					case 4:
						retorno = 0;
						break;
				}
			}
	}while(opcionMenu != 4);


	return retorno;

}

/// @brief --> Esta funcion busca el estado del vuelo por el codigo del vuelo
///
/// @param --> list Puntero al espacio de memoria donde se buscara el estado del vuelo
/// @param --> len Define el tamanio de la cadena
/// @param --> flyCode Recibe el codigo de vuelo a buscar
/// @return --> Esta funcion retorna el estado del vuelo del codigo de vuelo ingresado
int buscarStatusFlightByFlyCode(Passenger list[], int len, char flyCode[]) {
	int retorno = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			for(int j = 0; j < len; j++)
			{
				if(strncmp(list[i].flycode, flyCode, len) == 0)
				{
					retorno = list[i].statusFlight;
					break;
				}
			}

		}
	}
	return retorno;
}
