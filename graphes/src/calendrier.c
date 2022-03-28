int trouverIndiceSommet(int valeurSommet, int *tab)
{
    int indice = 0, i = 0;
    bool estTrouve = false;
    while (tab[i] != '\n')
    {
        if (valeurSommet == tab[i])
        {
            estTrouve = true;
            break;
        }
        else 
        {
            estTrouve = false;
            indice++;
        }
        i++;
    }
    if (estTrouve)
    {
        return indice;
    }
    else
    {
        return -1;
    }
}

int DateAuPlusTot(int sommet, File **TabPredecesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile();
    int dateAuPlusTot = TabDurees[Sommet], max = 0,s = 0, sMax = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    
        if(copiePredecesseur->firstElement != NULL){
            s = defiler(copiePredecesseur);
            max = TabDurees[s];
            sMax = s;
        }
        while (copiePredecesseur->firstElement != NULL)
        {       
            s = defiler(copiePredecesseur);
            if(TabDurees[s] > max)
            {
                max = TabDurees[s];
                sMax = s;
            }
        }
    
    dateAuPlusTot += max;
    return dateAuPlusTot;
}

int DateAuPlusTard(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees, int *tabSommet){
    int Sommet = trouverIndiceSommet(sommet, tabSommet);
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    int dateAuPlusTard = DateAuPlusTot(Sommet,TabPredecesseur,TabDurees,tabSommet), min = 0,s = 0,sMin = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet]);
    
    if(copieSuccesseur == NULL){
        goto EscapeLoop;    
    }else{    
        s = defiler(copieSuccesseur);
        min = TabDurees[s];
        sMin = s;
    }
    while (copieSuccesseur->firstElement != NULL)
    {       
        s = defiler(copieSuccesseur);
        if(TabDurees[s] < min) {
            min = TabDurees[s];
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