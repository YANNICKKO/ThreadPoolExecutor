/*-- functiiStiva-V.c -- elementele stivei sunt memorate intr-un vector --*/
#include "TStiva-L.h"

/* creeaza stiva vida cu elemente de dimensiune d;
	   este necesar si un al doilea parametru = numar maxim elemente in coada */
void *InitS(size_t d)
{
	ASt s;
	s = (ASt)malloc(sizeof(TStiva));
	if (!s)
		return NULL;

	s->dime = d;
	s->vf = NULL;

	return (void *)s;
}

/* pune element in varful stivei */
int Push(void *a, void *ae)
{
	ACelSt aux = (ACelSt)malloc(sizeof(TCelSt));
	if (!aux)
		return 0;
	aux->info = malloc((((TStiva *)a)->dime));
	if (aux->info == NULL)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info, ae, ((TStiva *)a)->dime);
	aux->urm = ((TStiva *)a)->vf;
	((TStiva *)a)->vf = aux;
	return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void *s, void *ae)
{
	if (((TStiva *)s)->vf == NULL)
		return 0;
	memcpy(ae, ((TStiva *)s)->vf->info, ((TStiva *)s)->dime);
	ACelSt aux = ((TStiva *)s)->vf;
	((TStiva *)s)->vf = aux->urm;
	free(aux->info);
	free(aux);
	return 1;
}

/* test stiva vida */
int VidaS(void *a)
{
	if (((TStiva *)a)->vf == NULL)
		return 1;
	return 0;
}

/* elibereaza intregul spatiu ocupat de stiva */
void DistrS(void **aa)
{
	ACelSt l = ((TStiva *)*aa)->vf;
	while (l != NULL)
	{
		ACelSt aux = l;
		free(aux->info);
		l = aux->urm;
		free(aux);
	}
	((TStiva *)*aa)->vf = NULL;

	free(*aa);
}

/* suprapune inversul sursei destinatie */
int Rastoarna(void *ad, void *as)
{
	if (as == NULL)
		return 0;
	if (((TStiva *)ad)->dime != ((TStiva *)as)->dime)
		return 0;
	ACelSt ld = ((TStiva *)ad)->vf;
	ACelSt ls = ((TStiva *)as)->vf;
	ACelSt aux;
	while (ls)
	{
		aux = ls;
		ls = ls->urm;
		aux->urm = ld;
		ld = aux;
	}
	((TStiva *)as)->vf = NULL;
	((TStiva *)ad)->vf = ld;
	return 1;
}
