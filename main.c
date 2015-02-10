/*
 * main.c
 *
 *  Created on: 24 janv. 2015
 *      Author: whitefecaf
 */

#include "probaLangue.h"

int main (int argc, char *argv[])
{

    /*les Langues sont francaise, anglaise, italienne et allemande
    dans les tableau de LangueProb et probaLangue
    - 0 designe le francais
    - 1 l'anglais
    - 2 l'iatalien
    - 3 l'allemand
    */
	int i;
	LangueProb *allLangue;
	allLangue = malloc(4 * sizeof(LangueProb));

	float **probaLangue;
	probaLangue = malloc(4 * sizeof(float*));
	for(i=0; i<4; i++)
    {
        probaLangue[i] = malloc(26 * sizeof(float));
    }
	creationBaseProba(&(allLangue[0]),"french.txt", initLangueProb(&allLangue[0],francais));
	creationBaseProba(&allLangue[1],"english.txt", initLangueProb(&allLangue[1],anglais));
	creationBaseProba(&allLangue[2],"italian.txt", initLangueProb(&allLangue[2],italien));
	creationBaseProba(&allLangue[3],"dutch.txt", initLangueProb(&allLangue[3],allemand));
	calculProba(&allLangue[0], probaLangue[0]);
	calculProba(&allLangue[1], probaLangue[1]);
	calculProba(&allLangue[2], probaLangue[2]);
	calculProba(&allLangue[3], probaLangue[3]);

	char *mot = "pomme";

    Langue l = searchLangue (mot, probaLangue);











/*
	saveProba(allLangue[0]);
	saveProba(allLangue[1]);
	saveProba(allLangue[2]);
	saveProba(allLangue[3]);
*/
	return 0;
}
