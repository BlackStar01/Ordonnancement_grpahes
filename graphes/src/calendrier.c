int trouverIndiceSommet(int valeurSommet, int *tab)
{
    int indice = -1;
    for (int i = 0; i < nbrSommets(); i++)
    {
        if (valeurSommet == tab[i]) indice = i;
    }
    
    return indice;
}

int DateAuPlusTot(int sommet, File **TabPredecesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile();
    int dateAuPlusTot = TabDurees[Sommet], max = 0,s = 0, sMax = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    
    if(copiePredecesseur->firstElement == NULL) goto EscapeLoop;
        s = defiler(copiePredecesseur);
        max = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet);
        sMax = s;
    
    while (copiePredecesseur->firstElement != NULL)
    {       
        s = defiler(copiePredecesseur);
        int nvDate = DateAuPlusTot(s, TabPredecesseur, TabDurees, tabSommet);
        if(nvDate > max)
        {
            max = nvDate;
            sMax = s;
        }
    }
    
    dateAuPlusTot = TabDurees[trouverIndiceSommet(sMax, tabSommet)] + max;
    EscapeLoop:;
    return dateAuPlusTot;
}

int DateAuPlusTard(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    int dateAuPlusTard = DateAuPlusTot(sommet,TabPredecesseur,TabDurees,tabSommet), min = 0,s = 0,sMin = Sommet; 
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet]); 
    
    if(copieSuccesseur->firstElement == NULL) goto EscapeLoop;    
    
    s = defiler(copieSuccesseur);
    min = DateAuPlusTard(s, TabPredecesseur, TabPredecesseur, TabDurees, tabSommet);
    sMin = s;
    
    while (copieSuccesseur->firstElement != NULL)
    {       
        s = defiler(copieSuccesseur);
        int nvDate = DateAuPlusTard(sMin, TabPredecesseur, TabPredecesseur, TabDurees, tabSommet);
        if(nvDate < min) {
            min = nvDate;
            sMin = s;
        }
    }
    dateAuPlusTard = DateAuPlusTard(sMin,TabPredecesseur,TabSuccesseur,TabDurees,tabSommet) - TabDurees[trouverIndiceSommet(sMin, tabSommet)];
    
    EscapeLoop:; 
    return dateAuPlusTard;
}

int margeTotale(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    return DateAuPlusTard(sommet,TabPredecesseur,TabSuccesseur,TabDurees,tabSommet) - DateAuPlusTot(sommet,TabPredecesseur, TabDurees,tabSommet);
}