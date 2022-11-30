/*
 * Validar.c
 *
 *  Created on: 30 nov. 2022
 *      Author: sblun
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Validar.h"

/// @brief Verifica si la cadena ingresada es numerica
///
/// @param cadena Cadena de caracteres a ser analizada
/// @param len Tamaño de la cadena a analizar
/// @return Retorna 1 si es numerica, 0 sino no lo es
int esNumero(char* cadena)
{
	   int todoOk = 1;
	    int esNumero;

	    if(cadena != NULL)
	    {
	        for(int i = 0; i < strlen(cadena) -1; i++)
	        {
	            esNumero = isdigit(cadena[i]);
	            if(esNumero == 0)
	            {
	                todoOk = 0;
	                break;
	            }
	        }
	    }

	    return todoOk;
}




int pidoValidoNumeroRango(int* pNumero, char mensaje[], int minimo, int maximo)
{
    int todoOk = 0;
    char bufferNum[100];
    int numero;

    if(pNumero != NULL && mensaje != NULL && minimo < maximo)
    {
        printf(" Ingrese %s: ", mensaje);
        fflush(stdin);
        fgets(bufferNum, 100, stdin);
        while(esNumero(bufferNum) == 0 || stricmp(bufferNum , "\n") == 0) // ver puntero de "esNumero"
        {
            printf("*** Ingreso inválido ****.\n--> Reingrese %s: ", mensaje);
            fflush(stdin);
            fgets(bufferNum, 100, stdin);
        }
        if(convertirCharAInt(bufferNum, &numero))
        {
            if(numero < minimo || numero > maximo)
            {
                printf("***** Numero fuera de rango, NO GUARDADO! Reintente\n");
            }
            else
            {
                *pNumero = numero;
                todoOk = 1;
            }

        }
    }
    return todoOk;
}


int convertirCharAInt(char num[], int* pNumero)
{
    int todoOk = 0;

    if(num != NULL && pNumero != NULL)
    {
        *pNumero = atoi(num);
        todoOk = 1;
    }
    return todoOk;
}

int validaConvierteChar_Int(char num[], int* pNumero)
{
    int todoOk = 1;
    int esNumero;

    if(num != NULL)
    {
        for(int i=0; i < strlen(num); i++)
        {
            esNumero = isdigit(num[i]);
            if(esNumero == 0)
            {
                puts("Error no es un numero...\n");
                todoOk = 0;
                break;
            }
            else
            {
                *pNumero = atoi(num);
            }
        }
    }
    return todoOk;
}
