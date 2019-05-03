#include "fonctions.h"


void liberer_matrice(int ** matrice, int taille)
{
	int i;
	for ( i = 0; i < taille; i++ )
		free(matrice[i]);
	free(matrice);


}
void affiche_matrice(int ** matrice, int taille)
{
	int i,j;
	printf("affichage de la matrice\n");
	for ( i = 0; i < taille ; i++ )
	{
		for (  j= 0; j < taille ; j++ )
			printf("%5d ",matrice[i][j]);
		printf("\n");
	}
	printf("fin de l'affichage de la matrice\n");



}

int ** lecture_fichier(FILE *F)
{
	int **matrice = malloc( MOLECULES * sizeof(int *));
	int i,j;
	float sim;
	for ( i = 0; i < MOLECULES; i++ )
		matrice[i] = calloc( MOLECULES, sizeof(int));
	
	for( i = 0; i < MOLECULES -1 ; i++)
	{
		for(j = 0; j < i + 1 ; j++)
		{
			fscanf(F,"%f",&sim);
			matrice[i + 1][j] = (int)(sim *10);
			matrice[j][i + 1] = (int)(sim *10);
		}
	}
	//affiche_matrice(matrice, MOLECULES);
	return matrice;
}


void ecrire_resultat(int *mols,int cas, int pos1, int pos2,int i, int j)
{
	FILE *F;
	char fic1[256];

	if( cas ==1)
		sprintf(fic1,"Dossier/GM_GC/GM_GC_%d_%d.data", pos1,pos2);
	if( cas ==2)
		sprintf(fic1,"Dossier/TC_GC/TC_GC_%d_%d.data", pos1,pos2);
	if( cas ==3)
		sprintf(fic1,"Dossier/GM_TC/GM_TC_%d_%d.data", pos1,pos2);
	F = fopen(fic1,"a");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot open the file %s\n", fic1);
		exit(6);
	}

	fprintf(F, "%6d \t %6d\n", mols[i], mols[j]);

	fclose(F);
}

int ** matrice_conf(int **M1, int **M2, int *mols, int cas)
{

	int **matrice = malloc( (NBVAL + 1) * sizeof(int *)); 
	int i,j;
	for ( i = 0; i < NBVAL + 1; i++ )
		matrice[i] = calloc( NBVAL + 1 , sizeof(int));

	int nb_couples_effectif = 0;

	for( i = 0; i < MOLECULES -1 ; i++)
	{
		for(j = 0; j < i + 1 ; j++)
		{
			if(M1[i + 1][j] >= 0 && M2[i + 1][j] >= 0)
			{
				//printf("%d %d \n",M1[i + 1][j],M2[i + 1][j]);
				nb_couples_effectif++;
				matrice[M1[i + 1][j]][M2[i + 1][j]]++;
				ecrire_resultat(mols, cas,M1[i + 1][j],M2[i + 1][j],i,j);
			}
		}
	}
	//printf("nb couples effectif  : %d/%d et nbre de couples non effectif : %d/%d\n\n\n",nb_couples_effectif,(((MOLECULES -1) * (MOLECULES))/2),(((MOLECULES -1) * (MOLECULES))/2) - nb_couples_effectif,(((MOLECULES -1) * (MOLECULES))/2) );
	//affiche_matrice(matrice, NBVAL + 1);
	return matrice;
}





void ecrire_matrice_confusion(int ** matrice)
{
	
	int i,j;

	FILE *F;
	char fic1[256];



	sprintf(fic1,"matrice_confusion.data");

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


void initialisation_fichier_latex()
{

	char fichier[256];
	sprintf(fichier,"fichiers/tableau.tex");

	FILE *F = fopen(fichier,"w");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot write the file %s\n", fichier);
		exit(4);
	}



	fprintf(F, "\\documentclass[a4paper]{article}\n");

	fprintf(F, "\\usepackage[utf8]{inputenc}\n");
	fprintf(F, "\\usepackage[french]{babel}\n");
	fprintf(F, "\\usepackage[T1]{fontenc}\n");

	fprintf(F, "\\usepackage[left=1cm,right=1cm,top=2cm,bottom=2cm]{geometry}\n");


	fprintf(F, "\\usepackage{graphicx}\n");
	fprintf(F, "\\usepackage[colorlinks=true,linkcolor=blue]{hyperref}\n");
	fprintf(F, "\\usepackage{longtable}\n");
	fprintf(F, "\\usepackage{slashbox,pict2e}\n");
	 
	fprintf(F, "\\begin{document}");


	


	fclose(F);
}



void ecriture_matrice ( int **MC, int cas)
{
	char fichier[256];
	sprintf(fichier,"fichiers/tableau.tex");

	FILE *F = fopen(fichier,"a");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot write the file %s\n", fichier);
		exit(4);
	}

	int i,j;
	fprintf(F, "\\begin{center}\n");

	fprintf(F, "\\vspace*{5mm}\n");

	fprintf(F, "\\begin{longtable}{|c");
	
	for (i = 0; i <= NBVAL; i++)
	{
		fprintf(F, "|c");
	}

	fprintf(F, "|}\n \\hline \n");
	if( cas == 1)
		fprintf(F, "\\backslashbox{\\textbf{GM}}{\\textbf{GC}} ");
	if( cas == 2)
		fprintf(F, "\\backslashbox{\\textbf{TC}}{\\textbf{GC}} ");
	if( cas == 3)
		fprintf(F, "\\backslashbox{\\textbf{GM}}{\\textbf{TC}} ");

	for (i = 0; i < NBVAL - 1; i++)
	{
		fprintf(F, "& \\textbf{[.%d,.%d[} ",i,i+1);
	}

	fprintf(F, "& \\textbf{[.9,1.0[} ");
	fprintf(F, "&\\textbf{ = 1.0}");

	fprintf(F, "\\\\ \n");
	fprintf(F, "\\hline\n");


	for( i = 0; i < NBVAL - 1;i++)
	{
		fprintf(F, "\\textbf{[.%d,.%d[} &",i,i+1);
		
		for( j = 0; j <  NBVAL;j++)
		{
			fprintf(F, "\\textbf{%d} &",MC[i][j]);
		}
		fprintf(F, "\\textbf{%d} \\\\ \\hline \n",MC[i][NBVAL]);

	}
	fprintf(F, "\\textbf{[.9,1.0[} &");
	for( j = 0; j <  NBVAL;j++)
	{
		fprintf(F, "\\textbf{%d} &",MC[NBVAL-1][j]);
	}
	fprintf(F, "\\textbf{%d} \\\\ \\hline \n",MC[NBVAL-1][NBVAL]);

	fprintf(F, "\\textbf{= 1.0} &");
	for( j = 0; j <  NBVAL;j++)
	{
		fprintf(F, "\\textbf{%d} &",MC[NBVAL][j]);
	}
	fprintf(F, "\\textbf{%d} \\\\ \\hline \n",MC[NBVAL][NBVAL]);

	fprintf(F, "\\end{longtable}\n");
	fprintf(F, "\\end{center}\n");
	fclose(F);
	

}
void fermeture_fichier_latex()
{

	char fichier[256];
	sprintf(fichier,"fichiers/tableau.tex");

	FILE *F = fopen(fichier,"a");
	if( F == NULL)
	{
		fprintf(stdout, "Cannot write the file %s\n", fichier);
		exit(4);
	}
	fprintf(F, "\\end{document}\n" );
	
	fclose(F);
}


