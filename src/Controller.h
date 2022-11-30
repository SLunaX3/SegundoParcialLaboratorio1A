/*
 * Controller.h
 *
 *  Created on: 30 nov. 2022
 *      Author: sblun
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "LinkedList.h"

int controller_menuMain();
void controller_confirmarSalida(char* x);
int controller_loadFromTextMovies(char* path, LinkedList* pArrayListMovies, int*pFlag);
int controller_imprimirMovies(LinkedList* pArrayMovies, int flag);
LinkedList* controller_AsignarTiempor(LinkedList* pArrayMovies, int* pFlag);
LinkedList* controller_FiltrarGenero(LinkedList* pArrayMovies);
int controller_sort(LinkedList* pArrayMovies, int pFlag);
int controller_MovieSaveAsText(char* path, LinkedList* pArrayListMovie, int flag);

#endif /* CONTROLLER_H_ */
