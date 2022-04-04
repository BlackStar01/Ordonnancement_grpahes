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
    
    if(copiePredecesseur->firstElement != NULL){
        s = defiler(copiePredecesseur);
        max = TabDurees[trouverIndiceSommet(s,tabSommet)];
        sMax = s;
    }
    while (copiePredecesseur->firstElement != NULL)
    {       
        s = defiler(copiePredecesseur);
        int nvDuree = TabDurees[trouverIndiceSommet(s,tabSommet)];
        if(nvDuree > max)
        {
            max = nvDuree;
            sMax = s;
        }
    }
    
    dateAuPlusTot += max;
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
    min = TabDurees[trouverIndiceSommet(s,tabSommet)];
    sMin = s;

    while (copieSuccesseur->firstElement != NULL)
    {       
        s = defiler(copieSuccesseur);
        if(TabDurees[trouverIndiceSommet(s,tabSommet)] < min) {
            min = TabDurees[trouverIndiceSommet(s,tabSommet)];
            sMin = s;
        }
    }
    dateAuPlusTard = DateAuPlusTard(sMin,TabPredecesseur,TabSuccesseur,TabDurees,tabSommet);
    dateAuPlusTard -= TabDurees[sMin];
    
    EscapeLoop:; 
    return dateAuPlusTard;
}

int margeTotale(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    return DateAuPlusTard(sommet,TabPredecesseur,TabSuccesseur,TabDurees,tabSommet) - DateAuPlusTot(sommet,TabPredecesseur, TabDurees,tabSommet);
}