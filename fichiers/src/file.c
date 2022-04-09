#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PATHBASE "../fichiers/tableauTest/"
char Path[100];

void setPath(char *FileName){
    strcpy(Path, PATHBASE);
    strcat(Path, FileName);
}

char *getPath(){
    return Path;
}

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct File File;
struct File
{
    Element *firstElement;
};

File *initialisationFile()
{
    File *file = malloc(sizeof(File *));
    if (file == NULL)
    {
        perror("Erreur d'initialisationFile\n");
        exit(EXIT_FAILURE);
    }
    file->firstElement = NULL;
    return file;
}

File **initialisationTabDeFile(int nbrSommets)
{
    File **TabDeFile = malloc(nbrSommets * sizeof(File *));
    for (int i = 0; i < nbrSommets; i++)
    {
        TabDeFile[i] = initialisationFile();
    }
    return TabDeFile;
}

void enfiler(File *file, int numberToAdd)
{
    Element *newElement = malloc(sizeof(*newElement));
    if (file == NULL || newElement == NULL)
    {
        perror("Erreur lors de l'ajout de l'element\n");
        exit(EXIT_FAILURE);
    }

    newElement->nombre = numberToAdd;
    newElement->suivant = NULL;

    if (file->firstElement != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element *currentElement = file->firstElement;
        while (currentElement->suivant != NULL)
        {
            currentElement = currentElement->suivant;
        }
        currentElement->suivant = newElement;
    }
    else /* La file est vide, notre élément est le firstElement */
    {
        file->firstElement = newElement;
    }
}

int defiler(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    if (file->firstElement != NULL)
    {
        Element *elementDefile = file->firstElement;

        nombreDefile = elementDefile->nombre;
        file->firstElement = elementDefile->suivant;
        free(elementDefile);
    }

    return nombreDefile;
}

void afficherFile(File *File)
{
    if (File == NULL)
    {
        perror("Rien à efficher\n");
        exit(EXIT_FAILURE);
    }

    Element *actuel = File->firstElement;

    while (actuel != NULL)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

File *copieFile(File *fileOriginale)
{
    File *fileTemporaire = initialisationFile();
    File *copieFile = initialisationFile();
    while (fileOriginale->firstElement != NULL)
    {
        int elementDefile = defiler(fileOriginale);
        enfiler(fileTemporaire, elementDefile);
        enfiler(copieFile, elementDefile);
    }
    /*
        Pour ramener tous les elements dans la file originale....
        vu qu'ils seront supprimés après la première boucle
        Ca va egalement supprimer les elements de la file temporaire vu qu'on défile
    */
    while (fileTemporaire->firstElement != NULL)
    {
        int elementDefile = defiler(fileTemporaire);
        enfiler(fileOriginale, elementDefile);
    }

    return copieFile;
}

File **copieTabDeFile(File **TabOriginal, int nbrSommets)
{
    File **copie = malloc(nbrSommets * sizeof(File *));

    for (int i = 0; i < nbrSommets; i++)
    {
        copie[i] = initialisationFile();
        copie[i] = copieFile(TabOriginal[i]);
    }
    return copie;
}

int nbrElementsFile(File *file)
{
    int compt = 0;
    if (file == NULL)
    {
        perror("Erreur lors de l'operation\n");
        exit(EXIT_FAILURE);
    }
    if (file->firstElement == NULL)
    {
        return 0;
    }

    Element *currentElement = malloc(sizeof(Element));
    currentElement = file->firstElement;
    /*  On compte le nombre d'elements*/
    while (currentElement != NULL)
    {
        currentElement = currentElement->suivant;
        compt++;
    }

    return compt;
}

File *FileCat(File *file1, File *file2)
{
    if (file1 == NULL || file2 == NULL)
    {
        perror("Erreur lors de la concatenation\n");
        exit(EXIT_FAILURE);
    }
    File *file = initialisationFile();
    file->firstElement = file1->firstElement;
    if (file->firstElement != NULL) /* La file n'est pas vide */
    {
        Element *currentElement = malloc(sizeof(Element));
        currentElement = file->firstElement;
        /* On se positionne à la fin de la file */
        while (currentElement->suivant != NULL)
        {
            currentElement = currentElement->suivant;
        }
        currentElement->suivant = file2->firstElement;
    }
    else /* La file est vide, notre élément est le firstElement */
    {
        file->firstElement = file2->firstElement;
    }
    return file;
}
