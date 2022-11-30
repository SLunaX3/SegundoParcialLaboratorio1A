/*
 ============================================================================
 Name        : PARCIAL2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Movie.h"

int main(void) {

	setbuf(stdout, NULL);
    char salir = 'n';
    int flag = 0;

    LinkedList* listaMovies = ll_newLinkedList();
    LinkedList* listaMap = ll_newLinkedList();
    LinkedList* filtrarGenero = ll_newLinkedList();

    do
    {
        switch(controller_menuMain())
        {
            case 1:
                controller_loadFromTextMovies("movies.csv", listaMovies, &flag);
                break;
            case 2:
                controller_imprimirMovies(listaMovies, flag);
                break;
            case 3:
                listaMap = controller_AsignarTiempor(listaMovies, &flag);
                controller_imprimirMovies(listaMap, flag);
                break;
            case 4:
                filtrarGenero = controller_FiltrarGenero(listaMovies);
                controller_imprimirMovies(filtrarGenero, flag);
                break;
            case 5:
                if(controller_sort(listaMovies, flag))
                {
                   controller_imprimirMovies(listaMovies, flag);
                }
                break;
            case 6:
                controller_MovieSaveAsText("listaSort.csv", listaMovies, flag);
                break;
            case 7:
                controller_confirmarSalida(&salir);
                break;
            default:
                printf("\n ***** Opcion Invalida ! *****\n\n");
            break;
        }
    }while(salir != 's');


    ll_deleteLinkedList(listaMovies);
    ll_deleteLinkedList(listaMap);
    ll_deleteLinkedList(filtrarGenero);


	return EXIT_SUCCESS;
}
