#include <stdio.h>
#include <stdlib.h>
#include "./src/traitementGraphe.c"
#include "../fichiers/src/traitementFichier.c"

int main(int argc, char const *argv[])
{
    FILE *fichier = fopen("../fichiers/test.txt", "r");
    File *data = recupererDonnees(fichier);

    /* Graphe *graphe1 = initialisationGraphe(nbrSommets(), tableauDurees(data), ); */
    
    afficherFile(data);
    afficherFile(tableauPredecesseurs(data));
        printf("\n\n");

    return 0;
}
