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
        return 555;
    }
    
}

int DateAuPlusTot(int Sommet, File **TabPredecesseur, int *TabDurees){
    
    File *copiePredecesseur = initialisationFile();
    int Sommet = trouverIndiceSommet(sommet);
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

int DateAuPlusTard(int Sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees){
    File *copiePredecesseur = initialisationFile(), *copieSuccesseur = initialisationFile();
    int Sommet = trouverIndiceSommet(sommet);
    int dateAuPlusTard = DateAuPlusTot(Sommet,TabPredecesseur,TabDurees), min = 0,s = 0,sMin = Sommet;
    copiePredecesseur = copieFile(TabPredecesseur[Sommet - 1]);
    copieSuccesseur = copieFile(TabSuccesseur[Sommet - 1]);
    
    if(copieSuccesseur->== NULL){
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
    dateAuPlusTard = DateAuPlusTard(sMin,TabPredecesseur,TabSuccesseur,TabDurees);
    dateAuPlusTard -= TabDurees[sMin - 1];
    
    EscapeLoop:;   
    return dateAuPlusTard;
}

int margeTotale(int sommet, File **TabPredecesseur, File **TabSuccesseur, int *TabDurees){
    int Sommet = trouverIndiceSommet(sommet);
    return DateAuPlusTard(Sommet,TabPredecesseur,TabSuccesseur,TabDurees) - DateAuPlusTot(Sommet,TabPredecesseur, TabDurees);
}