#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../fichiers/src/traitementFichier.c"

typedef struct Graphe Graphe;
struct Graphe
{
    int nbrSommets;
    int *tableauDuree;
    bool **matriceAdjacence;
};

/* ----------- Affichage de la matrice d'ajacence ------------  */

void affichage(bool **liste, int taille)
{
    printf("\nAffichage de la matrice d'adjacence\n");
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            printf(" %d ", liste[i][j]);
        }
        printf("\n");
    }
}

Graphe *initialisationGraphe(int nbrSommets, int *tableauDuree, File *predecesseurs) 
{
    Graphe *monGraphe = malloc(sizeof(*monGraphe));
    
    monGraphe->nbrSommets = nbrSommets;
    
    /*----------------Remplissage du tableau de durees----------------*/
    
    monGraphe->tableauDuree = malloc(nbrSommets * sizeof(int));
    for (int i = 0; i < nbrSommets; i++)
    {
        monGraphe->tableauDuree[i] = tableauDuree[i];
    }
    
    /*------------Remplissage de la matrice d'adjacence---------------*/
    int p=0,sommetTemporaire = 0;
    monGraphe->matriceAdjacence = (bool **)malloc(nbrSommets * sizeof(int*));
    
    
    File **TabP = malloc(nbrSommets * sizeof(File));
    /* Conversion de la file en tableau de files (car sera plus facile à manipuler pour la matrice) /
     */
    /*On met déjà tous les elements à 0*/
    for(int i = 0; i < nbrSommets; i++) 
    {
        monGraphe->matriceAdjacence[i] = (bool *)malloc(nbrSommets * sizeof(int));
        TabP[i] = initialisationFile();
        for(int j = 0; j < nbrSommets; j++)
        {
            monGraphe->matriceAdjacence[i][j] = 0;
        }
    }
    
    TabP = TabDePredecesseurs(predecesseurs);
    
    printf("Remplissage de la matrice d'adjacence ... \n");
        
    for (int i = 0; i < nbrSommets; i++)
    {       
        
        if (nbrElementsFile(TabP[i]) == 0) continue;
        
        while (TabP[i]->firstElement != NULL)
        {
            int cpt = 0;
            while (cpt < nbrElementsFile(TabP[i]))
            {
                p = defiler(TabP[i]);
                monGraphe->matriceAdjacence[p - 1][i] = 1;
                cpt++;
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
    
    monGraphe->tableauDuree = malloc(nbrSommets * sizeof(int));
    
    monGraphe->matriceAdjacence = malloc(nbrSommets * sizeof(bool));
    
    monGraphe->nbrSommets = model->nbrSommets;
    
    /* Copie du tableau de durées */
    for (int i = 0; i < nbrSommets; i++)
    {
        monGraphe->tableauDuree[i] = model->tableauDuree[i];
    }
    
    /* Copie de la matrice d'adjacence */
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
