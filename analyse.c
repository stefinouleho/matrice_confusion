#include "analyse.h"


int main(int argc, char *argv[])
{

	
	
	FILE *F,*G;
	char fic1[256],fic2[256];



	sprintf(fic1,"fichiers/mces.result");

	F = fopen(fic1,"r");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic1);
		exit(3);
	}


	sprintf(fic2,"fichiers/tanimoto.result");

	G = fopen(fic2,"r");
	if( G == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic2);
		exit(2);
	}

	int taille1, taille2;

	fscanf(F,"%d",&taille1);
	fscanf(G,"%d",&taille2);
	int *molecules = lecture_molecules (min(taille1,taille2));
	int **MC = matrice_confusion(F,G,molecules, min(taille1,taille2));


	fclose(G);
	fclose(F);

	ecrire_matrice_confusion(MC);

	liberer_matrice(MC);
	free(molecules);

	exit(0);
}

