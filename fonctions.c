#include "fonctions.h"



int min (int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int **matrice_confusion(FILE *F, FILE *G,int *molecules, int taille)
{

	int **matrice = malloc( (NBVAL + 2) * sizeof(int *)); // +2 dans le cas de 1.0 et de similarite non calcule

	int i,j;
	for ( i = 0; i < NBVAL + 2; i++ )
		matrice[i] = malloc( (NBVAL +1 ) * sizeof(int));


	//initialisation de la matrice
	for ( i = 0; i < NBVAL + 2; i++ )
	{
		for (  j= 0; j < NBVAL +1; j++ )
			matrice[i][j] = 0;
	}

	//lecture des fichiers 

	float sim1, sim2;
	int pos1,pos2;// nb_couples = ((taille)*(taille + 1))/ 2;
	//int nb_couples = 0;
	for( i = 0; i < taille ; i++)
	{
		for(j = 0; j < i; j++)
		{
			fscanf(F,"%f", &sim1);
			fscanf(G,"%f", &sim2);
			//nb_couples++;
			pos1 = (int)(sim1 * NBVAL);
			pos2 = (int)(sim2 * NBVAL);


			if(pos1 < 0)
				pos1 = NBVAL +1;
			if(pos2 < 0)
				pos2 = NBVAL +1;
			//printf("%f %f %d %d \n", sim1,sim2, pos1,pos2);
			matrice[pos1][pos2]++;
			ecrire_resultat(molecules, pos1,pos2, sim1,sim2 ,i,j);

		}	
		
	}
	//printf("nb nb_couples effectifs %d et attendu %d\n",nb_couples, ((taille)*(taille - 1))/ 2 );
	//affiche_matrice(matrice);
	return matrice;	
}
void ecrire_resultat(int *mols, int pos1, int pos2,float sim1, float sim2, int i,int j)
{
	FILE *F;
	char fic1[256];



	sprintf(fic1,"Dossier/TC_GC_%d_%d.data", pos1,pos2);

	F = fopen(fic1,"a");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic1);
		exit(6);
	}

	fprintf(F, "%6d \t %6d \t %.2f \t %.2f\n", mols[i], mols[j],sim1,sim2);

	fclose(F);
}
void liberer_matrice(int ** matrice)
{
	int i;
	for ( i = 0; i < NBVAL + 2; i++ )
		free(matrice[i]);
	free(matrice);


}

void affiche_matrice(int ** matrice)
{
	int i,j;
	for ( i = 0; i < NBVAL + 2; i++ )
	{
		for (  j= 0; j < NBVAL +1; j++ )
			printf("%5d ",matrice[i][j]);
		printf("\n");
	}



}

void ecrire_matrice_confusion(int ** matrice)
{
	
	int i,j;

	FILE *F;
	char fic1[256];



	sprintf(fic1,"matrice_confusion_TC_GC.data");

	F = fopen(fic1,"w");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic1);
		exit(5);
	}

	for ( i = 0; i < NBVAL + 2; i++ )
	{
		for (  j= 0; j < NBVAL +1; j++ )
			fprintf(F,"%5d ",matrice[i][j]);
		fprintf(F,"\n");
	}

	fclose(F);



}

int * lecture_molecules(int taille)
{
	int *mol = malloc(taille * sizeof(int));
	FILE *F;
	char fic1[256];



	sprintf(fic1,"fichiers/molecules.data");

	F = fopen(fic1,"r");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic1);
		exit(5);
	}

	int i;
	int numero;
	for( i = 0; i < taille; i++)
	{
		fscanf(F, "%d",&numero);
		mol[i] = numero;
		//printf("%d\n",mol[i] );
	}


	fclose(F);

	return mol;
}

