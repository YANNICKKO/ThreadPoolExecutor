/*-- TStiva.h --- tipul stiva ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _FUNCTII_
#define _FUNCTII_
typedef int (*TF1)(void *, ...);
typedef int (*TF2)(const void *, const void *);
#endif

#ifndef STIVA
#define STIVA

void *InitS(size_t d);       /* initializeaza stiva cu elem.de dimensiune d;
                       anumite implementari pot necesita si alti parametri */
int Push(void *a, void *ae); /* pune element in varful stivei */
int Pop(void *a, void *ae);  /* extrage elementul din varful stivei la adresa ae */
int VidaS(void *a);          /* test stiva vida */
void DistrS(void **aa);      /* elibereaza intregul spatiu ocupat de stiva */

/* Operatii de deplasare in stiva destinatie din stiva sursa.
   Rezultat < 0 in caz de eroare (de exemplu dimensiunile elementelor difera),
   0 daca sursa vida, 1 = succes */
int Rastoarna(void *ad, void *as); /* suprapune inversul sursei peste destinatie */

#endif
