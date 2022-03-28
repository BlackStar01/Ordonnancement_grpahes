#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"
#include "./src/calendrier.c"

int main(int argc, char const *argv[])
{
    FILE *fichier = fopen("../fichiers/test.txt", "r");
    File *data = recupererDonnees(fichier);
    
    
    Graphe *g = initialisationGraphe(nbrSommets(),tableauDurees(data),fileP);
    printf("-----------------------MATRICE D' ADJACENCE-----------------------------------\n\n");
    afficherMatriceBooleenne(g->matriceAdjacence, nbrSommets(), tableauDeSommets(data));
   
    printf("-----------------------MATRICE DE VALEURS-----------------------------------\n\n");
    afficherMatriceNormale(g->matriceValeurs, nbrSommets(),tableauDeSommets(data)); 
    
    if (detectionPointSortieUnique(g->matriceAdjacence))
    printf("Il  y  a  une  seule source");
    
    printf("\n%d\n", detectionPointSortieUnique(g->matriceAdjacence));
    printf("\n%d\n", detectionPointEntreeUnique(g->matriceAdjacence));
    
    printf("\n\n"); 
    
    /* printf("\n%d\n", detectionArcNegatif(tableauDurees(data)));
    if(detectionCircuit(g))
    {
        printf("\nIl y a un circuit \n");
    }else{
        printf("\nPas de circuit\n");
    } */
    
    rangSommets(g, data);
    
    afficherFile(fileP);
    printf("\n\n ----------------Calendrier------------\n\n");
    
    printf("\n\n ----------------Date au plus tot------------\n\n");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        printf("\ndatePlusTot de %d => %d\n",i+1,DateAuPlusTot(i+1,TabFileP,tabDurees));
    }
    
    printf("\n\n ----------------Date au plus tard------------\n\n");
    for (int i = 0; i < nbrSommets(); i++)
    {
        printf("\ndatePlusTard de %d => %d\n",i+1,DateAuPlusTard(i+1,TabFileP,TabFileS,tabDurees));
    }

    printf("\n\n ----------------Marge  Totale------------\n\n");
    for (int i = 0; i < nbrSommets(); i++)
    {
        printf("\nmargeTotale de %d => %d\n",i+1,margeTotale(i+1,TabFileP,TabFileS,tabDurees));
    }
    
    
    free(g);
    data = initialisationFile();
    free(fileP);
    afficherFile(detectPointSortie(g));
    
    return 0;
}

