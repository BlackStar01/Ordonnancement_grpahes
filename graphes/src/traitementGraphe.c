#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../fichiers/src/traitementFichier.c"
#include "./affichagesMatrices.c"

typedef struct Graphe Graphe;
struct Graphe
{
    int nbrSommets;
    int **matriceValeurs;
    bool **matriceAdjacence;
};

/* ----------- Création de la matrice d'ajacence ------------  */

Graphe *initialisationGraphe(int nbrSommets, int *tableauDurees, File *predecesseurs) 
{
    Graphe *monGraphe = malloc(sizeof(*monGraphe));
    monGraphe->nbrSommets = nbrSommets;
    int p=0, valeur = 0, sommetTemporaire = 0;
    
    /*----------------Remplissage de la matrice de valeurs-------------*/
    File* copieFileDePredecesseurs = copieFile(predecesseurs);

    afficherFile(copieFileDePredecesseurs);
    monGraphe->matriceValeurs = (int **)malloc(nbrSommets * sizeof(int*));
    for(int i = 0; i < nbrSommets; i++) 
    {
        monGraphe->matriceValeurs[i] = (int *)malloc(nbrSommets * sizeof(int));
        for(int j = 0; j < nbrSommets; j++)
        {
            monGraphe->matriceValeurs[i][j] = 0;
        }
    }
    /*-----------On initialise et on met toutes les valeurs à 0-------*/
    printf("\nRemplissage  matrice  des  valeurs ...\n");
    while (copieFileDePredecesseurs->firstElement->suivant != NULL)
    {
        int a = copieFileDePredecesseurs->firstElement->nombre;
        if (a == -1)
        {
            sommetTemporaire++;
            defiler(copieFileDePredecesseurs);
        }
        else
        {
            p = defiler(copieFileDePredecesseurs);
            valeur = tableauDurees[p - 1];
            monGraphe->matriceValeurs[p - 1][sommetTemporaire] = valeur;
        }
        copieFileDePredecesseurs->firstElement = copieFileDePredecesseurs->firstElement->suivant;
    }
    
    
    /*------------Remplissage de la matrice d'adjacence---------------*/
    monGraphe->matriceAdjacence = (bool **)malloc(nbrSommets * sizeof(int*));
    
    
    File **TabPredecesseurs = malloc(nbrSommets * sizeof(File));
    /* Conversion de la file en tableau de files (car sera plus facile à manipuler pour la matrice) /
        On met déjà tous les elements à 0*/
    for(int i = 0; i < nbrSommets; i++) 
    {
        monGraphe->matriceAdjacence[i] = (bool *)malloc(nbrSommets * sizeof(int));
        TabPredecesseurs[i] = initialisationFile();
        for(int j = 0; j < nbrSommets; j++)
        {
            monGraphe->matriceAdjacence[i][j] = 0;
        }
    }
    
    TabPredecesseurs = ConvertEnTabDeFile(predecesseurs);
    
    printf("Remplissage de la matrice d'adjacence ... \n");
    /* sleep(3); */
        
    for (int i = 0; i < nbrSommets; i++)
    {       
        
        if (nbrElementsFile(TabPredecesseurs[i]) == 0) continue;
        
        while (TabPredecesseurs[i]->firstElement != NULL)
        {
            int compteur = 0;
            while (compteur < nbrElementsFile(TabPredecesseurs[i]))
            {
                p = defiler(TabPredecesseurs[i]);
                monGraphe->matriceAdjacence[p - 1][i] = 1;                
                compteur++;
            }
        }
    }  
    printf("Initialisation effectuée ... \n");
    return monGraphe;
}

int **copieTableau(int **Tableau){
    int **copie = malloc(nbrSommets() * sizeof(int));
    for (int i = 0; i < nbrSommets(); i++)
    {
        copie[i] = malloc(nbrSommets() * sizeof(int));
        for (int j = 0; j < nbrSommets(); j++)
        {
            copie[i][j] = Tableau[i][j];
        }
    }
    return copie;
}

Graphe *copieG(Graphe *model)
{
    int nbrSommets = model->nbrSommets;
    Graphe *monGraphe = malloc(sizeof(monGraphe));
    
    monGraphe->matriceValeurs = malloc(nbrSommets * sizeof(int*));
    
    monGraphe->matriceAdjacence = (bool **)malloc(nbrSommets * sizeof(int*));
    
    monGraphe->nbrSommets = model->nbrSommets;
    
    /* Copie de la matrice d'adjacence et la matrice de valeurs */
    for (int i = 0; i < nbrSommets; i++)
    {
        monGraphe->matriceAdjacence[i] = malloc(nbrSommets * sizeof(bool));
        for (int j = 0; j < nbrSommets; j++)
        {
            monGraphe->matriceAdjacence[i][j] = model->matriceAdjacence[i][j];
        }
    }
    
    return monGraphe;
}
