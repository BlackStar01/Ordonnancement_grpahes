int DateAuPlusTot(int sommet, File **TabPredecesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile();
    int dateAuPlusTot = 0, max = 0,s = 0, sMax = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    
    if(copiePredecesseur->firstElement == NULL) goto EscapeLoop;
        s = defiler(copiePredecesseur);
        max = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s,tabSommet)];
        sMax = s;
    
    while (copiePredecesseur->firstElement != NULL)
    {       
        s = defiler(copiePredecesseur);
        int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s,tabSommet)];
        if(nvDate > max)
        {
            max = nvDate;
            sMax = s;
        }
    }
    
    dateAuPlusTot = max;
    
    EscapeLoop:;
    return dateAuPlusTot;
}

int DateAuPlusTard(int sommet,Graphe *Graphe,  File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet), min = 0,s = 0,sMin = Sommet;
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet]); 
    
    // Trouvons la date au plus tard de W (OMEGA)---------------------------------------------------------------
    
    File *PointsDeSortie = initialisationFile();
    PointsDeSortie = detectPointSortie(Graphe);
    int dateAuPlusTotW = 0;


    s = defiler(PointsDeSortie);
    dateAuPlusTotW = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s,tabSommet)];
    
    while (PointsDeSortie->firstElement != NULL)
    {       
        s = defiler(PointsDeSortie);
        int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet) + TabDurees[trouverIndiceSommet(s,tabSommet)];
        if(nvDate > dateAuPlusTotW)
        {
            dateAuPlusTotW = nvDate;
        }
    }
    
    // -----------------------------------------------------------------------------------------------------------
    
    int dateAuPlusTard = dateAuPlusTotW - TabDurees[Sommet]; 
    
    if(copieSuccesseur->firstElement == NULL) goto EscapeLoop;    
    
    s = defiler(copieSuccesseur);
    min = DateAuPlusTard(s, Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - TabDurees[Sommet];
    sMin = s;
    
    while (copieSuccesseur->firstElement != NULL)
    {       
        s = defiler(copieSuccesseur);
        int nvDate = DateAuPlusTard(s,Graphe, TabPredecesseur, TabSuccesseur, TabDurees, tabSommet) - TabDurees[Sommet];
        if(nvDate < min) {
            min = nvDate;
            sMin = s;
        }
    }
    dateAuPlusTard = min;
    
    EscapeLoop:; 
    return dateAuPlusTard;
}

int margeTotale(int sommet,Graphe *Graphe, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    return DateAuPlusTard(sommet,Graphe,TabPredecesseur,TabSuccesseur,TabDurees,tabSommet) - DateAuPlusTot(sommet,TabPredecesseur, TabDurees,tabSommet);
}