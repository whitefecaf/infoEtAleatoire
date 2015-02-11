/*
 * probaLangue.c
 *
 *  Created on: 24 janv. 2015
 *      Author: whitefecaf
 */
#include "probaLangue.h"

typedef struct ElementProbaBis ElementProbaBis;
struct ElementProbaBis
{
	char lettre;
	float proba;
	ElementProbaBis *suivant;
};

typedef struct ElementProba ElementProba;
struct ElementProba
{
	char lettre;
	ElementProbaBis *diffprobaFR;//valeur absolue de la difference entre les proba de la langue et celle du mot
	ElementProbaBis *diffprobaEN;
	ElementProbaBis *diffprobaIT;
	ElementProbaBis *diffprobaDE;
	ElementProba *suivant;
};

ElementProba *initStructProba(ElementProba *lp)
{
	int i, j;
	ElementProba *elem1;
	ElementProbaBis * elem2;
	ElementProba *elem;
	ElementProbaBis *elembis;
	elem1 = malloc(sizeof(ElementProba));
	elem2 = malloc(sizeof(ElementProbaBis));
	elem = malloc(sizeof(ElementProba));
	elembis = malloc(sizeof(ElementProbaBis));

	//1er élément
	elem->lettre = 'a';
	lp = elem;




	//1er élément de lettre suivante pour l'instance du premier élément
	elembis->lettre = 'a';
	lp->diffprobaFR = elembis;
	for(i='b'; i <= 'z'; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = i;
		elembis->suivant = elem2;
		elembis = elem2;
	}
	elembis->suivant = NULL;

	elembis = malloc(sizeof(ElementLangueBis));
	elembis->lettre = 'a';
	lp->diffprobaEN = elembis;
	for(i='b'; i <= 'z'; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = i;
		elembis->suivant = elem2;
		elembis = elem2;
	}
	elembis->suivant = NULL;

	elembis = malloc(sizeof(ElementLangueBis));
	elembis->lettre = 'a';
	lp->diffprobaIT = elembis;
	for(i='b'; i <= 'z'; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = i;
		elembis->suivant = elem2;
		elembis = elem2;
	}
	elembis->suivant = NULL;

	elembis = malloc(sizeof(ElementLangueBis));
	elembis->lettre = 'a';
	lp->diffprobaDE = elembis;
	for(i='b'; i <= 'z'; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = i;
		elembis->suivant = elem2;
		elembis = elem2;
	}
	elembis->suivant = NULL;
	//création du dictionnaire (1er élément deja créer)
	for(i='b'; i <= 'z'; i++)
	{
		elem1 = malloc(sizeof(ElementLangue));
		elem1->lettre = i;
		elem->suivant = elem1;
		elem = elem1;
		//1er élément de lettre suivante pour l'instance en cours
		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		lp->diffprobaFR = elembis;
		for(j='b'; j <= 'z'; j++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = j;
			elembis->suivant = elem2;
			elembis = elem2;
		}
		elembis->suivant = NULL;

		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		lp->diffprobaEN = elembis;
		for(j='b'; j <= 'z'; j++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = j;
			elembis->suivant = elem2;
			elembis = elem2;
		}
		elembis->suivant = NULL;

		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		lp->diffprobaIT = elembis;
		for(j='b'; j <= 'z'; j++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = j;
			elembis->suivant = elem2;
			elembis = elem2;
		}
		elembis->suivant = NULL;

		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		lp->diffprobaDE = elembis;
		for(j='b'; j <= 'z'; j++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = j;
			elembis->suivant = elem2;
			elembis = elem2;
		}
		elembis->suivant = NULL;
	}
	elem->suivant = NULL;

	return lp;
}

void increment(LangueProb *lp, char lettre)
{
	lp->nblettreTotal = (lp->nblettreTotal) + 1;
	ElementLangue *elem = lp->l;
	while((elem->lettre) != lettre)
	{
		elem = elem->suivant;
	}
	elem->nbOccur = (elem->nbOccur) + 1;
}

void incrementation(LangueProb *lp, char lettre, char lettrePrec)
{

	increment(lp, lettre);
	lp->nblettreTotal = (lp->nblettreTotal) + 1;
	ElementLangue *elem = lp->l;
	while(elem->lettre != lettrePrec)
		elem = elem->suivant;
	elem->nbOccur = (elem->nbOccur) + 1;
	ElementLangueBis *l = elem->lettreSuivante;
	while(l->lettre != lettre)
	{
		l = l->suivant;
	}
	l->nbOccur = (l->nbOccur) + 1;
}

void calculProba(LangueProb *lp)
{
	ElementLangue *l = lp->l;
	ElementLangueBis *li;
	while(l->suivant != NULL)
	{
		li = l->lettreSuivante;
		while(li->suivant != NULL)
		{
			li->proba = (float)((l->nbOccur)+ 1) /(float)((li->nbOccur) + 26);
			li = li->suivant;
		}
		l = l->suivant;
	}
}

void calculProbaInternal(ElementLangue *l)
{
	ElementLangueBis *li;
	while(l->suivant != NULL)
	{
		li = l->lettreSuivante;
		while(li->suivant != NULL)
		{
			li->proba = (float)((l->nbOccur)+ 1) /(float)((li->nbOccur) + 26);
			li = li->suivant;
		}
		l = l->suivant;
	}
}

Langue comparProba(ElementLangue *l,LangueProb *lp)
{
	int i =0;
	float totalFR = 0, totalEN = 0, totalIT = 0, totalDE = 0;
	ElementProba *prob = malloc(sizeof(ElementProba));
	ElementProbaBis *probBisFR, *probBisEN, *probBisIT, *probBisDE;
	printf("before initStructProba\n");
	prob = initStructProba(prob);
	printf("after initStructProba\n");
	ElementLangue *l0,*l1,*l2,*l3;
	ElementLangueBis *lb0, *lb1,*lb2,*lb3,*lbMot;
	l0 = lp[0].l;
	l1 = lp[1].l;
	l2 = lp[2].l;
	l3 = lp[3].l;

	while(l0 != NULL)//l0,l1,l2 et l3 ont la même taille
	{

		probBisFR = prob->diffprobaFR;
		probBisEN = prob->diffprobaEN;
		probBisIT = prob->diffprobaIT;
		probBisDE = prob->diffprobaDE;
		lb0 = l0->lettreSuivante;
		lb1 = l1->lettreSuivante;
		lb2 = l2->lettreSuivante;
		lb3 = l3->lettreSuivante;
		lbMot = l->lettreSuivante;
		while(lb0 != NULL) // lb0 ... ont la meme taille(de meme que l0)
		{
			i++;
			probBisFR->proba = abs(lb0->proba - lbMot->proba);
			probBisEN->proba = abs(lb1->proba - lbMot->proba);
			probBisIT->proba = abs(lb2->proba - lbMot->proba);
			probBisDE->proba = abs(lb3->proba - lbMot->proba);
			totalFR += probBisFR->proba;
			totalEN += probBisEN->proba;
			totalIT += probBisIT->proba;
			totalDE += probBisDE->proba;

			lb0 = lb0->suivant;
			lb1 = lb1->suivant;
			lb2 = lb2->suivant;
			lb3 = lb3->suivant;
		}
		l = l->suivant;
		l0 = l0->suivant;
		l1 = l1->suivant;
		l2 = l2->suivant;
		l3 = l3->suivant;
	}
	if(totalFR < totalIT && totalFR < totalEN && totalFR < totalDE)
	{
		return francais;
	}else if(totalIT < totalFR && totalIT < totalEN && totalIT < totalDE)
	{
		return italien;
	}else if(totalEN < totalFR && totalEN < totalIT && totalEN < totalDE)
	{
		return anglais ;
	}else if(totalDE < totalFR && totalDE < totalEN && totalDE < totalIT)
	{
		return allemand ;
	}
	return francais;//ne sert a rien juste pour les warning
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
					lettrePrec = ' ';
					break;
				default :
					if(lettrePrec == ' ')
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
int initLangueProb( LangueProb *lp, Langue langue)
{
	FILE *f;
	int i,j;


	///////////////////////////////////////definition de lp////////////////////////////////////////////////


	ElementLangue *elem1;
	ElementLangueBis * elem2;
	ElementLangue *elem;
	ElementLangueBis *elembis;
	lp->langue = langue;
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
	for(i='b'; i <= 'z'; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = i;
		elembis->suivant = elem2;
		elembis->nbOccur = 0;
		elembis = elem2;
	}
	elembis->suivant = NULL;
	//création du dictionnaire (1er élément deja créer)
	for(i='b'; i <= 'z'; i++)
	{
		elem1 = malloc(sizeof(ElementLangue));
		elem1->lettre = i;
		elem1->nbOccur = 0;
		elem->suivant = elem1;
		elem = elem1;
		//1er élément de lettre suivante pour l'instance en cours
		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		elembis->nbOccur = 0;
		elem->lettreSuivante = elembis;
		for(j='b'; j <= 'z'; j++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = j;
			elembis->suivant = elem2;
			elembis->nbOccur = 0;
			elembis = elem2;
		}
		elembis->suivant = NULL;
	}
	elem->suivant = NULL;

	////////////////////////////////////////////debut remplissage de lp si des fichiers sont sauvegarder ////////////////////////////////////////////////////////:

	ElementLangue *li = lp->l;
	ElementLangueBis *l;

	if (lp->langue == francais && access("saveProbaFR.txt",F_OK) == 0)
	{
		f = fopen("saveProbaFR.txt","r");
		fscanf(f,"%d\n",&lp->nblettreTotal);
		while(li != NULL)
		{
			fscanf(f,"%c : %d ",&(li->lettre), &(li->nbOccur));
			l = li->lettreSuivante;
			while(l != NULL)
			{
				fscanf(f,"%c : %d ",&(l->lettre), &(l->nbOccur));
				l = l->suivant;
			}
			li = li->suivant;
			fprintf(f,"\n");
		}
		fclose(f);
		return 0;
	}
	else if (lp->langue == anglais && access("saveProbaEN.txt",F_OK) == 0)
	{
		f = fopen("saveProbaEN.txt","r");
		fscanf(f,"%d\n",&lp->nblettreTotal);

		while(li != NULL)
		{
			fscanf(f,"%c : %d ",&(li->lettre), &(li->nbOccur));
			l = li->lettreSuivante;
			while(l != NULL)
			{
				fscanf(f,"%c : %d ",&(l->lettre), &(l->nbOccur));
				l = l->suivant;
			}
			li = li->suivant;
			fprintf(f,"\n");
		}
		fclose(f);
		return 0;
	}
	else if (lp->langue == italien && access("saveProbaIT.txt",F_OK) == 0)
	{
		f = fopen("saveProbaIT.txt","r");
		fscanf(f,"%d\n",&lp->nblettreTotal);
		while(li != NULL)
		{
			fscanf(f,"%c : %d ",&(li->lettre), &(li->nbOccur));
			l = li->lettreSuivante;
			while(l != NULL)
			{
				fscanf(f,"%c : %d ",&(l->lettre), &(l->nbOccur));
				l = l->suivant;
			}
			li = li->suivant;
			fprintf(f,"\n");
		}
		fclose(f);
		return 0;
	}
	else if (lp->langue == allemand && access("saveProbaDE.txt",F_OK) == 0)
	{
		f = fopen("saveProbaDE.txt","r");
		fscanf(f,"%d\n",&lp->nblettreTotal);
		while(li != NULL)
		{
			fscanf(f,"%c : %d ",&(li->lettre), &(li->nbOccur));
			l = li->lettreSuivante;
			while(l != NULL)
			{
				fscanf(f,"%c : %d ",&(l->lettre), &(l->nbOccur));
				l = l->suivant;
			}
			li = li->suivant;
			fprintf(f,"\n");
		}
		fclose(f);
		return 0;
	}else
	{
		printf("else");
		return 1;
	}
}
void saveProba(LangueProb lp)
{
	FILE *f;
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
	ElementLangue *l1 = lp.l;
	ElementLangueBis *l;
	while(l1 != NULL)
	{
		fprintf(f,"%c : %d ",l1->lettre, l1->nbOccur);
		l = l1->lettreSuivante;
		while(l != NULL)
		{
			fprintf(f,"%c : %d ",l->lettre, l->nbOccur);
			l = l->suivant;
		}
		l1 = l1->suivant;
		fprintf(f,"\n");
	}
	fclose(f);
}

Langue searchLangue(char *mot,LangueProb *lp, int n)
{

	int i, j;
	ElementLangue *racine = malloc(sizeof(ElementLangue));
	ElementLangue *elem1 =malloc(sizeof(ElementLangue));
	ElementLangueBis * elem2;
	ElementLangue *elem;
	ElementLangueBis *elembis;



	while(mot[i] < n)
	{
		if (i == 0)
		{
			racine->lettre = mot[i];
			racine->nbOccur = 1;
		}else
		{
			while((elem->lettre) != mot[i])
			{
				elem = elem->suivant;
			}
			elem->nbOccur = (elem->nbOccur) + 1;
			elem = racine;
			while(elem->lettre != mot[i-1])
				elem = elem->suivant;
			elem->nbOccur = (elem->nbOccur) + 1;
			ElementLangueBis *l = elem->lettreSuivante;
			while(l->lettre != mot[i])
			{
				l = l->suivant;
			}
			l->nbOccur = (l->nbOccur) + 1;
		}
		i++;
	}

	/*
	int i, j;
	ElementLangue *racine;
	ElementLangue *elem1;
	ElementLangueBis * elem2;
	ElementLangue *elem;
	ElementLangueBis *elembis;
	elem1 = malloc(sizeof(ElementLangue));
	elem2 = malloc(sizeof(ElementLangueBis));
	elem = malloc(sizeof(ElementLangue));
	elembis = malloc(sizeof(ElementLangueBis));


	//1er élément
	elem->lettre = 'a';
	elem->nbOccur = 0;
	racine = elem;


	//1er élément de lettre suivante pour l'instance du premier élément
	elembis->lettre = 'a';
	elembis->nbOccur = 0;
	racine->lettreSuivante = elembis;
	for(i='b'; i <= 'z'; i++)
	{
		elem2 = malloc(sizeof(ElementLangue));
		elem2->lettre = i;
		elembis->suivant = elem2;
		elembis->nbOccur = 0;
		elembis = elem2;
	}
	elembis->suivant = NULL;
	//création du dictionnaire (1er élément deja créer)
	for(i='b'; i <= 'z'; i++)
	{
		elem1 = malloc(sizeof(ElementLangue));
		elem1->lettre = i;
		elem1->nbOccur = 0;
		elem->suivant = elem1;
		elem = elem1;
		//1er élément de lettre suivante pour l'instance en cours
		elembis = malloc(sizeof(ElementLangueBis));
		elembis->lettre = 'a';
		elembis->nbOccur = 0;
		elem->lettreSuivante = elembis;
		for(j='b'; j <= 'z'; j++)
		{
			elem2 = malloc(sizeof(ElementLangue));
			elem2->lettre = j;
			elembis->suivant = elem2;
			elembis->nbOccur = 0;
			elembis = elem2;
		}
		elembis->suivant = NULL;
	}
	elem->suivant = NULL;

	elem = racine;
	i = 0;
	while(mot[i] < n)
	{
		if (i == 0)
		{
			while((elem->lettre) != mot[i])
			{
				elem = elem->suivant;
			}
			elem->nbOccur = (elem->nbOccur) + 1;
		}else
		{
			while((elem->lettre) != mot[i])
			{
				elem = elem->suivant;
			}
			elem->nbOccur = (elem->nbOccur) + 1;
			elem = racine;
			while(elem->lettre != mot[i-1])
				elem = elem->suivant;
			elem->nbOccur = (elem->nbOccur) + 1;
			ElementLangueBis *l = elem->lettreSuivante;
			while(l->lettre != mot[i])
			{
				l = l->suivant;
			}
			l->nbOccur = (l->nbOccur) + 1;
		}
		i++;
	}
	calculProbaInternal(racine);
	*/
	return comparProba(racine,lp);
}
