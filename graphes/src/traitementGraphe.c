#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./creationMatrices.c"
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
    monGraphe->matriceAdjacence = creationMatriceAdjacence(nbrSommets, predecesseurs);
    monGraphe->matriceValeurs = creationMatriceValeurs(nbrSommets, tableauDurees, predecesseurs);
    
    printf("\n Initialisation du graphe effectuée ... \n");
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
