#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "Controller.h"
#include "parser.h"
#include "bibliotecaUtn.h"

/****************************************************
 Menu:
 1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
 2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
 3. Alta de pasajero
 4. Modificar datos de pasajero
 5. Baja de pasajero
 6. Listar pasajeros
 7. Ordenar pasajeros
 8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
 9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
 10. Salir
 *****************************************************/

int main() {
	setbuf(stdout, NULL);

	int option = 0;
	char respuesta;
	int flag;
	int flagCargaTexto;

	LinkedList *lista = ll_newLinkedList();
	respuesta = 'n';
	flag = 0;
	flagCargaTexto = 0;

	do
	{
		if(menuPrincipal(&option)==0)
		{
			if(option == 1 || option == 2 || option == 3 || option == 10 || flag == 1)
			{
				switch(option)
				{
					case 1:
						if(controller_loadFromText("data.csv", lista)==0)
						{
							printf("\nSe han cargado los pasajeros correctamente (modo texto)\n");
							flag = 1;
							flagCargaTexto = 1;
						}
						else
						{
							printf("\nERROR al cargar el archivo (modo texto)\n");
						}
						break;
					case 2:
						if(controller_loadFromBinary("data.bin", lista)==0)
						{
							printf("\nSe han cargado los pasajeros correctamente (modo binario)\n");
						}
						else
						{
							printf("\nERROR al cargar el archivo (modo binario)\n");
						}
						break;
					case 3:
						if(controller_addPassenger(lista)==0)
						{
							printf("\nSe ha a�adido correctamente el pasajero\n");
							flag = 1;
						}
						break;
					case 4:
						if(controller_editPassenger(lista)==0)
						{
							printf("\nSe han guardado los cambios correctamente\n");
						}
						break;
					case 5:
						if(controller_removePassenger(lista)==0)
						{
							printf("\nSe ha dado de baja el pasajero\n");
						}
						break;
					case 6:
						if(controller_ListPassenger(lista)==-1)
						{
							printf("\nNo hay pasajeros para mostrar\n");
						}
						break;
					case 7:
						if(controller_sortPassenger(lista)==0)
						{
							printf("\nLISTAR los pasajeros para ver los cambios realizados\n");
						}
						break;
					case 8:
						if(flagCargaTexto == 1)
						{
							if(controller_saveAsText("data.csv", lista)==0)
							{
								printf("\nSe guardaron los datos de los pasajeros correctamente (modo texto)\n");
							}
							else
							{
								printf("\nERROR al guardar el archivo (modo texto)\n");
							}
						}
						else
						{
							printf("\nDebe cargar los datos de los pasajeros para poder guardar (opcion 1)\n");
						}
						break;
					case 9:
						if(controller_saveAsBinary("data.bin", lista)==0)
						{
							printf("\nSe guardaron los datos de los pasajeros correctamente (modo binario)\n");
						}
						else
						{
							printf("\nERROR al guardar el archivo (modo binario)\n");
						}
						break;
					case 10:
						getChars(&respuesta, sizeof(respuesta), "�Desea salir del programa? s(si) o n(no): ",
								"Ingreso un caracter invalido\n", 3);
						break;
				}
			}
			else
			{
				printf("\nPrimero debe cargar algun pasajero para avanzar\n");
			}

		}
	}while(respuesta != 's');

	printf("\n��HASTA LUEGO!!\n");

	return 0;
}


