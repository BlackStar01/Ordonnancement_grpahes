#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nbrSommets()
{
    FILE *ourFile = fopen("../fichiers/test.txt", "r");
    char character;
    int compt = 1;
    
    if (ourFile == NULL)
    {
        printf("File does not exist!!!\n");
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

int *tableauDurees(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = uneFile;
    int i = 1, *tab = malloc(nbrSommets()*sizeof(int));


    defiler(f1);
    tab[0] = defiler(f1);

    while (f1->firstElement->suivant!=NULL)
    {   
        if (defiler(f1) == 980)
        {
            defiler(f1);
            tab[i] = defiler(f1);
            i++;
        }
    }

    return tab;
}

File *tableauPredecesseurs(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = uneFile;
    /* On fait une copie pour éviter de perdre des données ... On travaillera avec la copie du coup */

    File *fileDePredecesseurs = initialisationFile();
    int compt = 0;
    while (f1->firstElement!=NULL)
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
            980 représente le séparateur de notre file 
        */

        int alpha = defiler(f1);
        if (alpha == 980)
        {
            defiler(f1);
            defiler(f1);
            enfiler(fileDePredecesseurs, 980); // Peut être effacé pour avoir le tableau normal
        }
        else
        { 
            enfiler(fileDePredecesseurs, alpha);
        }
    }    

    return fileDePredecesseurs;
} 

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
        enfiler(maFile, 980);
        i++;
    }

    if (fclose(fichier) == EOF)
    {
        perror("Erreur de fermerture du fichier");
    }

    return maFile;
}