#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define NBVAL 10
#define MOLECULES 500
#define PAS (1.0/NBVAL)

void liberer_matrice(int ** matrice, int taille);
void affiche_matrice(int ** matrice, int taille);
int * lecture_molecules(int taille);
int ** lecture_fichier(FILE *F);
int ** matrice_conf(int **M1, int **M2,int *mols, int cas);
void ecriture_matrice ( int **MC, int cas);
void fermeture_fichier_latex();
void initialisation_fichier_latex();


