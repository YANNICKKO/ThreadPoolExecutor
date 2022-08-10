/*-- TCoada-V.h -- elementele cozii sunt memorate intr-un vector --*/
#include "TCoada.h"

#ifndef _COADA_VECTOR_
#define _COADA_VECTOR_

typedef struct cel /* dimensiune variabila */
{
	struct cel *urm;
	void *info;
} TCel, *ACel;
typedef struct coada
{
	size_t dime; /* dim.element */
	ACel ic, sc; /* adr.prima, ultima celula */
} TCoada, *AQ;

#endif
