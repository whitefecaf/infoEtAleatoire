/*
 * probaLangue.h
 *
 *  Created on: 24 janv. 2015
 *      Author: whitefecaf
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef probaLangue_H
#define probaLangue_H

enum langue {francais,anglais,italien,allemand};
typedef enum langue Langue;

typedef struct ElementLangueBis ElementLangueBis;
struct ElementLangueBis
{
    char lettre;
    int nbOccur;
    float proba;
    ElementLangueBis *suivant;
};

typedef struct ElementLangue ElementLangue;
struct ElementLangue
{
    char lettre;
    int nbOccur;
    float proba;
    ElementLangueBis *lettresuivante;
    ElementLangue *suivant
};


struct langueProb{
Langue langue;
int nblettreTotal;
ElementLangue l;
};

typedef struct langueProb LangueProb;


int initLangueProb(LangueProb *lp, Langue l);

void creationBaseProba(LangueProb *lp, char *namefile, int condition);

void saveProba(LangueProb lp);

void calculProba(LangueProb *lp, float *proba);


Langue searchLangue(char *mot,float **probaLangue);


#endif
