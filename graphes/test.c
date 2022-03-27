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
    
    Graphe *g = initialisationGraphe(nbrSommets(),tableauDurees(data),fileP);
    afficherMatriceBooleenne(g->matriceAdjacence, nbrSommets(), tableauDeSommets(data));
    /* afficherMatriceNormale(g->matriceValeurs, nbrSommets(),tableauDeSommets(data)); 
    printf("\n%d\n", detectionPointSortieUnique(g->matriceAdjacence));
    printf("\n%d\n", detectionPointEntreeUnique(g->matriceAdjacence));
    
    printf("\n\n"); */
    
    /* printf("\n%d\n", detectionArcNegatif(tableauDurees(data)));
    if(detectionCircuit(g))
    {
        printf("\nIl y a un circuit \n");
    }else{
        printf("\nPas de circuit\n");
    } */

    rangSommets(g, data);

    free(g);
    free(fileP);

    return 0;
}

