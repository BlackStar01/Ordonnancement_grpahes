/*
    Notre liste chainée est un file
*/

#include "List.h"

Liste *listeCat(Liste *file1,Liste *file2){
    if (file1 == NULL || file2 == NULL)
    {
        perror("Erreur lors de la concatenation\n");
        exit(EXIT_FAILURE);
    }
    Liste *file = initialisation();
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



Liste *renderData(int *numbers)
{
    FILE *fileOfData = fopen("./test.txt", "r");

    Liste *file = malloc(sizeof(*file));
    Element *element = malloc(sizeof(*element));
    file = initialisation();

    for (int j = 0; j < numberOfLines(fileOfData); j++)
    {

        for (int i = 0; numbers[i] != '\0'; i++)
        {
            enfiler(file, numbers[i]);
        }
    }

    return file;
}

Liste *tab = NULL;

void freeElement(Element *el)
{
    if (el->suivant != NULL)
    {
        freeElement(el->suivant);
    }
    free(el);
}

void freeListe(Liste *list)
{
    if (list->firstElement != NULL)
    {
        freeElement(list->firstElement);
    }
    free(list);
}


