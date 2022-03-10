#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../fichiers/src/file.c"

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
    printf("Matrice d'adjacence\n");
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            printf(" %d ", liste[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Graphe *initialisationGraphe(int nbrSommets, int *tableauDuree, File **predecesseurs) 
{
    Graphe *monGraphe = malloc(sizeof(*monGraphe));
    if (monGraphe == NULL)
    {
        perror("Erreur lors de la création du graphe");
        exit(EXIT_FAILURE);
    }
    monGraphe->nbrSommets = nbrSommets;

    /*----------------Remplissage du tableau de durees----------------*/

    monGraphe->tableauDuree = malloc(nbrSommets * sizeof(int));
    for (int i = 0; i < nbrSommets; i++)
    {
        monGraphe->tableauDuree[i] = tableauDuree[i];
    }

    /*------------Remplissage de la matrice d'adjacence---------------*/
    //monGraphe->matriceAdjacence = malloc(nbrSommets *sizeof(bool));
    int sommetTemporaire = 0;
    printf("Remplissage de la matrice d'adjacence ... \n");
    /*sleep(2)*/;
    for (int i = 0; i < nbrSommets; i++)
    {
        monGraphe->matriceAdjacence[i] = malloc(nbrSommets * sizeof(bool));

        while (predecesseurs[i]->firstElement != NULL)
        {
            sommetTemporaire = defiler(predecesseurs[i]);
            monGraphe->matriceAdjacence[i][sommetTemporaire - 1] = 1;
            
        }
    }

    printf("Initialisation effectuée ... \n");

}


Graphe *copie(Graphe *model)
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
