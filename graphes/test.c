#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"
#include "./src/calendrier.c"

int main(int argc, char const *argv[])
{
    /* char str1[100] = "This is ", str2[] = "programiz.com";
    printf("%s", strcat(str1, str2)); */

    printf("\n Nombre de sommets : %d \n\n", nbrSommets());

    FILE *fichier = fopen(PATH, "r");
    File *data = recupererDonnees(fichier);
    
    /* printf("\n Affichage de toutes les données : \n");    
    afficherFile(data); */
    
    /* printf("\n File de predecesseurs : \n");
    afficherFile(fileDePredecesseurs(data)); */

    File *fileP = initialisationFile();
    File **TabFileSucc = initialisationTabDeFile(nbrSommets()), **TabFilePred = initialisationTabDeFile(nbrSommets());
    int *tabDurees = malloc(nbrSommets() * sizeof(int));
    tabDurees = tableauDurees(data); 
    int *tabSommets = malloc(nbrSommets() * sizeof(int));
    tabSommets = tableauDeSommets(data);
    fileP = fileDePredecesseurs(data);
    /* afficherFile(fileP); */
    TabFileSucc = TabDeSuccesseurs(data);
    TabFilePred = ConvertFileEnTabDeFile(fileP);

    
    Graphe *g = initialisationGraphe(nbrSommets(),tableauDurees(data),fileP);
    
    printf("\n\n ------------------------ Matrices d'adjacence -----------------------\n\n");

    afficherMatriceBooleenne(g->matriceAdjacence, nbrSommets(), tableauDeSommets(data));

    printf("\n\n ---------------------- Matrice de valeurs  ---------------------------\n\n");

    afficherMatriceNormale(g->matriceValeurs, nbrSommets(),tableauDeSommets(data)); 
    
    printf("\n\n --------------------- Détection de points -----------------------\n\n");

    printf("%d\n", detectionPointEntreeUnique(g->matriceAdjacence));
    printf("%d\n", detectionPointSortieUnique(g->matriceAdjacence));
    
    printf("\n\n ------------------------ Détection Arc Négatif -------------------------\n\n");
    
    if(!detectionArcNegatif(tableauDurees(data)))
    {
        printf("\n Pas d'arc négatif \n");
    }else{
        printf("\n Il y a un ou plusieurs arcs négatifs \n");
    }
  
    printf("\n\n ---------------------- Détection de circuit --------------------\n\n");

    if(detectionCircuit(g))
    {
        printf("\n Il y a un circuit \n");
    }else{
        printf("\n Pas de circuit\n");
    }

    printf("\n\n ------------------- Calcul des rangs des sommets  -----------------\n\n");

    rangSommets(g, data);
    
    printf("\n\n --------------------------  Calendrier  ---------------------------\n\n");
    
    printf("\n\n ------------------------- Dates au plus tot --------------------------\n\n");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        printf("\n Date au plus tôt du sommet de %d => %d\n", tabSommets[i],DateAuPlusTot(i+1,TabFilePred,tabDurees));
    }
    
    printf("\n\n --------------------- Date au plus tard -----------------------\n\n");
    for (int i = 0; i < nbrSommets(); i++)
    {
        printf("\n Date au plus tard du sommet %d => %d\n", tabSommets[i],DateAuPlusTard(i+1,TabFilePred,TabFileSucc,tabDurees));
    }

    printf("\n\n -------------------- Marge Totale -----------------------\n\n");
    for (int i = 0; i < nbrSommets(); i++)
    {
        printf("\n Marge totale du sommet %d => %d\n", tabSommets[i],margeTotale(i+1,TabFilePred,TabFileSucc,tabDurees));
    }

    free(g);
    data = initialisationFile();
    free(fileP);
    
    return 0;
}

