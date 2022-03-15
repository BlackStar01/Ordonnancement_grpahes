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

int *tableauDeSommets(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = copieFile(uneFile);
    int i = 1, *tab = malloc(nbrSommets()*sizeof(int));

    tab[0] = defiler(f1);

    while (f1->firstElement->suivant!=NULL)
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
    int i = 1, *tab = malloc(nbrSommets()*sizeof(int));
    
    
    defiler(f1);
    tab[0] = defiler(f1);
    
    while (f1->firstElement->suivant!=NULL)
    {   
        if (defiler(f1) == -1)
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
    
    tab[i] = '\0';
    return tab;
}

File *fileDePredecesseurs(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = uneFile;
    
    File *fileDePredecesseurs = malloc(nbrSommets() * sizeof(int));
    f1 = copieFile(uneFile);
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

