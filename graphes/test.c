#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"

int main(int argc, char const *argv[])
{
    FILE *fichier = fopen("../fichiers/test.txt", "r");
    File *data = recupererDonnees(fichier);

    printf("\n Affichage de toutes les données : \n");    
    afficherFile(data);
    
    printf("\n File de predecesseurs : \n");
    File *fileP = initialisationFile();
    fileP = fileDePredecesseurs(data);
    afficherFile(fileP);

    printf(" \n On va initaliser now ... \n");
    
    Graphe *g = initialisationGraphe(nbrSommets(),tableauDurees(data),fileP);
    afficherMatriceBooleenne(g->matriceAdjacence, nbrSommets());
    afficherMatriceNormale(g->matriceValeurs, nbrSommets());
    
    printf("\n\n");
    printf("%d", detectionCircuit(g->matriceAdjacence));
    printf("%d", detectionArcNegatif(tableauDurees(data)));

    free(g);
    free(fileP);

    return 0;
}

