#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"

int main(int argc, char const *argv[])
{
    FILE *fichier = fopen("../fichiers/test.txt", "r");
    File *data = recupererDonnees(fichier);

    printf("\n Affichage de toutes les données : \n");    
    afficherFile(data);
    
    printf("\n Tableau de predecesseurs : \n");
    File *fileP = initialisationFile();
    fileP = fileDePredecesseurs(data);
    afficherFile(fileP);

    printf(" \n On va initaliser now ... \n");
    Graphe *g = initialisationGraphe(nbrSommets(),tableauDurees(data),fileP);
    afficherMatrice(g->matriceAdjacence, nbrSommets());
    
    printf("\n\n");
    printf("%d", detectionCircuit(g->matriceAdjacence));

    int *tab = tableauDurees(data);
        detectionArcNegatif(tab));

    printf("\ntab de pred\n\n");
    int i = 0;
    do
    {
        printf("%d - ", tab[i]);
        i++;
    } while (tab[i] != '\0');

    free(g);
    free(fileP);

    return 0;
}

