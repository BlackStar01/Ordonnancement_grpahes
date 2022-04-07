#include "./src/file.c"
#include "./src/traitementFichier.c"

int main(int argc, char const *argv[])
{
    FILE *fichier1 = fopen("./tableauTest/test.txt", "r");
    
    File *data = recupererDonnees(fichier1);
    File *data_temporaire = copieFile(data);

    afficherFile(data);
    printf("\n\n");

    afficherFile(data);
    printf("\n\n");

    afficherFile(data_temporaire);
    printf("\n\n");
    
    return 0;
}



