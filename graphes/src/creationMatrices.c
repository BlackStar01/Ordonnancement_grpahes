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
    
    TabPredecesseurs = ConvertFileEnTabDeFile(predecesseurs);
    
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

int **creationMatriceValeurs(int nbrSommets, int *tableauDurees, bool **matriceAdjacence)
{
    int valeur = 0, sommetTemporaire = 0;
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
    printf("Remplissage  matrice  des  valeurs ...\n");
    for (int i = 0; i < nbrSommets; i++)
    {
        for (int j = 0; j < nbrSommets; j++)
        {
            if (matriceAdjacence[i][j] == 1) matriceValeurs[i][j] = tableauDurees[i];
            // Un arc entre 2 sommets est symbolisé par un '1' de la matrice d'adjcence
            // On associe chaque arc (i->j) à la la valeur du sommet prédécesseur sur l'arc(qui est i)            
        }
    }
    return matriceValeurs;  
}