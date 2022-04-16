/*
 ============================================================================
 Name        : TP_[1].c
 Author      : Julian Carraro
 Version     : 1E
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "bibliotecaPedirDatos.h"
#include "bibliotecaCalculos.h"

#define DESCUENTO 0.9
#define INTERES 1.25
#define BTC 4606954.55

int main(void) {
	setbuf(stdout, NULL);

	int opcionesDelMenu;
	int verificacionRetorno;
	int flagMenu;
	float kilometros;
	float precioAerolineas;
	float precioLatam;
	float precioConDebitoLatam;
	float precioConDebitoAerolineas;
	float precioConCreditoAerolineas;
	float precioConCreditoLatam;
	float precioConBitcoinLatam;
	float precioConBitcoinAerolineas;
	float precioPorKmAerolineas;
	float precioPorKmLatam;
	float diferenciaDePrecio;
	int flagPrecioDeVuelos;
	int flagCalculosPrecios;
	char respuesta;
	int opcionMenuPrecios;
	int flagPrecioAerolineas;
	int flagPrecioLatam;
	char volverAtras;

	flagMenu = 0;
	flagPrecioDeVuelos = 0;
	flagCalculosPrecios = 0;
	flagPrecioAerolineas = 0;
	flagPrecioLatam = 0;

	do
	{
		if(flagMenu == 0)
		{
			flagPrecioAerolineas = 0;
			flagPrecioLatam = 0;
			flagCalculosPrecios = 0;
			flagPrecioDeVuelos = 0;
			kilometros = 0;
			precioAerolineas = 0;
			precioLatam = 0;
		}

		system("cls");
		printf("\n******************************MENU PRINCIPAL******************************\n\n");
		printf("1) Ingresar Kilometros (km = %.2f) \n", kilometros);
		printf("2) Ingresar Precio de Vuelos (Aerolineas = $%.2f, Latam = $%.2f)\n", precioAerolineas, precioLatam);
		printf("3) Calcular todos los costos\n");
		printf("4) Informar Resultados\n");
		printf("5) Carga forzada de datos\n");
		printf("6) Salir\n");

		verificacionRetorno = getInt(&opcionesDelMenu ,"Ingrese una opcion: ", "La opcion no es correcta\n\n", 6, 1, 5);

		if(verificacionRetorno == 0)
		{
			if(opcionesDelMenu == 1 || flagMenu == 1 || opcionesDelMenu == 6 || opcionesDelMenu == 5)
			{
				switch(opcionesDelMenu)
				{
					case 1:
						verificacionRetorno = getFloat(&kilometros ,"Ingresar Kilometros: ", "La km no son validos \n\n", 30000, 1, 3);
						if(verificacionRetorno == 0)
						{
							flagMenu = 1;
							flagCalculosPrecios = 0;
						}
						break;
					case 2:
						do
						{
							volverAtras = 'n';
							system("cls");
							printf("\nIngresar Precios de Vuelos \n\n");
							printf("1) Ingresar Precio Aerolineas (Aerolineas = $%.2f)\n", precioAerolineas);
							printf("2) Ingresar Precio Latam (Latam = $%.2f)\n", precioLatam);
							printf("3) Volver atras\n");

							verificacionRetorno = getInt(&opcionMenuPrecios ,"Ingrese una opcion: ", "La opcion no es valida \n\n", 3, 1, 3);

							if(verificacionRetorno == 0)
							{
								switch(opcionMenuPrecios)
								{
									case 1:
										verificacionRetorno = getFloat(&precioAerolineas ,"Precio vuelo Aerolineas: $", "El precio no es valido \n\n", 1500000, 1, 3);
										if(verificacionRetorno == 0)
										{
											flagPrecioAerolineas = 1;
											flagCalculosPrecios = 0;
										}
										break;
									case 2:
										verificacionRetorno = getFloat(&precioLatam ,"Precio vuelo LATAM: $", "El precio no es valido \n\n", 1500000, 1, 3);
										if(verificacionRetorno == 0)
										{
											flagPrecioLatam = 1;
											flagCalculosPrecios = 0;
										}
										break;
									case 3:
										if(flagPrecioAerolineas == 1 || flagPrecioLatam == 1)
										{
											volverAtras = printf("Seguro que desea volver atras? s(si)/n(no): ");
											fflush(stdin);
											scanf("%c", &volverAtras);
											flagPrecioDeVuelos = 1;
										}
										else
										{
											printf("Debe ingresar, al menos, uno de los datos para volver al Menu Principal\n");
											system("pause");
										}
										break;
								}
							}

						}while(volverAtras != 's');
						break;
					case 3:
						if(flagPrecioDeVuelos == 1)
						{
							if(flagPrecioAerolineas == 1)
							{
								precioConDebitoAerolineas = producto(precioAerolineas, DESCUENTO);
								precioConCreditoAerolineas = producto(precioAerolineas, INTERES);
								precioConBitcoinAerolineas = reglaDeTresSimples(precioAerolineas, 1, BTC);
								precioPorKmAerolineas = reglaDeTresSimples(1, precioAerolineas, kilometros);
							}
							if(flagPrecioLatam == 1)
							{
								precioConDebitoLatam = producto(precioLatam, DESCUENTO);
								precioConCreditoLatam =	producto(precioLatam, INTERES);
								precioConBitcoinLatam =	reglaDeTresSimples(precioLatam, 1, BTC);
								precioPorKmLatam = reglaDeTresSimples(1, precioLatam, kilometros);
							}
							if(flagPrecioAerolineas == 1 && flagPrecioLatam == 1)
							{
								diferenciaDePrecio = calculoDiferencia(precioLatam, precioAerolineas);
							}

							flagCalculosPrecios = 1;

							printf("Hemos calculado sus costos\n");
							system("pause");
						}
						else
						{
							printf("Antes, debes indicar los precios del vuelo\n");
							system("pause");
						}
						break;
					case 4:
						if(flagPrecioDeVuelos == 1)
						{
							if(flagCalculosPrecios == 1)
							{
								printf("*************************INFORMAR RESULTADOS*************************\n\n");
								printf("\nKMs Ingresados: %.2fkm\n\n", kilometros);
								if(flagPrecioAerolineas == 1)
								{
									printf("PRECIO AEROLINEAS: $%.2f\n", precioAerolineas);
									printf("Precio con tarjeta de debito: $%.2f\n", precioConDebitoAerolineas);
									printf("Precio con tarjeta de credito: $%.2f\n", precioConCreditoAerolineas);
									printf("Precio pagando con bitcoin: %.8f BTC\n", precioConBitcoinAerolineas);
									printf("Precio unitario: $%.2f\n\n", precioPorKmAerolineas);
								}
								if(flagPrecioLatam == 1)
								{
									printf("PRECIO LATAM: $%.2f\n", precioLatam);
									printf("Precio con tarjeta de debito: $%.2f\n", precioConDebitoLatam);
									printf("Precio con tarjeta de credito: $%.2f\n", precioConCreditoLatam);
									printf("Precio pagando con bitcoin: %.8f BTC\n", precioConBitcoinLatam);
									printf("Precio unitario: $%.2f\n\n", precioPorKmLatam);
								}
								if(flagPrecioAerolineas == 1 && flagPrecioLatam == 1)
								{
									printf("La diferencia de precio es de: $%.2f\n", diferenciaDePrecio);
								}

								system("pause");

								flagMenu = 0;
							}
							else
							{
								printf("Debes calcular los precios antes de mostrarlos\n");
								system("pause");
							}
						}
						else
						{
							printf("Antes, debes indicar los precios del vuelo\n");
							system("pause");
						}
						break;
					case 5:
						kilometros = 7090;
						precioAerolineas = 162965;
						precioLatam = 159339;

						precioConDebitoAerolineas = producto(precioAerolineas, DESCUENTO);
						precioConDebitoLatam = producto(precioLatam, DESCUENTO);

						precioConCreditoAerolineas = producto(precioAerolineas, INTERES);
						precioConCreditoLatam =	producto(precioLatam, INTERES);

						precioConBitcoinAerolineas = reglaDeTresSimples(precioAerolineas, 1, BTC);
						precioConBitcoinLatam =	reglaDeTresSimples(precioLatam, 1, BTC);

						precioPorKmAerolineas = reglaDeTresSimples(1, precioAerolineas, kilometros);
						precioPorKmLatam = reglaDeTresSimples(1, precioLatam, kilometros);

						diferenciaDePrecio = calculoDiferencia(precioLatam, precioAerolineas);

						system("cls");
						printf("*************************INFORMAR RESULTADOS*************************\n\n");
						printf("\nKMs Ingresados: %.2fkm\n\n", kilometros);
						printf("PRECIO AEROLINEAS: $%.2f\n", precioAerolineas);
						printf("Precio con tarjeta de debito: $%.2f\n", precioConDebitoAerolineas);
						printf("Precio con tarjeta de credito: $%.2f\n", precioConCreditoAerolineas);
						printf("Precio pagando con bitcoin: %.8f BTC\n", precioConBitcoinAerolineas);
						printf("Precio unitario: $%.2f\n\n", precioPorKmAerolineas);
						printf("PRECIO LATAM: $%.2f\n", precioLatam);
						printf("Precio con tarjeta de debito: $%.2f\n", precioConDebitoLatam);
						printf("Precio con tarjeta de credito: $%.2f\n", precioConCreditoLatam);
						printf("Precio pagando con bitcoin: %.8f BTC\n", precioConBitcoinLatam);
						printf("Precio unitario: $%.2f\n\n", precioPorKmLatam);
						printf("La diferencia de precio es de: $%.2f\n", diferenciaDePrecio);
						system("pause");

						flagMenu = 0;
						break;
					case 6:
						respuesta = printf("Seguro que desea salir? s(si)/n(no)");
						fflush(stdin);
						scanf("%c", &respuesta);
						break;
				}
			}
			else
			{
				printf("Primero debe ingresar los KM\n");
				system("pause\n");
			}

		}

	}while(respuesta != 's');

	return EXIT_SUCCESS;

}

