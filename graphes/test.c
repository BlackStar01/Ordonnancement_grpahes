#include "./src/menu.c"

int main(int argc, char const *argv[])
{
    int option = 0;
    do
    {
        printf("\n\n\n --------------------------------   O P T I O N S   ------------------------------\n\n");
        printf("\n\n\t 1 - Je veux soummettre un fichier ... \n");
        printf("\t 2 - J'ai fini ... Je quitte la console ... \n");
        printf("\n\nTaper un nombre : ");
        scanf("%d", &option);
        if (option == 2)
        {
            goto bye;
        }
        /*
            https://stackoverflow.com/questions/9562218/c-multiple-scanfs-when-i-enter-in-a-value-for-one-scanf-it-skips-the-second-s
            Raison de l'écriture du getchar()...
            Sans cela, on arrive pas à faire le second scanf pour récuprer le nom du fichier ...
        */
        getchar();
         
        LectureDuFichier();
        constructionDuGraphe();
        AfficherMatriceAdjacence();
        AfficherMatriceValeurs();
        AlgoDetectCircuit();
        AlgoDetectArcNegatif();
        AlgoPointEntreeUnique();
        AlgoPointSortieUnique();
        AfficherRangs();
        AfficherCalendrier();

    } while (option != 2);

    bye:
    printf("\nBye...\n\n");

    return 0;
}
