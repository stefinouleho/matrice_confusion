#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define NBVAL 10
#define PAS (1.0/NBVAL)

void liberer_matrice(int ** matrice);
int **matrice_confusion(FILE *F, FILE *G, int *molecules, int taille);
int min (int a, int b);
void affiche_matrice(int ** matrice);
int * lecture_molecules(int taille);
void ecrire_resultat(int *mols, int pos1, int pos2,float sim1, float sim2, int i,int j);
void ecrire_matrice_confusion(int ** matrice);
