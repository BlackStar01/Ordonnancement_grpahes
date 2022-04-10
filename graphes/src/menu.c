#include <stdio.h>
#include <stdlib.h>
#include "../../fichiers/src/file.c"
#include "./traitementGraphe.c"
#include "./calendrier.c"

File *ourData;
Graphe *ourGraph;

void checkErrorGraphe(Graphe *graph)
{
    if(graph == NULL)
    {
        printf("\n\n Erreur : Graphe  non  initialisé !! \n\n");
        return;
    }
}

bool checkOrdonnancement()
{
    return (detectionArcNegatif(tableauDurees(ourData)) || detectionCircuit(ourGraph) || detectPointEntree(ourGraph) == NULL || detectPointSortie(ourGraph) == NULL);
}

void errorOrdonnancement()
{
    printf("\n Ce n'est pas le graphe n'est pas d'ordonnancement ... \n");
}

void LectureDuFichier()
{
    char c[15];
    printf("\n ----------------------------------- M E N U ---------------------------------------- \n");
    printf("\n Entrez le nom de ton fichier (Exemple: table 45.txt) \n");
    
    // On donne le path du fichier au programme
    gets(c);
    setPath(c);
    
    // On recupere les donnees à partir du fichier
    FILE *fichier = fopen(getPath(), "r");
    File *data = recupererDonnees(fichier);
    // S'il y a erreur recupererDonnees genere une erreur et le programme s'arrete direct        
    
    printf("\n LOADING  DATAS ...\n");
    sleep(1);
    system("clear");
    // On vide la console
    
    // Et on enregistre les donnees dans ourData    
    ourData = initialisationFile();
    ourData = copieFile(data);
    printf("\n\n ----------------------------------- M E N U ---------------------------------------- \n\n");
    printf("\n Données recupérées avec succès ...\n");
}

void constructionDuGraphe(){
    if(ourData == NULL)
    {
        printf("\n\n Erreur : Aucune donnée n' a été lue!! \n\n");
        return;
    }

    File *fileP = initialisationFile();
    fileP = fileDePredecesseurs(ourData);
    int *tabDurees = malloc(nbrSommets() * sizeof(int));
    tabDurees = tableauDurees(ourData);
    
    ourGraph = (Graphe *)malloc(sizeof(Graphe));
    ourGraph = initialisationGraphe(nbrSommets(), tabDurees, fileP, tableauDeSommets(ourData));
    sleep(1);
    printf("\n Graphe  créé avec succès... \n");
}

void AlgoDetectCircuit(){
    checkErrorGraphe(ourGraph);
    printf("%s",(!detectionCircuit(ourGraph))?"\n Le graphe ne possède pas de circuit !\n":"\n Il y a un circuit dans le graphe !\n");
}

void AlgoDetectArcNegatif(){
    checkErrorGraphe(ourGraph);
    printf("%s",(!detectionArcNegatif(tableauDurees(ourData)))?"\n Le graphe ne possède pas d'arc négatif !\n":"\n Le graphe contient un arc négatif !\n");
}

void AlgoPointEntreeUnique(){
    checkErrorGraphe(ourGraph);
    printf("%s",(!detectionPointEntreeUnique(ourGraph->matriceAdjacence))?"\n Le graphe a  plusieurs points  d' entrée  qui  sont : ":"\n Le graphe a  un  point  d' entrée unique  qui est :");
    afficherFile(detectPointEntree(ourGraph));
    printf("\n");    
}

void AlgoPointSortieUnique(){
    checkErrorGraphe(ourGraph);
    
    printf("%s",(!detectionPointSortieUnique(ourGraph->matriceAdjacence))?"\n Le graphe a  plusieurs points  de sortie  qui  sont : ":"\n Le graphe a  un  point  de sortie unique  qui est :");
    afficherFile(detectPointSortie(ourGraph));
    printf("\n");    
}

void AfficherMatriceAdjacence(){

    printf("\n\n ------------------------ Matrices d'adjacence -----------------------\n\n");
    afficherMatriceBooleenne(ourGraph->matriceAdjacence, nbrSommets(), tableauDeSommets(ourData));
}

void AfficherMatriceValeurs(){
    checkErrorGraphe(ourGraph);
    
    printf("\n\n ---------------------- Matrice de valeurs  ---------------------------\n\n");
    afficherMatriceNormale(ourGraph->matriceValeurs, nbrSommets(), tableauDeSommets(ourData));
}

void AfficherRangs(){
    checkErrorGraphe(ourGraph);
    if (checkOrdonnancement())
    {
        errorOrdonnancement();
        return;
    }
    rangSommets(ourGraph, ourData);   
}

void AfficherCalendrier(){
    checkErrorGraphe(ourGraph);
    
    printf("\n\n ----------------------------------  Affichage  Du Calendrier de  %s --------------------------------------\n\n",getPath());
        
    if (checkOrdonnancement())
    {
        errorOrdonnancement();
        return;
    }
    
    
    char buff[100];

    for (int i = 0; i < 23; i++) printf("-");
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < 10; j++) printf("-");
    }

    printf("\n");
    
    strcpy(buff,"| Sommets");
    printf("%s",buff);
    for (int i = 0; i < 23 - (strlen(buff) + 1); i++) printf(" ");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        int nb = 3 - sprintf(buff,"%d",tableauDeSommets(ourData)[i]);
        printf("|");
        for (int j = 0; j < 3 + nb; j++) printf(" ");
        printf("%s",buff);
        for (int j = 0; j < 3; j++) printf(" ");
    }
    printf("|");
    
    
    
    
    printf("\n");
    
    
    for (int i = 0; i < 23; i++) printf("-");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < 10; j++) printf("-");
    }
    
    printf("\n");
    
    
    strcpy(buff,"| Durees");
    printf("%s",buff);
    for (int i = 0; i < 23 - (strlen(buff) + 1); i++) printf(" ");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        int nb = 3 - sprintf(buff,"%d",tableauDurees(ourData)[i]);
        printf("|");
        for (int j = 0; j < 3 + nb; j++) printf(" ");
        printf("%s",buff);
        for (int j = 0; j < 3; j++) printf(" ");
    }
    printf("|");
    
    
    
    printf("\n");
    
    
    for (int i = 0; i < 23; i++) printf("-");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < 10; j++) printf("-");
    }
    
    printf("\n");
    
    
    strcpy(buff,"| Date au plus tot");
    printf("%s",buff);
    for (int i = 0; i < 23 - (strlen(buff) + 1); i++) printf(" ");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        int nb = 3 - sprintf(buff,"%d",DateAuPlusTot(tableauDeSommets(ourData)[i],ConvertFileEnTabDeFile(fileDePredecesseurs(ourData)),tableauDurees(ourData),tableauDeSommets(ourData)));
        printf("|");
        for (int j = 0; j < 3 + nb; j++) printf(" ");
        printf("%s",buff);
        for (int j = 0; j < 3; j++) printf(" ");
    }
    printf("|");
    
    
    
    
    printf("\n");
    
    
    for (int i = 0; i < 23; i++) printf("-");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < 10; j++) printf("-");
    }
    
    printf("\n");
    
    
    strcpy(buff,"| Date au plus tard");
    printf("%s",buff);
    for (int i = 0; i < 23 - (strlen(buff) + 1); i++) printf(" ");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        int nb = 3 - sprintf(buff,"%d",DateAuPlusTard(tableauDeSommets(ourData)[i],ourGraph,ConvertFileEnTabDeFile(fileDePredecesseurs(ourData)),TabDeSuccesseurs(ourData, tableauDeSommets(ourData)),tableauDurees(ourData),tableauDeSommets(ourData)));
        printf("|");
        for (int j = 0; j < 3 + nb; j++) printf(" ");
        printf("%s",buff);
        for (int j = 0; j < 3; j++) printf(" ");
    }
    printf("|");
    
    printf("\n");
   
    for (int i = 0; i < 23; i++) printf("-");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < 10; j++) printf("-");
    }
    
    printf("\n");
    
    
    strcpy(buff,"| Marge Totale");
    printf("%s",buff);
    for (int i = 0; i < 23 - (strlen(buff) + 1); i++) printf(" ");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        int nb = 3 - sprintf(buff,"%d",margeTotale(tableauDeSommets(ourData)[i],ourGraph,ConvertFileEnTabDeFile(fileDePredecesseurs(ourData)),TabDeSuccesseurs(ourData, tableauDeSommets(ourData)),tableauDurees(ourData),tableauDeSommets(ourData)));
        printf("|");
        for (int j = 0; j < 3 + nb; j++) printf(" ");
        printf("%s",buff);
        for (int j = 0; j < 3; j++) printf(" ");
    }
    printf("|");
    
    printf("\n");

    for (int i = 0; i < 23; i++) printf("-");
    
    for (int i = 0; i < nbrSommets(); i++)
    {
        for (int j = 0; j < 10; j++) printf("-");
    }
    
    printf("\n\n");
}