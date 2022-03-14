#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"
#include "../fichiers/src/traitementFichier.c"

int main(int argc, char const *argv[])
{
    FILE *fichier = fopen("../fichiers/test.txt", "r");
    File *data = recupererDonnees(fichier);
    File *copy = initialisationFile();
    copy = data; 

    /* Graphe *graphe1 = initialisationGraphe(nbrSommets(), tableauDurees(data), ); */
    
    afficherFile(data);
    printf("\n\n");
    afficherFile(fileDePredecesseurs(data));
        printf("\n\n");

        
    int *aaa = tableauDeSommets(copy);
    int i = 0;
    do
    {
        printf("%d - ", aaa[i]);
        i++;
    } while (aaa[i] != '\0');

    printf("\n");

    afficherFile(data);
    printf("\n\n");
    afficherFile(fileDePredecesseurs(data));
        printf("\n\n");



    return 0;
}
