#include "analyse.h"


int main(int argc, char *argv[])
{

	
	
	FILE *F,*G,*H;
	char fic1[256],fic2[256],fic3[256];
	

	//LECTURES DE FICHIERS 
	sprintf(fic1,"fichiers/mces.result");

	F = fopen(fic1,"r");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic1);
		exit(3);
	}
	int **M1 = lecture_fichier(F);
	fclose(F);
	

	sprintf(fic2,"fichiers/cycles.result");

	G = fopen(fic2,"r");
	if( G == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic2);
		exit(2);
	}
	int **M2 = lecture_fichier(G);
	fclose(G);

	sprintf(fic3,"fichiers/tanimoto.result");

	H = fopen(fic3,"r");
	if( H == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic3);
		exit(4);
	}
	int **M3 = lecture_fichier(H);
	fclose(H);

	

	int *molecules = lecture_molecules (MOLECULES);
	

	int **MC1 = matrice_conf(M1,M2,molecules, 1);
	int **MC2 = matrice_conf(M3,M2,molecules, 2);
	int **MC3 = matrice_conf(M1,M3,molecules, 3);

	initialisation_fichier_latex();
	ecriture_matrice(MC1,1);
	ecriture_matrice(MC2,2);
	ecriture_matrice(MC3,3);
	fermeture_fichier_latex();



	liberer_matrice(M1,MOLECULES);
	liberer_matrice(M2,MOLECULES);
	liberer_matrice(M3,MOLECULES);
	liberer_matrice(MC1, NBVAL +1);
	liberer_matrice(MC2, NBVAL +1);
	liberer_matrice(MC3, NBVAL +1);
	free(molecules);

	exit(0);
}

