

#ifndef DECORATION_H_
#define DECORATION_H_

#include "../Model/sala.h"
#include "../My_Libraries/LinkedList.h"

#endif /* DECORATION_H_ */

void printf_highlight(char* startString, char* colorString, char* endString, void (*pFuncColor)(void));
void decoration_printCinepolisLogo(void);
int decoration_printUbicacionesSala(LinkedList *listaUbicaciones, eSala sala);
int decoration_printCarritoCompra(LinkedList *carrito);
