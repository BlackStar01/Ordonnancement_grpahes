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
    monGraphe->matriceValeurs = creationMatriceValeurs(nbrSommets, tableauDurees, monGraphe->matriceAdjacence);
    
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

Graphe *copieGraphe(Graphe *model)
{
    int nbrSommets = model->nbrSommets;
    Graphe *monGraphe = (Graphe *)malloc(sizeof(Graphe));
    
    monGraphe->matriceValeurs = (int **)malloc(nbrSommets * sizeof(int*));
    
    monGraphe->matriceAdjacence = (bool **)malloc(nbrSommets * sizeof(int*));
    
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
bool detectionPointEntreeUnique(bool **matriceAdjacence)
{
    bool result = true; 
    int nbrEntrees = 0;
    for (int i = 0; i < nbrSommets(); i++)
    {
        int compt = 0;
        for (int j = 0; j < nbrSommets(); j++)
        {
            if (matriceAdjacence[j][i] == 1)
            {
                break;
            }
            else
            {
                compt++;
            }
            
            if (compt == nbrSommets())
            {
                printf("Entrée : %d \n", i+1);
                nbrEntrees++;
            }
        }
        compt = 0;
    }
    if (nbrEntrees > 1)
    {
        result = false;
    }
    
    return result;
}

bool detectionPointSortieUnique(bool **matriceAdjacence)
{
    /* 
        Un sommet qui n'a que des zéros sur la ligne dans la matrie d'adjacence est une sortie
        On verifie les lignes qui ne contiennent que des zéros 
        On incrémente un compteur pour compter le nombre de zeros que contient la ligne
        Quand on trouve le nombre de séros est égale au nombre de colonnes du tableau ... alors il n'y a que des zéros sur la ligne nequestion
        Donc ce point est une sortie
        
        La fonction retourne 1 = true lorsque la sortie est unique et 0 = false dans le cas contraire
    */
    bool result = true;
    int nbrSorties = 0;
    for (int i = 0; i < nbrSommets(); i++)
    {
        int compt = 0;
        for (int j = 0; j < nbrSommets(); j++)
        {
            if (matriceAdjacence[i][j] == 1)
            {
                break;
            }
            else
            {
                compt++;
            }
            
            if (compt == nbrSommets())
            {
                printf("Sortie : %d \n", i+1);
                nbrSorties++;
            }
        }
        compt = 0;
    }
    if (nbrSorties > 1)
    {
        result = false;
    }
    
    return result;
}
/*---------------------détection de circuit--------------*/

File *detectPointEntree(Graphe *monGraphe)
{
    File *result = initialisationFile();
    bool isAnEntryPoint = true;
    int i = 0, j = 0;
    for (i = 0; i < monGraphe->nbrSommets; i++)
    {
        isAnEntryPoint = true;
        for (j = 0; j < monGraphe->nbrSommets; j++)
        {
            if (monGraphe->matriceAdjacence[j][i] == 1)
            {
                isAnEntryPoint = false;
                break;
            }
        }
        if (isAnEntryPoint)
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



bool detectionCircuit(Graphe *monGraphe){
    Graphe *copie = copieGraphe(monGraphe);
    File *FileDePoint = initialisationFile();
 
    for(int i = 0; i < copie->nbrSommets; i++){
        
        FileDePoint = FileCat(FileDePoint,FileCat(detectPointEntree(copie),detectPointSortie(copie)));
        
        Element *firstPoint = malloc(sizeof(Element));
        firstPoint = FileDePoint->firstElement;
            
            while (firstPoint != NULL)
            {
                for (int j = 0; j < copie->nbrSommets; j++)
                {
                    if(j == (firstPoint->nombre-1)){
                        for (int k = 0; k < copie->nbrSommets; k++)
                        {
                            copie->matriceAdjacence[j][k] = 0;
                            copie->matriceAdjacence[k][j] = 0;
                            if (j == k)copie->matriceAdjacence[j][k] = 1;
                    }
                }
            }
            firstPoint = firstPoint->suivant;
    }
}
    return (nbrElementsFile(FileDePoint) < copie->nbrSommets);
}
