#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int nbrSommets()
{
    FILE *ourFile = fopen(getPath(), "r");
    char character;
    int compt = 1;
    
    if (ourFile == NULL)    
    {
        perror("File does not exist!!! ");
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
        Element *el_suivant = malloc(sizeof(*el_suivant));
        el_suivant = f1->firstElement->suivant;
        if ((defiler(f1) == -1) && (el_suivant != NULL))
        {
            int temp = defiler(f1);
            if (temp != -1)
            {
                tab[i] = temp;
                i++;
            }
        }
    }
    return tab;
}

int trouverIndiceSommet(int valeurSommet, int *tab)
{
    int indice = -1;
    for (int i = 0; i < nbrSommets(); i++)
    {
        if (valeurSommet == tab[i]) indice = i;
    }
    
    return indice;
}

int *tableauDurees(File *uneFile)
{
    File *f1 = initialisationFile();
    f1 = copieFile(uneFile);
    int i = 1, *tab = malloc(nbrSommets()*sizeof(int));
    
    defiler(f1);
    tab[0] = defiler(f1);
    while (f1->firstElement->suivant != NULL)
    {
        Element *el_suivant = malloc(sizeof(*el_suivant));
        el_suivant = f1->firstElement->suivant;
        if ((defiler(f1) == -1) && el_suivant != NULL)
        {
            defiler(f1);
            tab[i] = defiler(f1);
            i++;
        }
    }
    return tab;
}

File **TabDeSuccesseurs(File *uneFile, int *tabS)
{
    File *f1 = initialisationFile();
    File **TabDeSuccesseurs = malloc(nbrSommets() * sizeof(File));
    
    
    f1 = copieFile(uneFile);
    for (int i = 0; i < nbrSommets(); i++)
    {
        TabDeSuccesseurs[i] = initialisationFile();
    }
    int compt = 0, index = 0;
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
            index++;
            defiler(f1);
            defiler(f1);
        }else{
            enfiler(TabDeSuccesseurs[trouverIndiceSommet(alpha,tabS)], index + 1);
        }
    }
    
    return TabDeSuccesseurs;
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

File **ConvertFileEnTabDeFile(File *uneFile)
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

File *convertTabDeFileEnFile(File **TabDeFile, int nbrSommets){
    File *file = initialisationFile();
    File **copieTableau = initialisationTabDeFile(nbrSommets);
   
    copieTableau = copieTabDeFile(TabDeFile , nbrSommets);
    
    for (int i = 0; i < nbrSommets; i++)
    {
        while (copieTableau[i]->firstElement != NULL)
        {
            enfiler(file , defiler(copieTableau[i]));
        }
        enfiler(file , -1);
    }
    return file;
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
