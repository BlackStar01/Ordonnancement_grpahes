#include "./src/menu.c"

int main(int argc, char const *argv[])
{
    
    LectureDuFichier();  
    constructionDuGraphe();
    // AlgoDetectCircuit();
    AfficherCalendrier();
    /* char **aaa = findFiles();
    for (int i = 0; i < 11; i++)
    {
        printf("%s\n", aaa[i]);
    } */
    //  setPath("table 11.txt");
    // int nbrS = nbrSommets();
    // printf("\n Nombre de sommets : %d \n\n", nbrS);
    
    // printf("\n\n -------------------------- I - Lecture du tableau de contraintes dans un fichier et stockage en mémoire -------------------------\n\n");
    
    // FILE *fichier = fopen(getPath(), "r");
    // File *data = recupererDonnees(fichier);
    // if (data != NULL)
    // {
    //     printf("\n Données recupérées avec succès ...\n");
    // }
    // printf("\n\n");
    
    //  printf("\n Affichage de toutes les données : \n");
    // afficherFile(data); 
    
    //  printf("\n File de predecesseurs : \n");
    // afficherFile(fileDePredecesseurs(data)); 
    
    // printf("\n\n ------------------------ II - Affichage du graphe correspondant sous forme matricielle -----------------------\n\n");
    
    // File *fileP = initialisationFile();
    // fileP = fileDePredecesseurs(data);
    // int *tabDurees = malloc(nbrS * sizeof(int));
    // tabDurees = tableauDurees(data);
    
    // File **TabFileSucc = initialisationTabDeFile(nbrSommets());
    // File **TabFilePred = initialisationTabDeFile(nbrSommets());
    
    // int *tabSommets = malloc(nbrSommets() * sizeof(int));
    // tabSommets = tableauDeSommets(data);
    
    // TabFileSucc = TabDeSuccesseurs(data, tabSommets);
    //  afficherFile(fileP); 
    // TabFilePred = ConvertFileEnTabDeFile(fileP);
    
    // Graphe *g = (Graphe *)malloc(sizeof(Graphe));
    // g = initialisationGraphe(nbrS, tabDurees, fileP);
    
    // printf("\n\n ------------------------ Matrices d'adjacence -----------------------\n\n");
    
    // afficherMatriceBooleenne(g->matriceAdjacence, nbrS, tableauDeSommets(data));
    
    // printf("\n\n ---------------------- Matrice de valeurs  ---------------------------\n\n");
    
    // afficherMatriceNormale(g->matriceValeurs, nbrSommets(), tableauDeSommets(data));
    
    // printf("\n\n ---------------------------------- III - Verification des propriétés --------------------------------------\n\n");
    
    // printf("\n\n --------------------- Détection de points -----------------------\n\n");
    
    /* J'ai mis les if juste pour afficher sans les valeurs booleennes *
    if (detectionPointEntreeUnique(g->matriceAdjacence))
    {
        printf(" ");
    }
    if (detectionPointSortieUnique(g->matriceAdjacence))
    {
        printf(" ");
    }
    
    printf("\n\n ------------------------ Détection Arc Négatif -------------------------\n\n");
    
    if (!detectionArcNegatif(tableauDurees(data)))
    {
        printf("\n Pas d'arc négatif \n");
    }
    else
    {
        printf("\n Il y a un ou plusieurs arcs négatifs \n");
    }

    printf("\n\n ---------------------- Détection de circuit --------------------\n\n");

    if (detectionCircuit(g))
    {
        printf("\n Il y a un circuit \n");
    }
    else
    {
        printf("\n Pas de circuit\n\n");
    }
    
    if (!detectionArcNegatif(tableauDurees(data)) && !detectionCircuit(g))
    {
        printf("\n\n ---------------------------------- IV - Calculer les rangs de tous les sommets du graphe. --------------------------------------\n\n");

        printf("\n\n ------------------- Calcul des rangs des sommets  -----------------\n\n");

        rangSommets(g, data);
        
        printf("\n\n ---------------------------------- IV - Calculer le calendrier au plus tôt, le calendrier au plus tard et les marges --------------------------------------\n\n");
        
        printf("\n\n --------------------------  Calendrier  ---------------------------\n\n");

        printf("\n\n ------------------------- Dates au plus tot --------------------------\n\n");

        for (int i = 0; i < nbrSommets(); i++)
        {
            printf("\n Date au plus tôt du sommet de %d => %d\n", tabSommets[i], DateAuPlusTot(tabSommets[i], TabFilePred, tabDurees, tabSommets));
        }

        printf("\n\n --------------------- Date au plus tard -----------------------\n\n");
        for (int i = 0; i < nbrSommets(); i++)
        {
            printf("\n Date au plus tard du sommet %d => %d\n", tabSommets[i], DateAuPlusTard(tabSommets[i], TabFilePred, TabFileSucc, tabDurees, tabSommets));
        }

        printf("\n\n -------------------- Marge Totale -----------------------\n\n");
        for (int i = 0; i < nbrSommets(); i++)
        {
            printf("\n Marge totale du sommet %d => %d\n", tabSommets[i], margeTotale(i + 1, TabFilePred, TabFileSucc, tabDurees, tabSommets));
        }
    }
    else
    {
        printf("\n Ce n'est pas un graphe d'ordonnencement. \n\n");
    }
    
    
    free(g);
    data = initialisationFile();
    free(fileP); */

    return 0;
}
