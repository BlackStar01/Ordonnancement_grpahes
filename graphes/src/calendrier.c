int DateAuPlusTot(int sommet, File **TabPredecesseur, int *TabDurees, int *tabSommet)
{
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile();
    int dateAuPlusTot = 0, max = 0, s = 0, sMax = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);

    if (copiePredecesseur->firstElement == NULL)
    {
        goto EscapeLoop;
    }
    else
    {
        s = defiler(copiePredecesseur);
        max = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];
        sMax = s;

        while (copiePredecesseur->firstElement != NULL)
        {
            s = defiler(copiePredecesseur);
            int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];
            if (nvDate > max)
            {
                max = nvDate;
                sMax = s;
            }
        }
        dateAuPlusTot = max;
    }
EscapeLoop:;
    return dateAuPlusTot;
}

void traceDateAuPlusTot(int sommet, File **TabPredecesseur, int *TabDurees, int *tabSommet)
{
    printf("\n\n---------------Date Au Plus Tot de %d----------------\n\n", sommet);
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile();
    int dateAuPlusTot = 0, max = 0, s = 0, sMax = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);

    if (copiePredecesseur->firstElement == NULL)
    {
        goto EscapeLoop;
    }
    else
    {
        printf("\n\n Predecesseur(s) de %d est(sont) : ", sommet);
        afficherFile(copiePredecesseur);
        printf("Avec pour date(s) au plus tôt : ");

        File *copieP = initialisationFile();
        copieP = copieFile(copiePredecesseur);

        while (copieP->firstElement != NULL)
        {
            int pred = defiler(copieP);
            printf("%d , ", DateAuPlusTot(pred, TabPredecesseur, TabDurees, tabSommet));
        }
        printf("\n");
        s = defiler(copiePredecesseur);
        max = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];
        sMax = s;

        while (copiePredecesseur->firstElement != NULL)
        {
            s = defiler(copiePredecesseur);
            int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];
            if (nvDate > max)
            {
                max = nvDate;
                sMax = s;
            }
        }
        dateAuPlusTot = max;
        printf("Date au plus tôt  =  %d \n\n\n", dateAuPlusTot);
    }
EscapeLoop:;
}

int DateAuPlusTard(int sommet, Graphe *Graphe, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet)
{
    int Sommet = trouverIndiceSommet(sommet, tabSommet), min = 0, s = 0, sMin = Sommet;
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet]);

    // Trouvons la date au plus tard de W (OMEGA)---------------------------------------------------------------

    File *PointsDeSortie = initialisationFile();
    PointsDeSortie = detectPointSortie(Graphe);
    int dateAuPlusTotW = 0;

    s = defiler(PointsDeSortie);
    dateAuPlusTotW = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];

    while (PointsDeSortie->firstElement != NULL)
    {
        s = defiler(PointsDeSortie);
        int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];
        if (nvDate > dateAuPlusTotW)
        {
            dateAuPlusTotW = nvDate;
        }
    }

    // -----------------------------------------------------------------------------------------------------------

    int dateAuPlusTard = dateAuPlusTotW - TabDurees[Sommet];

    if (copieSuccesseur->firstElement == NULL)
        goto EscapeLoop;

    s = defiler(copieSuccesseur);
    min = DateAuPlusTard(s, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - TabDurees[Sommet];
    sMin = s;

    while (copieSuccesseur->firstElement != NULL)
    {
        s = defiler(copieSuccesseur);
        int nvDate = DateAuPlusTard(s, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - TabDurees[Sommet];
        if (nvDate < min)
        {
            min = nvDate;
            sMin = s;
        }
    }
    dateAuPlusTard = min;

EscapeLoop:;
    return dateAuPlusTard;
}

void traceDateAuPlusTard(int sommet, Graphe *Graphe, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet)
{
    printf("\n\n---------------Date Au Plus Tard de %d----------------\n\n", sommet);

    int Sommet = trouverIndiceSommet(sommet, tabSommet), min = 0, s = 0, sMin = Sommet;
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet]);

    // Trouvons la date au plus tard de W (OMEGA)---------------------------------------------------------------

    File *PointsDeSortie = initialisationFile();
    PointsDeSortie = detectPointSortie(Graphe);
    int dateAuPlusTotW = 0;

    s = defiler(PointsDeSortie);
    dateAuPlusTotW = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];

    while (PointsDeSortie->firstElement != NULL)
    {
        s = defiler(PointsDeSortie);
        int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s, tabSommet)];
        if (nvDate > dateAuPlusTotW)
        {
            dateAuPlusTotW = nvDate;
        }
    }

    printf("\n Date au plus tard de W = %d(Qui est egalement sa date au plus tot)\n", dateAuPlusTotW);
    // -----------------------------------------------------------------------------------------------------------

    int dateAuPlusTard = dateAuPlusTotW - TabDurees[Sommet];

    if (copieSuccesseur->firstElement == NULL)
    {
        printf("\n %d est un puit ...\n", sommet);
        printf("Date au plus tard de %d = dateAuPlusTard(W) - Duree(%d) = %d\n\n", sommet, sommet, dateAuPlusTard);
        goto EscapeLoop;
    }

    printf("\n\n Le(s) successeur(s) de %d est(sont) : ", sommet);
    afficherFile(copieSuccesseur);
    printf("\n\n Avec pour date(s) au plus tard : ");

    File *copieS = initialisationFile();
    copieS = copieFile(copieSuccesseur);

    while (copieS->firstElement != NULL)
    {
        int succ = defiler(copieS);
        printf("%d , ", DateAuPlusTard(succ, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet));
    }
    printf("\n");

    s = defiler(copieSuccesseur);
    min = DateAuPlusTard(s, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - TabDurees[Sommet];
    sMin = s;

    while (copieSuccesseur->firstElement != NULL)
    {
        s = defiler(copieSuccesseur);
        int nvDate = DateAuPlusTard(s, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - TabDurees[Sommet];
        if (nvDate < min)
        {
            min = nvDate;
            sMin = s;
        }
    }
    dateAuPlusTard = min;

    printf("\n\n Date au plus tard de %d = dateAuPlusTard(%d) - Duree(%d) = %d \n\n", sommet, sMin, sommet, dateAuPlusTard);
EscapeLoop:;
}

int margeTotale(int sommet, Graphe *Graphe, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet)
{
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    return DateAuPlusTard(sommet, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - DateAuPlusTot(sommet, TabPredecesseur, TabDurees, tabSommet);
}

void traceMargeTotale(int sommet, Graphe *Graphe, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet)
{
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    int MT = DateAuPlusTard(sommet, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - DateAuPlusTot(sommet, TabPredecesseur, TabDurees, tabSommet);
    printf("\n\n Marge totale de %d = DateAuPlusTard(%d) - DateAuPlusTot(%d) = %d\n\n", sommet, sommet, sommet, MT);
}