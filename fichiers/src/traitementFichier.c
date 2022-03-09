#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nbrSommets()
{
    FILE *ourFile = fopen("test.txt", "r");
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

/* File *copieFile(File *uneFile)
{
    int compt = 0;
    File *nouvelleFile = malloc(nbrSommets(uneFile) * sizeof(int));
    nouvelleFile->firstElement = malloc(sizeof(int));

    for (int i = 0; i < nbrSommets; i++)
    {
        graph->durees[i] = model->durees[i];
    }

    return nouvelleFile
} */

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
    
    /* for (int k = 0; k < nbrSommets(); k++)
    {
        printf("%d - ", tab[k]);
    } */

    return tab;
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