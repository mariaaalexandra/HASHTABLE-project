//DRUGA MARIA-ALEXANDRA 313CB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "list.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

//comparare element
typedef int (*TFCmp)(void*, void*);

//cod element
typedef int (*TFHash)(void*);

//afisare element
typedef void (*TF)(void*);

//structura tabela
typedef struct
{
    size_t M;
    TFHash fh;
    TLDI *v;
} TH;

//initializare tabela
TH* IniTH(size_t M, TFHash fh);

//distrugere tabela
void DistrTH(TH** ah, TF fe);

#endif