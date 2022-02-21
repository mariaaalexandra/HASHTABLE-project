//DRUGA MARIA-ALEXANDRA 313CB
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef _LISTA_DUBLU_INLANTUITA_
#define _LISTA_DUBLU_INLANTUITA_

typedef void (*TF)(void*);
typedef int (*TFCmp)(void*, void*); 

//structura lista
typedef struct celula2
{
  void *info;
  struct celula2 *pre, *urm;
} TCelula2, *TLDI;

//structura pagina-web
typedef struct pagina 
{
  char *name;
  char *ip;
} Pag;

//inserare lista
int InsL(TLDI *a, void* x, TFCmp f);

//afisare structura
void afEL(void *el);

//distrugere lista
void DistrL(TLDI s, TF f);

#endif