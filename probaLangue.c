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
	while(l != NULL)
	{
		li = l->lettreSuivante;
		while(li != NULL)
		{
			li->proba = (float)((l->nbOccur)+ 1) /(float)((li->nbOccur) + 26);
			li = li->suivant;
		}
		l = l->suivant;
	}
}

// renvoie la langue qui qui a la proba la plus proche de l
Langue compareProba(ElementLangue* l,LangueProb* lp)
{
  float diff[4] = {0};
  while(L != null)
    {
      diff[0] = min(diff[0], compare_language_probability(l, lp[0]));
      diff[1] = compare_language_probability(l, lp[1]);
      diff[2] = compare_language_probability(l, lp[2]);
      diff[3] = compare_language_probability(l, lp[3]);
    }
}

float get_language_probability(ElementLangue l, LangueProb lp)
{

}

Langue comparProba(ElementLangue *l,LangueProb *lp)
{
	float totalFR = 0, totalEN = 0, totalIT = 0, totalDE = 0;
	ElementProba *prob = malloc(sizeof(ElementProba));
	prob = initStructProba(prob);
	ElementLangue *l0,*l1,*l2,*l3;
	ElementLangueBis *lb0, *lb1,*lb2,*lb3,*lbMot;
	l0 = lp[0].l;
	l1 = lp[1].l;
	l2 = lp[2].l;
	l3 = lp[3].l;

	while(l != NULL)//l0,l1,l2 et l3 ont la même taille
	{
	  while (l0->lettre != l->lettre)
	    {
	      l0 = l0->suivant;
	      l1 = l1->suivant;
	      l2 = l2->suivant;
	      l3 = l3->suivant;
	    }
	  //l0->lettre = l->lettre
	  lbMot = l->lettreSuivante;
	  while (lbMot != NULL)
	    {

	      lb0 = l0->lettreSuivante;
	      lb1 = l1->lettreSuivante;
	      lb2 = l2->lettreSuivante;
	      lb3 = l3->lettreSuivante;
	      while (lb0->lettre != lbMot->lettre)
		{
		  lb0 = lb0->suivant;
		  lb1 = lb1->suivant;
		  lb2 = lb2->suivant;
		  lb3 = lb3->suivant;
		}
	      //lb0->lettre = lbMot->lettre
	      totalFR += (lb0->proba - lbMot->proba);
	      totalEN += (lb1->proba - lbMot->proba);
	      totalIT += (lb2->proba - lbMot->proba);
	      totalDE += (lb3->proba - lbMot->proba);
	    }
	  l = l->suivant;
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

void  insereTrier(ElementLangue **racine, char letter)
{
  ElementLangue *elemInser = malloc(sizeof(ElementLangue));
  elemInser->lettre = letter;
  elemInser->lettreSuivante = NULL;
  elemInser->nbOccur = 1;

  if (*racine == NULL)
    {
      *racine = elemInser;
      return;
    }
  ElementLangue *elem = (*racine)->suivant;
  ElementLangue *elemPrec = *racine;
     
  if ((*racine)->lettre > letter)
    {
      elemInser->suivant = *racine;
      *racine = elemInser;
    }
  else
    {
      while(elem != NULL && elem->lettre < letter)
	{
	  elem = elem->suivant;
	  elemPrec = elemPrec->suivant;
	}
      elemPrec->suivant = elemInser;
      elemInser->suivant = elem;
    }
}

void  insereTrierLettre(ElementLangueBis **racine, char letter)
{

  ElementLangueBis *elemInser = malloc(sizeof(ElementLangue));
  elemInser->lettre = letter;
  elemInser->nbOccur = 1;
  if (*racine != NULL)
    {
      ElementLangueBis *elem = (*racine)->suivant;
      ElementLangueBis *elemPrec = *racine;
      if ((*racine)->lettre > letter)
	{
	  elemInser->suivant = *racine;
	  *racine = elemInser;
	}
      else
	{
	  while(elem != NULL && elem->lettre < letter)
	    {
	      elem = elem->suivant;
	      elemPrec = elemPrec->suivant;
	    }
	  elemPrec->suivant = elemInser;
	  elemInser->suivant = elem;
	}
    }else
    {
      *racine = elemInser;
    }
}

ElementLangue* get_EL_from_word(char* word, int n)
{
  
  int i = 0, j = 0;
  ElementLangue *racine = malloc(sizeof(ElementLangue));
  ElementLangue *elem;
 

  while(i < n)
    {
      elem = racine;
      if (i == 0)
	{
	  elem->lettre = mot[i];
	  elem->nbOccur = 1;
	  elem->suivant = NULL;
	}
      else
	{
	   j = 0;
	  //prise compte du caractere imise dans 
	  while (elem != NULL && elem->lettre < mot[i])
	    {
	      elem = elem->suivant;
	    }
	  if(elem == NULL || mot[i] > elem->lettre || mot[i] < elem->lettre)
	    {
	      insereTrier(&racine, mot[i]);
	     
	    }
	  else
	    {
	      elem->nbOccur += 1;
	    }
	   
	  //mise dans la deuxieme liste du carctere i
	  elem = racine;
	 
	  while (elem->lettre != mot[i-1])
	    {
	      j++;
	      elem = elem->suivant;
	      
	    }
	  ElementLangueBis *l = elem->lettreSuivante;
	  ElementLangueBis *l2 = l;
	  while(l2 != NULL && l2->lettre < mot[i])
	    {
	      l2 = l2->suivant;
	    }
	  if(l2 == NULL || mot[i] > l2->lettre)
	    {
	      insereTrierLettre(&l, mot[i]);
	    }
	  else
	    {
	      l2->nbOccur += 1;
	    }
	}
      i++;
    }
  calculProbaInternal(racine);
  return racine;
}

Langue searchLangue(char *mot,LangueProb *lp, int n)
{
  ElementLangue *racine = get_EL_from_world(mot,n); 
  return comparProba(racine,lp);
}
