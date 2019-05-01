# Matrice de confusion pour la similarité : MCES sur les graphes moléculaires(GM) simplifiées ( retirer toutes les feuilles ) et les graphes de cycles(GC)

 Les fichiers de sortie:

 - la matrice de confusion dans le fichier matrice_confusion 

( je vais joindre un pdf latex plutard pour que coit plus claire). neanmoins en ligne cest graphes moleculaires et en colonne graphes de cycles

- Dans le dossier "Dossier" on retrouve les couples de molécules tels que :

"GM_GC_i_j.data", sur chaque ligne des fichiers on a : mol1 mol2 simGM simGC

"GM_GC_i_j.data" signifie couples de molécules dont la similarité sur GM est i/10 et j/10 avec GC.


Normalement i et j varient de 0 à 10 mais comme on a des valeurs qui ne sont pas calculées par GM faute de temps , on considère que i = 11 corespond a cette état.



A JOUR
