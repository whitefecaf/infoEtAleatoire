/*
 * main.c
 *
 *  Created on: 24 janv. 2015
 *      Author: whitefecaf
 */

#include "probaLangue.h"
#include <assert.h>

int main (int argc, char *argv[])
{

  /*les Langues sont francaise, anglaise, italienne et allemande
    dans les tableau de LangueProb et probaLangue
    - 0 designe le francais
    - 1 l'anglais
    - 2 l'iatalien
    - 3 l'allemand
  */

  LangueProb *allLangue;
  allLangue = malloc(4 * sizeof(LangueProb));


  creationBaseProba(&(allLangue[0]),"french.txt", initLangueProb(&allLangue[0],francais));
  creationBaseProba(&allLangue[1],"english.txt", initLangueProb(&allLangue[1],anglais));
  creationBaseProba(&allLangue[2],"italian.txt", initLangueProb(&allLangue[2],italien));
  creationBaseProba(&allLangue[3],"dutch.txt", initLangueProb(&allLangue[3],allemand));
  calculProba(&allLangue[0]);
  calculProba(&allLangue[1]);
  calculProba(&allLangue[2]);
  calculProba(&allLangue[3]);

  int spacePassed = 0;
  int line = 0, lineFR = 0, lineEN = 0, lineIT = 0, lineDE = 0;
  int resultGood = 0, goodFR = 0, goodEN = 0, goodIT = 0, goodDE = 0;
  char *lg = malloc(2);;
  char *mot;
  char c;
  int longueurMot = 0;
  FILE* f = fopen("test.txt","r");
  FILE* f1 = fopen("result.txt","w+");
  assert(f!=NULL);
  assert (f1 != NULL);




  while((c=fgetc(f)) != EOF)
    {

      if (c == '\n')
	{
	  spacePassed = 0;
	 
	  Langue l = searchLangue (mot,allLangue, longueurMot);
	  printf("%s\n",lg);
	  if(l == francais)
	    {
	      fprintf(f1,"%s FR->%s -- %d\n", mot, lg, longueurMot);
	      lineFR++;
	      if(lg[1] == 'F')
		{
		  goodFR++;
		  resultGood++;
		}
	    }
	  else if(l == anglais)
	    {
	      fprintf(f1,"%s EN->%s -- %d\n", mot, lg, longueurMot);
	      lineEN++;
	      if(lg[1] == 'E')
		{
		  goodEN++;
		  resultGood++;
		}
	    }
	  else if (l == italien)
	    {
	      fprintf(f1,"%s IT->%s -- %d\n", mot, lg, longueurMot);
	      lineIT++;
	      if(lg[1] == 'I')
		{
		  goodIT++;
		  resultGood++;
		}
	    }
	  else
	    {
	      fprintf(f1,"%s GR->%s -- %d\n", mot, lg, longueurMot);
	      lineDE++;
	      if(lg[1] == 'G')
		{
		  goodDE++;
		  resultGood++;
		}
	    }
	  mot = NULL;
	  lg = NULL;
	  longueurMot = 0;
	  lg = malloc (2);
	  line++;
	}
      else
	{
	  if (c == ' ')
	    spacePassed = 1;

	  if (spacePassed == 0)
	    {
	      if (longueurMot == 0)
		{		  
		  mot = malloc(1);
		  mot[0] = c;
		}
	      else
		{
		  mot = realloc(mot, longueurMot+1);
		  mot[longueurMot] = c;
		}
	      longueurMot++;
	    }
	  else
	    {
	      lg[spacePassed -1] = c;
	      spacePassed++;
	    }
		

	}
    }
  printf("%d, %d -> %f\n",resultGood, line, (float)resultGood*100/(float)line);
  printf("%d, %d -> %f\n",goodFR, lineFR, (float)goodFR*100/(float)lineFR);
  printf("%d, %d -> %f\n",goodEN, lineEN, (float)goodEN*100/(float)lineEN);
  printf("%d, %d -> %f\n",goodIT, lineIT, (float)goodIT*100/(float)lineIT);
  printf("%d, %d -> %f\n",goodDE, lineDE, (float)goodDE*100/(float)lineDE);
    
  saveProba(allLangue[0]);
  saveProba(allLangue[1]);
  saveProba(allLangue[2]);
  saveProba(allLangue[3]);

  return 0;
}
