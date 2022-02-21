//DRUGA MARIA-ALEXANDRA 313CB
#include "table.h"

//initializare tabela
TH* IniTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLDI *) calloc(M, sizeof(TLDI));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

//distrugere tabela
void DistrTH(TH** ah, TF fe)
{
    TLDI *p;
    
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        DistrL(*p, fe);
    }

    free((*ah)->v);
    free(*ah);
    *ah = NULL;

    return;
}