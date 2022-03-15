#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"

int main(int argc, char const *argv[])
{
    FILE *fichier = fopen("../fichiers/test.txt", "r");
    File *data = recupererDonnees(fichier);
    
    /* Graphe *graphe1 = initialisationGraphe(nbrSommets(), tableauDurees(data), ); */
    
    afficherFile(data);
    
    printf("\n tableau de predecesseurs : \n");
    File *fileP = initialisationFile();
    fileP = fileDePredecesseurs(data);
    afficherFile(fileP);
    
    printf(" \n On va initaliser now ... \n");
    Graphe *g = initialisationGraphe(nbrSommets(),tableauDurees(data),fileP);
    affichage(g->matriceAdjacence, nbrSommets());
    
    printf("\n\n");
    free(g);
    free(fileP);
/*  afficherFile(fileDePredecesseurs(data));
        printf("\n\n");
    
        
    int *aaa = tableauDeSommets(copy);
    int i = 0;
    do
    {
        printf("%d - ", aaa[i]);
        i++;
    } while (aaa[i] != '\0');
    
    printf("\n");
    
    afficherFile(data);
    printf("\n\n");
    afficherFile(fileDePredecesseurs(data));
        printf("\n\n");*/
    return 0;
}

