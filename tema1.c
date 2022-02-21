//DRUGA MARIA-ALEXANDRA 313CB
#include "list.h"
#include "table.h"

//dezalocare structura
void dezaloc(void *el)
{
    Pag *pagina = (Pag *)el;
    free(pagina->name);
    if (pagina->ip) free(pagina->ip);
    free(pagina);
}

//functie cod tabela
int codHash(void * element)
{
	Pag *page  = (Pag *)element;
    int len = strlen(page->name), i, suma = 0;

    //calculez suma caracterelor ASCII
    for (i = 0; i < len; i++) {
        suma = suma + (int)((page->name)[i]);
    }

	return suma;
}

//compar alfabetic
int alfa(void *el1, void *el2)
{
    Pag *pag1 = (Pag *)el1;
    Pag *pag2 = (Pag *)el2;

    //verific ordonarea alfabetica
    if (strcmp(pag1->name, pag2->name) > 0) {
        return 1;
    }
    return 0;
}

//adaugare pereche
void put (void *element, TH *h, TFCmp f)
{
    //calcul cod
    int cod = h->fh(element) % h->M;
    //inserare element in tabela
    InsL(h->v + cod, element, f);
}

//afisare structura
void afiEL(void *el)
{
    Pag *page = (Pag *)el;

    //afisez informatia din celula
    printf("%s %s\n", page->name, page->ip);
}

//alocare structura
Pag * alocare(char *key, char *val)
{
    //aloc fiecare camp al structurii

   Pag *page = malloc(sizeof(Pag));
   page->ip = malloc(30 * sizeof(char));
   if (page->ip == NULL) {
       exit(1);
   }
   page->name = malloc(30 * sizeof(char));
   if (page->name == NULL) {
       exit(1);
   }
   strcpy(page->name, key);
   strcpy(page->ip, val);

   return page;
}

//verificare elemente cu key identice
int comp_key(void *el1, void *el2)
{
    Pag *page1 = (Pag *)el1;
    Pag *page2 = (Pag *)el2;
    if (strcmp(page1->name, page2->name) == 0) {
        return 1;
    }
    return 0;    
}

//cautare elemente in lista
int find(TH *h, void *el, TFCmp f)
{   
    //calculez codul elementului si parcurg lista pentru cautare
    int cod = h->fh(el) % h->M;
    TLDI copie1 = h->v[cod];

    if (!copie1) return 0;
        do {
            if (f(copie1->info, el) == 1) {
                return 1;
            }
            copie1 = copie1->urm;
        } while (copie1 != h->v[cod]);
    return 0;
}

//returneaza valoarea lui key gasita
void *get(TH *h, void *el, TFCmp f)
{   
    //calculez codul si parcurg lista pentru a gasi key
    int cod = h->fh(el) % h->M;
    TLDI copie1 = h->v[cod];

    if (!copie1) return NULL;
        do {
            if (f(copie1->info, el) == 1) {
                return copie1->info;
            }
            copie1 = copie1->urm;
        } while (copie1 != h->v[cod]);
    return NULL;
}

//eliminare
void Eliminare(TH *h, void *el, TFCmp f, TF g)
{   
    //calculez cod si parcurg lista
    int cod = h->fh(el) % h->M;
    TLDI p = h->v[cod];
    if(!p) return;
	
	do {
		if (f(p->info, el) == 1) {
            //lista cu un singur element
            if (p->urm == p) {
                h->v[cod] = NULL;
                g(p->info);
                free(p);
                return;
            }
            //eliminare primul element
            else if (p == h->v[cod]) {
                (h->v[cod])->pre->urm  = p->urm;
		        (h->v[cod])->urm->pre = p->pre;
                (h->v[cod]) = p->urm;
                g(p->info);
                free(p);
                return;
            }
            //eliminare element oarecare
            else {
                p->pre->urm = p->urm;
		        p->urm->pre = p->pre;
                g(p->info);
		        free(p);
                return;
            }
        }
        p = p->urm;
	}while (p != h->v[cod]);
}

//afisare ip
void af(void *el, FILE *f)
{
    Pag *pagina = (Pag *)el;
    
    //afisez ip-ul structurii
    fprintf(f, "%s ", pagina->ip);
}

//afisare ip pentru elemente din bucket
void print_bucket(int nr, TH *h, FILE *f)
{   
    //verificare numar de bucket
    if(nr > h->M || nr == h->M) {
        return;
    }
    TLDI p = h->v[nr];
    if (!p) {
        fprintf(f, "VIDA\n");
        return;
    }

    //afisez informatia din structura 
    do {
        af(p->info, f);
        p = p->urm;
    } while (p != h->v[nr]);
    fprintf(f, "\n");
}

//afisare tabela
void print(TH *h, FILE *f)
{
    int i;
    //afisez informatia din celule din bucket-uri valide
    for (i = 0; i < h->M; i++) {
        TLDI p = h->v[i];
        if (p != NULL) {
            fprintf(f, "%d: ", i);
            print_bucket(i, h, f);
        }            
    }
}

int main(int argc, char *argv[])
{
    //numar de bucket-uri
    int M = atoi(argv[1]);
    TH *h = IniTH(M, codHash);

    //deschid fisierele de citire si scriere
    FILE *fp, *gp;
    fp = fopen(argv[2], "rt");
    if (fp == NULL) {
        exit(2);
        printf("EROARE DESCHIDERE FISIER\n");
    }
    gp = fopen(argv[3], "wt");
    if (gp == NULL) {
        exit(2);
        printf("EROARE DESCHIDERE FISIER\n");
    }

    //aloc dinamic linia din fisier
    char *line = calloc(50, sizeof(char));
    if (line == NULL) {
        exit(1);
        printf("EROARE DE ALOCARE\n");
    }

    while (fgets(line, 50, fp) != NULL) {
        char *comanda = strtok(line, " \n");
        if (!comanda) break;
        if (strcmp(comanda, "put") == 0) {
            char *nume = strtok(NULL, " ");
            char *add = strtok(NULL, " \n");
            Pag *pagina = alocare(nume, add);
            if (find(h, (void *)pagina, comp_key) == 0) {
                put((void *)pagina, h, alfa);
            }
            else {
                dezaloc(pagina);
            }
        }
        else if (strcmp(comanda, "find") == 0) {
            char *nume = strtok(NULL, " \n");
            Pag *pagina = malloc(sizeof(Pag));
            if (pagina == NULL) {
                exit(1);
                printf("EROARE DE ALOCARE\n");
            }
            pagina->name = malloc(30 * sizeof(char));
            if (pagina->name == NULL) {
                exit(1);
                printf("EROARE DE ALOCARE\n");
            }
            strcpy(pagina->name, nume);
            pagina->ip = NULL;
            if (find(h, (void *)pagina, comp_key) == 0) {
                fprintf(gp, "False\n");
            }
            else {
                fprintf(gp, "True\n");
            }
            dezaloc(pagina);
        }
        else if (strcmp(comanda, "get") == 0) {
            char *nume = strtok(NULL, " \n");
            Pag *pagina = malloc(sizeof(Pag));
            if (pagina == NULL) {
                exit(1);
                printf("EROARE DE ALOCARE\n");
            }
            pagina->name = malloc(30 * sizeof(char));
            if (pagina->name == NULL) {
                exit(1);
                printf("EROARE DE ALOCARE\n");
            }
            strcpy(pagina->name, nume);
            pagina->ip = NULL;

            if (get(h, (void *)pagina, comp_key) != NULL) {
                Pag *page = (Pag *)(get(h, (void *)pagina, comp_key));
                fprintf(gp, "%s\n", page->ip);
            }
            else {
                fprintf(gp, "NULL\n");
            }
           dezaloc(pagina);
        }
        else if (strcmp(comanda, "remove") == 0) {
            char *nume = strtok(NULL, " \n");
            Pag *pagina = malloc(sizeof(Pag));
            if (pagina == NULL) {
                exit(1);
                printf("EROARE DE ALOCARE\n");
            }
            pagina->name = malloc(30 * sizeof(char));
            if (pagina->name == NULL) {
                exit(1);
                printf("EROARE DE ALOCARE\n");
            }
            strcpy(pagina->name, nume);
            pagina->ip = NULL;
            Eliminare(h, (void *)pagina, comp_key, dezaloc);
            dezaloc(pagina);
        }
        else if (strcmp(comanda, "print_bucket") == 0) {
            char *index = strtok(NULL, " \n");
            int ind = atoi(index);
            print_bucket(ind, h, gp);
        }
        else {
            print(h, gp);
        }
    }

    DistrTH(&h, dezaloc);
    free(line);
    fclose(fp);
    fclose(gp);

    return 0;
}