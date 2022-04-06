#include <stdio.h>
#include <stdlib.h>
#include "../../fichiers/src/file.c"
#include "./traitementGraphe.c"
#include "./calendrier.c"

void demanderFichier()
{
    char c[15];
    printf("\n ----------------------------------- M E N U ---------------------------------------- \n");
    printf("\n Ecris le nom de ton fichier (Exemple: table 45.txt) \n");
    gets(c);
    setPath(c);
    FILE *fichier = fopen(getPath(), "r");
    File *data = recupererDonnees(fichier);
    if (data != NULL)
    {
        printf("\n Données recupérées avec succès ...\n");
    }
}