
int DateAuPlusTot(int sommet, File **TabPredecesseur, int *TabDurees, int *tableauSommet){
    
    File *copiePredecesseur = initialisationFile();
    int Sommet = trouverIndiceSommet(sommet , tableauSommet);
    int dateAuPlusTot = TabDurees[Sommet - 1], max = 0,s = 0, sMax = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet - 1]);
    
        if(copiePredecesseur->firstElement != NULL){
            s = defiler(copiePredecesseur);
            max = TabDurees[s - 1];
            sMax = s;
        }
        while (copiePredecesseur->firstElement != NULL)
        {       
            s = defiler(copiePredecesseur);
            if(TabDurees[s - 1] > max)
            {
                max = TabDurees[s - 1];
                sMax = s;
            }
        }
    
    dateAuPlusTot += max;
    return dateAuPlusTot;
}

int DateAuPlusTard(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tableauSommet){
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    int Sommet = trouverIndiceSommet(sommet , tableauSommet);
    int dateAuPlusTard = DateAuPlusTot(Sommet,TabPredecesseur,TabDurees,tableauSommet), min = 0,s = 0,sMin = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet - 1]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet - 1]);
    
    if(copieSuccesseur->firstElement== NULL){
        goto EscapeLoop;    
    }else{    
        s = defiler(copieSuccesseur);
        min = TabDurees[s - 1];
        sMin = s;
    }
    while (copieSuccesseur->firstElement != NULL)
    {       
        s = defiler(copieSuccesseur);
        if(TabDurees[s - 1] < min) {
            min = TabDurees[s - 1];
            sMin = s;
        }
    }
    dateAuPlusTard = DateAuPlusTard(sMin,TabPredecesseur,TabSuccesseur,TabDurees,tableauSommet);
    dateAuPlusTard -= TabDurees[sMin - 1];
    
    EscapeLoop:;   
    return dateAuPlusTard;
}

int margeTotale(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tableauSommet){
    int Sommet = trouverIndiceSommet(sommet , tableauSommet);
    return DateAuPlusTard(Sommet,TabPredecesseur,TabSuccesseur,TabDurees,tableauSommet) - DateAuPlusTot(Sommet,TabPredecesseur, TabDurees,tableauSommet);
}