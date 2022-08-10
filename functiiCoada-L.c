/*-- functiiCoada-V.c -- elementele cozii sunt memorate intr-un vector --*/
#include "TCoada-L.h"

/* creeaza coada vida cu elemente de dimensiune d;
   este necesar si un al doilea parametru = numar maxim elemente in coada */
int VidaQ(void *a)
{
	if (((TCoada *)a)->ic == NULL && ((TCoada *)a)->sc == NULL)
		return 1;
	return 0;
}

void *InitQ(size_t d)
{
	AQ aux = calloc(1, sizeof(TCoada));
	if (aux == NULL)
		return NULL;
	aux->dime = d;
	aux->ic = NULL;
	aux->sc = NULL;
	return (void *)aux;
}

/* adauga element la sfarsitul cozii */
int IntrQ(void *a, void *ae)
{
	ACel aux = calloc(1, sizeof(TCel));
	if (aux == NULL)
		return 0;
	aux->info = calloc(1, ((TCoada *)a)->dime);
	if (aux->info == NULL)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info, ae, (((TCoada *)a))->dime);
	aux->urm = NULL;
	if (VidaQ(a))
	{
		((TCoada *)a)->ic = ((TCoada *)a)->sc = aux;
	}
	else
	{
		((TCoada *)a)->sc->urm = aux;
		((TCoada *)a)->sc = aux;
	}
	return 1;
}

/* extrage primul element din coada la adresa ae */
int ExtrQ(void *a, void *ae)
{
	if (((TCoada *)a)->ic == ((TCoada *)a)->sc)
	{
		((TCoada *)a)->sc = NULL;
	}
	if (VidaQ(a))
		return 0;
	else
	{
		ACel aux = ((TCoada *)a)->ic;
		((TCoada *)a)->ic = aux->urm;
		memcpy(ae, aux->info, ((TCoada *)a)->dime);
		free(aux->info);
		free(aux);
	}

	return 1;
}

/* transforma coada in coada vida */
void ResetQ(void *a)
{
	ACel p;
	p = ((TCoada *)a)->ic;
	while (p != NULL)
	{
		ACel aux = p;
		p = aux->urm;
		free(aux->info);
		free(aux);
	}
	((TCoada *)a)->ic = NULL;
	((TCoada *)a)->sc = ((TCoada *)a)->ic;
}

/* elibereaza intregul spatiu ocupat de coada */
void DistrQ(void **aa)
{
	ResetQ(*aa);
	free(*aa);
}

/* concatenare (muta toate elem.din sursa) */
int ConcatQ(void *ad, void *as)
{
	if (VidaQ(((TCoada *)as)))
		return 0;
	if (VidaQ(((TCoada *)ad)))
	{
		((TCoada *)ad)->ic = ((TCoada *)as)->ic;
		((TCoada *)ad)->sc = ((TCoada *)as)->sc;
		((TCoada *)as)->ic = ((TCoada *)as)->sc = NULL;
	}
	else
	{
		((TCoada *)ad)->sc->urm = ((TCoada *)as)->ic;
		((TCoada *)ad)->sc = ((TCoada *)as)->sc;
		((TCoada *)as)->ic = ((TCoada *)as)->sc = NULL;
	}
	return 1;
}
