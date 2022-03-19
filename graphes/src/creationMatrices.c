#include "../../fichiers/src/traitementFichier.c"

bool **creationMatriceAdjacence(int nbrSommets, File *predecesseurs)
{
    bool **matriceAdjacence = (bool **)malloc(nbrSommets * sizeof(bool*));
    
    File **TabPredecesseurs = malloc(nbrSommets * sizeof(File));
    /* Conversion de la file en tableau de files (car sera plus facile à manipuler pour la matrice) /
        On met déjà tous les elements à 0*/
    for(int i = 0; i < nbrSommets; i++) 
    {
        matriceAdjacence[i] = (bool *)malloc(nbrSommets * sizeof(bool));
        TabPredecesseurs[i] = initialisationFile();
        for(int j = 0; j < nbrSommets; j++)
        {
            matriceAdjacence[i][j] = 0;
        }
    }
    
    TabPredecesseurs = ConvertEnTabDeFile(predecesseurs);
    
    printf("Remplissage de la matrice d'adjacence ... \n");
    int p =0;
    for (int i = 0; i < nbrSommets; i++)
    {       
        if (nbrElementsFile(TabPredecesseurs[i]) == 0) continue;
        
        while (TabPredecesseurs[i]->firstElement != NULL)
        {
            int compteur = 0;
            while (compteur < nbrElementsFile(TabPredecesseurs[i]))
            {
                p = defiler(TabPredecesseurs[i]);
                matriceAdjacence[p - 1][i] = 1;                
                compteur++;
            }
        }
    }  

    return matriceAdjacence;
}

int **creationMatriceValeurs(int nbrSommets, int *tableauDurees, File *predecesseurs)
{
    int valeur = 0, sommetTemporaire = 0;
    File* copieFileDePredecesseurs = copieFile(predecesseurs);
    int **matriceValeurs = (int **)malloc(nbrSommets * sizeof(int*));

    /*----------- On initialise et on met toutes les valeurs à 0 -------*/
    for(int i = 0; i < nbrSommets; i++) 
    {
        matriceValeurs[i] = (int *)malloc(nbrSommets * sizeof(int));
        for(int j = 0; j < nbrSommets; j++)
        {
            matriceValeurs[i][j] = 0;
        }
    }

    printf("\nRemplissage  matrice  des  valeurs ...\n");
    int p = 0;
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
            matriceValeurs[p - 1][sommetTemporaire] = valeur;
        }
        copieFileDePredecesseurs->firstElement = copieFileDePredecesseurs->firstElement->suivant;
    }

    return matriceValeurs;  
}