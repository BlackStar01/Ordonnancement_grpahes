bool detectionPointEntreeUnique(bool **matriceAdjacence)
{
    printf("Points d'entrée : ");
    bool result = true;
    int nbrEntrees = 0;
    for (int i = 0; i < nbrSommets(); i++)
    {
        int compt = 0;
        for (int j = 0; j < nbrSommets(); j++)
        {
            if (matriceAdjacence[j][i] == 1)
            {
                break;
            }
            else
            {
                compt++;
            }

            if (compt == nbrSommets())
            {
                printf(" %d ,", i + 1);
                nbrEntrees++;
            }
        }
        compt = 0;
    }
    if (nbrEntrees > 1)
    {
        result = false;
    }
    if (result == false)
    {
        printf("\n Il y a plusieurs points d'entrée \n");
    }
    else
    {
        printf("\n Il y a un seul point d'entrée \n");
    }

    printf("\n");
    return result;
}

bool detectionPointSortieUnique(bool **matriceAdjacence)
{
    /*
        Un sommet qui n'a que des zéros sur la ligne dans la matrie d'adjacence est une sortie
        On verifie les lignes qui ne contiennent que des zéros
        On incrémente un compteur pour compter le nombre de zeros que contient la ligne
        Quand on trouve le nombre de séros est égale au nombre de colonnes du tableau ... alors il n'y a que des zéros sur la ligne nequestion
        Donc ce point est une sortie

        La fonction retourne 1 = true lorsque la sortie est unique et 0 = false dans le cas contraire
    */
    printf("Points de sorties : ");
    bool result = true;
    int nbrSorties = 0;
    for (int i = 0; i < nbrSommets(); i++)
    {
        int compt = 0;
        for (int j = 0; j < nbrSommets(); j++)
        {
            if (matriceAdjacence[i][j] == 1)
            {
                break;
            }
            else
            {
                compt++;
            }
            if (compt == nbrSommets())
            {
                printf(" %d ,", i + 1);
                nbrSorties++;
            }
        }
        compt = 0;
    }
    if (nbrSorties > 1)
    {
        result = false;
    }
    if (result == false)
    {
        printf("\n Il y a plusieurs points de sortie \n");
    }
    else
    {
        printf("\n Il y a un seul point de sortie \n");
    }
    printf("\n");

    return result;
}