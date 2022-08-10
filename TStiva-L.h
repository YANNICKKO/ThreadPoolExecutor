/*-- TStiva-V.h -- elementele stivei sunt memorate intr-un vector --*/
#include "TStiva.h"

#ifndef _STIVA_VECTOR_
#define _STIVA_VECTOR_

typedef struct celst
{
	struct celst *urm; /* adr.urmatoarei celule */
	void *info;		   /* adresa informatie */
} TCelSt, *ACelSt;
typedef struct stiva
{
	size_t dime; /* dim.element */
	ACelSt vf;	 /* adresa celulei din varf */
} TStiva, *ASt;

#endif
