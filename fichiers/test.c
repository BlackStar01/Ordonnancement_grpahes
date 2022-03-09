#include "./src/file.c"
#include "./src/traitementFichier.c"

int main(int argc, char const *argv[])
{
    FILE *fichier1 = fopen("./test.txt", "r");
    
    File *data = recupererDonnees(fichier1);

    afficherFile(data);

    printf("%d \n", nbrSommets());
    tableauDurees(data);
    
    return 0;
}



