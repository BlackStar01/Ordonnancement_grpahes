#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./creationMatrices.c"
#include "./affichagesMatrices.c"
#include "./detectionPointUnique.c"

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
    Graphe *monGraphe = (Graphe *)malloc(sizeof(Graphe));
    
    monGraphe->nbrSommets = nbrSommets;
    monGraphe->matriceAdjacence = creationMatriceAdjacence(nbrSommets, predecesseurs);
    monGraphe->matriceValeurs = creationMatriceValeurs(nbrSommets, tableauDurees, monGraphe->matriceAdjacence);
    
    printf("\n Initialisation du graphe effectuée ... \n");
    return monGraphe;
}

int **copieTableau(int **Tableau, int nbrSommets)
{
    int **copie = malloc(nbrSommets * sizeof(int *));
    for (int i = 0; i < nbrSommets; i++)
    {
        copie[i] = malloc(nbrSommets * sizeof(int));
        for (int j = 0; j < nbrSommets; j++)
        {
            copie[i][j] = Tableau[i][j];
        }
    }
    return copie;
}

Graphe *copieGraphe(Graphe *model)
{
    int nbrSommets = model->nbrSommets;
    Graphe *monGraphe = (Graphe *)malloc(sizeof(Graphe));
    
    monGraphe->matriceValeurs = (int **)malloc(nbrSommets * sizeof(int *));
    
    monGraphe->matriceAdjacence = (bool **)malloc(nbrSommets * sizeof(int *));
    
    monGraphe->nbrSommets = model->nbrSommets;
    
    /* Copie de la matrice d'adjacence et la matrice de valeurs */
    for (int i = 0; i < nbrSommets; i++)
    {
        monGraphe->matriceAdjacence[i] = malloc(nbrSommets * sizeof(bool *));
        monGraphe->matriceValeurs[i] = malloc(nbrSommets * sizeof(int *));
        for (int j = 0; j < nbrSommets; j++)
        {
            monGraphe->matriceAdjacence[i][j] = model->matriceAdjacence[i][j];
            monGraphe->matriceValeurs[i][j] = model->matriceValeurs[i][j];
        }
    }
    
    return monGraphe;
}

/*---------------------  Détection de circuit   -----------------*/

File *detectPointEntree(Graphe *monGraphe)
{
    File *result = initialisationFile();
    bool estUnPointDentree = true;
    for (int i = 0; i < monGraphe->nbrSommets; i++)
    {
        estUnPointDentree = true;
        for (int j = 0; j < monGraphe->nbrSommets; j++)
        {
            if (monGraphe->matriceAdjacence[j][i] == 1)
            {
                estUnPointDentree = false;
                break;
            }
        }
        if (estUnPointDentree)
        {
            enfiler(result, i + 1);
        }
    }
    return result;
}

File *detectPointSortie(Graphe *monGraphe)
{
    File *result = initialisationFile();
    bool isAnEndPoint = true;
    int i = 0, j = 0;
    for (i = 0; i < monGraphe->nbrSommets; i++)
    {
        isAnEndPoint = true;
        for (j = 0; j < monGraphe->nbrSommets; j++)
        {
            if (monGraphe->matriceAdjacence[i][j] == 1)
            {
                isAnEndPoint = false;
                break;
            }
        }
        if (isAnEndPoint)
        {
            enfiler(result, i + 1);
        }
    }
    return result;
}

bool detectionCircuit(Graphe *monGraphe)
{
    Graphe *copie = copieGraphe(monGraphe);
    File *FileDePoint = initialisationFile();
    
    for (int i = 0; i < copie->nbrSommets; i++)
    {
        FileDePoint = FileCat(FileDePoint, FileCat(detectPointEntree(copie), detectPointSortie(copie)));
        
        Element *firstPoint = malloc(sizeof(Element));
        firstPoint = FileDePoint->firstElement;
        
        while (firstPoint != NULL)
        {
            for (int j = 0; j < copie->nbrSommets; j++)
            {
                if (j == (firstPoint->nombre - 1))
                {
                    for (int k = 0; k < copie->nbrSommets; k++)
                    {
                        copie->matriceAdjacence[j][k] = 0;
                        copie->matriceAdjacence[k][j] = 0;
                        if (j == k)
                            copie->matriceAdjacence[j][k] = 1;
                    }
                }
            }
            firstPoint = firstPoint->suivant;
        }
    }
    return (nbrElementsFile(FileDePoint) < copie->nbrSommets);
}

/* Important de le mettre hors de la fonction, sinon il reste toujours à 1 */
int compt = 1;

void rangSommets(Graphe *monGraphe, File *data)
{
    Graphe *copieMonGraphe = malloc(sizeof(Graphe));
    File *pointsEntree = initialisationFile();
    File *copieData = initialisationFile();

    copieData = copieFile(data);
    copieMonGraphe = copieGraphe(monGraphe);
    pointsEntree = detectPointEntree(copieMonGraphe);
    
    if (compt == 1)
    {
        printf("Sommmet %d  ->  ", pointsEntree->firstElement->nombre);
    }
    
    printf(" Rang : %d \n\n", compt);
    /* Retrouver les indices et mettre les lignes à 0 */
    while (pointsEntree->firstElement != NULL)
    {
        for (int i = 0; i < copieMonGraphe->nbrSommets; i++)
        {
            if (tableauDeSommets(copieData)[i] == pointsEntree->firstElement->nombre)
            {
                for (int j = 0; j < copieMonGraphe->nbrSommets; j++)
                {
                    if (copieMonGraphe->matriceAdjacence[i][j] == 1)
                    {
                        copieMonGraphe->matriceAdjacence[i][j] = 0;
                       /*  printf(" indice %d \n", j + 1);   */ 
                    }
                    if (i == j)
                    {
                        /* Astuce de Kessel ... :) */
                        copieMonGraphe->matriceAdjacence[i][j] = 1;
                    }
                    
                }
            }
        }
        pointsEntree->firstElement = pointsEntree->firstElement->suivant;
    }
    compt++;
    pointsEntree = detectPointEntree(copieMonGraphe);
    if (pointsEntree->firstElement == NULL)
    {
        goto escapeLoop;
    }
    else
    {
        printf("Sommet %d  ->  ", pointsEntree->firstElement->nombre);
    }
    rangSommets(copieMonGraphe, copieData);
    escapeLoop:;
    pointsEntree = initialisationFile();
}

