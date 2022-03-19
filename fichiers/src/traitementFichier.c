#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.c"

int nbrSommets()
{
    FILE *ourFile = fopen("../fichiers/test.txt", "r");
    char character;
    int compt = 1;

    if (ourFile == NULL)
    {
        perror("File does not exist!!!\n");
        return -1;
    }

    while ((character = fgetc(ourFile)) != EOF)
    {
        if (character == '\n')
        {
            compt++;
        }
    }

    fclose(ourFile);

    return compt;
}

bool detectionPointEntreeUnique(bool **matriceAdjacence)
{
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
                printf("Entrée : %d \n", i+1);
                nbrEntrees++;
            }
        }
        compt = 0;
    }
    if (nbrEntrees > 1)
    {
        result = false;
    }
    
    return result;
}

bool detectionCircuit(bool **matriceAdjacence)
{
    bool result = false;
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < nbrSommets(); j++)
        {
            if (i == j)
            {
                if (matriceAdjacence[i][j] == 1)
                {
                    printf("Circuit detecté...\n");
                    result = true;
                    goto escapeLoop;
                }
            }
        }
    }
    escapeLoop:
    /* Elle retourne  0 quand le resultat est faux et 1 quand c'est vrai ...*/
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
                printf("Sortie : %d \n", i+1);
                nbrSorties++;
            }
        }
        compt = 0;
    }
    if (nbrSorties > 1)
    {
        result = false;
    }
    
    return result;
}

bool detectionArcNegatif(int *tab)
{
    bool result = false;
    int i = 0;
    while (tab[i] != '\0')
    {
        if (tab[i] < 0)
        {
            printf("Arc negatif repéré ... \n");
            result = true;
            break;
        }
        i++;
    }

    return result;
}

int *tableauDeSommets(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = copieFile(uneFile);
    int i = 1, *tab = malloc(nbrSommets() * sizeof(int));

    tab[0] = defiler(f1);

    while (f1->firstElement->suivant != NULL)
    {
        if (defiler(f1) == -1)
        {
            int temp = defiler(f1);
            if (temp != -1)
            {
                tab[i] = temp;
                i++;
            }
        }
    }
    tab[i] = '\0';
    return tab;
}

int *tableauDurees(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = copieFile(uneFile);
    int i = 1, *tab = malloc(nbrSommets() * sizeof(int));

    defiler(f1);
    tab[0] = defiler(f1);

    while (f1->firstElement->suivant != NULL)
    {
        if (defiler(f1) == -1)
        {
            defiler(f1);
            tab[i] = defiler(f1);
            i++;
        }
    }

    tab[i] = '\0';

    return tab;
}

File *fileDePredecesseurs(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = copieFile(uneFile);

    File *fileDePredecesseurs = initialisationFile();
    /* On fait une copie pour éviter de perdre des données ... On travaillera avec la copie du coup */

    int compt = 0;
    while (f1->firstElement != NULL)
    {
        if (compt == 0)
        {
            /*
                On défile deux fois pour enlever le premier element de la file (sommet)
                Et le deuxieme element ... qui est la durée
            */
            defiler(f1);
            defiler(f1);
            compt++;
        }

        /*
            -1 représente le séparateur de notre file
        */

        int alpha = defiler(f1);
        if (alpha == -1)
        {
            defiler(f1);
            defiler(f1);
        }
        enfiler(fileDePredecesseurs, alpha);
    }

    return fileDePredecesseurs;
}

/*-------------------- Conversion file en tableau de File -------------------*/

File **ConvertEnTabDeFile(File *uneFile)
{
    File *f1 = initialisationFile();
    /* On fait une copie pour éviter de perdre des données ... On travaillera avec la copie du coup */
    f1 = copieFile(uneFile);

    File **TabDeFiles = malloc(nbrSommets() * sizeof(File));
    for (int i = 0; i < nbrSommets(); i++)
    {
        TabDeFiles[i] = initialisationFile();
        int el = defiler(f1);
        while (el != -1)
        {
            enfiler(TabDeFiles[i], el);
            el = defiler(f1);
        }
    }

    return TabDeFiles;
}

/* -------------------Recuperer les données du fichier-----------------------------*/
File *recupererDonnees(FILE *fichier)
{
    File *maFile = initialisationFile();
    int i = 0;
    char c[20];

    if (fichier == NULL)
    {
        perror("Erreur d'ouverture du fichier\n");
    }

    while (fscanf(fichier, "%[^\n]%*c", c) != EOF)
    {
        char *token = strtok(c, " "); /* Il fonctionne comme un split en javascript */
        while (token != NULL)
        {
            enfiler(maFile, atoi(token));
            token = strtok(NULL, " ");
            i++;
        }
        enfiler(maFile, -1);
        i++;
    }

    if (fclose(fichier) == EOF)
    {
        perror("Erreur de fermerture du fichier");
    }

    return maFile;
}
