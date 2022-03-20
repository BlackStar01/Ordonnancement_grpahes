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
