/*
 * probaLangue.c
 *
 *  Created on: 24 janv. 2015
 *      Author: whitefecaf
 */
#include "probaLangue.h"

void increment(LangueProb *lp, char lettre)
{
	lp->nblettreTotal = (lp->nblettreTotal) + 1;
	ElementLangue *elem = lp->l;
	while(elem->lettre != lettre)
		elem = elem->suivant;
	elem->nbOccur = (elem->nbOccur) + 1;
}

void incrementation(LangueProb *lp, char lettre, char lettrePrec)
{
	lp->nblettreTotal = (lp->nblettreTotal) + 1;
	ElementLangue *elem = lp->l;
	while(elem->lettre != lettre)
		elem = elem->suivant;
	elem->nbOccur = (elem->nbOccur) + 1;
	ElementLangueBis *l = elem->lettreSuivante;
	while(l->lettre != lettrePrec)
		l = l->suivant;
	l->nbOccur = (l->nbOccur) + 1;
}

void calculProba(LangueProb *lp, float *proba)
{
	int i;
	for(i=0; i<26; i++)
	{
		proba[i] = (float)(lp->nbLettre[i]+1)/((float)(lp->nbLettreTotal +26));
	}
}

void calculProbaInternal(char *tabLetter, int nbLetter, float *proba)
{
    int i;
	for(i=0; i<26; i++)
	{
		proba[i] = (float)(tabLetter[i]+1)/((float)(nbLetter +26));
	}
}
Langue comparProba(float *prob,float **probaLangue)
{
    int i, j;
    float **diffProba;
    diffProba = malloc(4*sizeof(float*));
    diffProba[0] = malloc (26* sizeof(float));
    diffProba[1] = malloc (26* sizeof(float));
    diffProba[2] = malloc (26* sizeof(float));
    diffProba[3] = malloc (26* sizeof(float));
    for(j = 0; j < 4; j++)
        for(i = 0; i < 26;i++)
            diffProba[j][i] = probaLangue[j][i] - prob[i];

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 26; i++)
            printf("proba %d : %f ", j, diffProba[j][i]);
        printf("\n");
    }
    return francais;

}
void creationBaseProba(LangueProb *lp, char *namefile , int condition)
{
	if (condition == 1)
	{
		FILE *f  = fopen(namefile,"r");
		int lettrePrec = ' ';
		if(f == NULL)
		{
			printf("erreur sur l'ouverture du fichier");
		}else{
			int lettre;
			lettre = fgetc(f);
			while(lettre != EOF)
			{
				switch(lettre)
				{
					case' ' :
						;
					break;
					default :
						if(lettrePrec != ' ')
						{
							increment(lp, lettre); 
						}else
						{
							incrementation(lp, lettre, lettrePrec);  
						}
						lettrePrec = lettre;
					break;
				}
				lettre = fgetc(f);

			}
			fclose(f);
		}
	}
}
int initLangueProb( LangueProb *lp, Langue l)
{
	FILE *f;
	int i;
	ElementLangue *elem1;
	ElementLangueBis * elem2;
	ElementLangue *elem;
	ElementLangueBis *Elembis;
	lp->langue = l;
	lp->nblettreTotal = 0;
	elem1 = malloc(sizeof(ElementLangue));
	elem2 = malloc(sizeof(ElementLangueBis));
	elem = malloc(sizeof(ElementLangue));
	elembis = malloc(sizeof(ElementLangueBis));
	
	
	//1er élément
	elem->lettre = 'a';
	elem->nbOccur = 0;
	lp->l = elem;
	//1er élément de lettre suivante pour l'instance du premier élément
	elembis->lettre = 'a';
	elembis->nbOccur = 0;
	lp->l->lettreSuivante = elembis;
	for(i=1; i < 'z' - 97; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = 'a' + i;
		elembis->suivant = elem2;
		elembis->nbOccur = 0;
		elembis = elem2;
	}
	//création du dictionnaire (1er élément deja créer)
	for(i=1; i < 'z' - 97; i++)
    {
		elem1 = malloc(sizeof(ElementLangue));
        elem1->lettre = 'a' + i;
        elem1->nbOccur = 0;
		elem->suivant = elem1;
        elem = elem1;
		//1er élément de lettre suivante pour l'instance en cours
		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		elembis->nbOccur = 0;
		elem->lettreSuivante = elembis;
		for(i=1; i < 'z' - 97; i++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = 'a' + i;
			elembis->suivant = elem2;
			elembis->nbOccur = 0;
			elembis = elem2;
		}
		

    }
	if (lp->langue == francais && access("saveProbaFR",F_OK) == 0)
	{
		f= fopen("saveProbaFR","r");
		for (i=0; i<26; i++)
		{
			fprintf(f,"%c : %d ",l1->lettre, l1->nbOccur);
			l = l1->lettreSuivante;
			for (i=0; i<26; i++)
			{
				fprintf(f,"%c : %d ",l->lettre, l->nbOccur);
			}
			l1 = l1.suivant;
			fprintf(f,"\n",l->lettre, l->nbOccur);
		}
	fclose(f);
	}
	else if (lp->langue == anglais && access("saveProbaEN",F_OK) == 0)
	{
		f= fopen("saveProbaEN","r");
		for(i = 0;i<26; i++)
            //TODO
            ;
	}
	else if (lp->langue == italien && access("saveProbaIT",F_OK) == 0)
	{
		f= fopen("saveProbaIT","r");
		for(i = 0;i<26; i++)
			//TODO
            ;
	}
	else if (lp->langue == allemand && access("saveProbaDE",F_OK) == 0)
	{
		f= fopen("saveProbaDE","r");
		for(i = 0;i<26; i++)
			//TODO
			;
	}
	return 0;
}
void saveProba(LangueProb lp)
{
	FILE *f;
	int i;
	do
	{
		if (lp.langue == francais)
			f= fopen("saveProbaFR.txt","w+");
		else if (lp.langue == anglais)
			f= fopen("saveProbaEN.txt","w+");
		else if (lp.langue == italien)
			f= fopen("saveProbaIT.txt","w+");
		else if (lp.langue == allemand)
			f= fopen("saveProbaDE.txt","w+");
	}while(f==NULL);

	fprintf(f,"%d\n",lp.nblettreTotal);
	ElementLangue *l1 = lp->l;
	ElementLangueBis *l;
	for (i=0; i<26; i++)
	{
		fprintf(f,"%c : %d ",l1->lettre, l1->nbOccur);
		l = l1->lettreSuivante;
		for (i=0; i<26; i++)
		{
			fprintf(f,"%c : %d ",l->lettre, l->nbOccur);
		}
		l1 = l1.suivant;
		fprintf(f,"\n",l->lettre, l->nbOccur);
	}
	fclose(f);
}
Langue searchLangue(char *mot,float **probaLangue)
{
    char lettre[26] = {0};
    float prob[26];
    int i = 0;
    while(mot[i] != NULL)
    {
        lettre[mot[i]]++;
        i++;
    }
    calculProbaInternal(lettre, i, prob);

    return comparProba(prob,probaLangue);
}

