//DRUGA MARIA-ALEXANDRA 313CB
#include "list.h"


//inserare in lista
int InsL(TLDI *a, void* x, TFCmp f)
{	
	//inserare in lista vida
	if (*a == NULL) {
		*a = calloc(1, sizeof(TCelula2));
		if (!(*a)) return 0;
		(*a)->info = x;
		(*a)->urm = *a;
		(*a)->pre = *a;
		return 1;
	}

	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
	if(!aux) return 0;

	aux->info = x;
	TLDI copie = *a;
    do {
        if (f(copie->info, x) == 1) {
			//inserare in cap de lista
			if (copie == *a) {
				aux->urm = *a;
				aux->pre = (*a)->pre;
				(*a)->pre->urm = aux;
				(*a)->pre = aux;
				(*a) = aux;
				return 1;
			}
			else {
			//inserare inainte de elementul curent
		 	aux->urm = copie;
			aux->pre = copie->pre;			
			copie->pre->urm = aux;
			copie->pre = aux;
			return 1;
			}
		}
		copie = copie->urm;
    } while (copie != *a);
			//inserare la final de lista
			aux->urm = copie;
			aux->pre = copie->pre;			
			copie->pre->urm = aux;
			copie->pre = aux;
    return 1;
}

//distrugere lista
void DistrL(TLDI s, TF f)
{
	TLDI p = s, aux;

	while (p) {
		aux = p;

		if (p->urm == p) {
			f(p->info);
			free(p);
			p = NULL;
			break;
		}

		p->urm->pre = p->pre;
		p->pre->urm = p->urm;

		p = p->urm;

		f(aux->info);
		free(aux);
	}
}
