#include <stdio.h>
#include <stdlib.h>

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
    File *File = malloc(sizeof(*File));
    
    if (File == NULL)
    {
        perror("Erreur d'initialisation\n");
        exit(EXIT_FAILURE);
    }
    
    File->firstElement = NULL;
    return File;
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


int nbrElementsFile(File *file){
    int compt = 0;
    if (file == NULL)
    {
        perror("Erreur lors de l'operation\n");
        exit(EXIT_FAILURE);
    }
    if (file ->firstElement == NULL)
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
