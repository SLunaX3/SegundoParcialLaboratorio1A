/*
 * Controller.c
 *
 *  Created on: 30 nov. 2022
 *      Author: sblun
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Controller.h"
#include "Movie.h"
#include "Validar.h"
#include "Parser.h"


int controller_menuMain()
{
    int opcion;

    printf("\n****** MENU ******\n\n");
    printf("1. Cargar archivo de Peliculas.\n");
    printf("2. Imprimir Lista.\n");
    printf("3. Asignar Tiempos.\n");
    printf("4. Filtrar por tipo.\n");
    printf("5. Mostrar duraciones.\n");
    printf("6. Guardar peliculas.\n");
    printf("7. Salir\n");

    pidoValidoNumeroRango(&opcion, "Opcion ", 1, 7);

    return opcion;
}

void controller_confirmarSalida(char* x)
{
    if(x != NULL)
    {
        printf("Presione 's' para confirmar salida: ");
        fflush(stdin);
        scanf("%c", x);
        *x = tolower(*x);
        printf("**** Hasta pronto! *****\n");
    }
    else
    {
        printf("**** ERROR! No se realizo el guardado de archivo *****\n");
    }

}

int controller_loadFromTextMovies(char* path, LinkedList* pArrayListMovies, int*pFlag)
{
	int todoOk = -1;
	FILE* f = NULL;

    if(path != NULL && pArrayListMovies != NULL)
    {
        if((f = fopen(path, "r")) != NULL) //Condicional, verifico si la lectura del archivo, si no retorna NULL accedo al jugador
        {
        	parser_MoviesFromText(f, pArrayListMovies);
            printf("****Lista de peliculas cargada con exito! ****\n");

            todoOk = 1;
        }
        else{ //Si retorna NULL no encontro el archivo, por lo tanto lo creo e informo que no se encontro y se creo uno nuevo
            if((f = fopen(path, "w")) != NULL){
                printf("\n --> No se encontro el archivo. Se creo uno nuevo con el nombre \"%s\"\n\n", path);
                todoOk = 0;
            }
        }
        fclose(f);
        *pFlag = 1;
        todoOk = 1;

    }
    else
    {
    	printf("**** ERROR. La lista ya fue cargada ! *****\n");
    }
    return todoOk;

}

int controller_imprimirMovies(LinkedList* pArrayMovies, int flag)
{
    int todoOk = 0;
    eMovie* unMovie;
    int len = ll_len(pArrayMovies);
    if(pArrayMovies != NULL && flag > 0)
    {
        printf("************************** LISTADO DE PELICULAS ********************************\n\n");
        printf("---------------------------------------------------------------------------------\n");
        printf(" ID                         TITULO                      GENERO          DURACION\n");
        printf("---------------------------------------------------------------------------------\n");

        for(int i=0; i < len ; i++)
        {
            unMovie = (eMovie*) ll_get(pArrayMovies, i);
            Movie_mostrarDinamico(unMovie);
        }
        todoOk = 1;
    }
    else
    {
        printf("***** Debe cargar primero el archivo *****\n");
    }
    return todoOk;
}


LinkedList* controller_AsignarTiempor(LinkedList* pArrayMovies, int* pFlag)
{
    LinkedList* bufferLista = NULL;
    if(pArrayMovies != NULL)
    {
        bufferLista = ll_map(pArrayMovies, Movie_AsignarTiempos);
        *pFlag = 2;
    }
    return bufferLista;
}



LinkedList* controller_FiltrarGenero(LinkedList* pArrayMovies)
{
    int opcion;

    printf("\n****** Generos ******\n\n");
    printf(" 1.Adventure\n");
    printf(" 2.Drama\n");
    printf(" 3.Comedy\n");
    printf(" 4.Romance\n");
    printf(" 5.Documentary\n");
    printf(" 6.Horror\n");
    printf(" 7.Musical\n");
    printf(" 8.Animation\n");
    printf(" 9.Action\n");
    printf(" 10.Western\n");

    pidoValidoNumeroRango(&opcion, "opcion", 1, 10);

    LinkedList* bufferLista = NULL;
    if(pArrayMovies != NULL)
    {
        switch(opcion)
        {
        case 1:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero1);
            break;
        case 2:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero2);
            break;
        case 3:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero3);
            break;
        case 4:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero4);
            break;
        case 5:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero5);
            break;
        case 6:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero6);
            break;
        case 7:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero7);
            break;
        case 8:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero8);
            break;
        case 9:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero9);
            break;
        case 10:
            bufferLista = ll_filter(pArrayMovies, Movie_ComparaGenero10);
            break;
        }
    }

    return bufferLista;
}

int controller_sort(LinkedList* pArrayMovies, int pFlag)
{
    int todoOk = 0;
    if(pArrayMovies != NULL && pFlag == 2)
    {
        if(ll_sort(pArrayMovies, Movie_ComparaGenerosEntreSi, 1) == 0)
        {
            ll_sort(pArrayMovies, Movie_CompareDuracion, 0);
        }
    }
    else
    {
        printf("***** Primero debe cargar los tiempos ******\n");
    }
    return todoOk;
}

int controller_MovieSaveAsText(char* path, LinkedList* pArrayListMovie, int flag)
{
    int todoOk = 0;
    eMovie* auxiliar = NULL;
    int idPel;
    int durac;
    char buffer[1][50];

    if(path != NULL && pArrayListMovie != NULL && flag == 2)
    {
        FILE* f = fopen(path, "w");

        if(f != NULL)
        {

        	fprintf(f,"%s,%s\n", "id", "nombre");
        	for(int i=0; i<ll_len(pArrayListMovie); i++)
            {
                auxiliar = ll_get(pArrayListMovie, i);
                if(Movie_GetIdPeli(auxiliar, &idPel)
                    && Movie_GetTitulo(auxiliar,buffer[0])
                    && Movie_GetGenero(auxiliar, buffer[1])
                    && Movie_Getduracion(auxiliar, &durac))
                {
                    fprintf(f,"%d,%s,%s,%d\n", idPel,buffer[0],buffer[1],durac);
                    todoOk = 1;
                }
                else
                {
                    printf("***** ERROR No se pudo escribir el archivo! *****\n");
                }
            }


            if(todoOk)
            {
                printf("***** Guardado con exito! *****\n");
            }


        }
        else
        {
        	printf("***** No se pudo abrir el archivo *****\n");
        }

        fclose(f);


    }
    else
    {
        printf("***** Primero debe realizar el punto 5 *****\n");
    }
    return todoOk;
}
