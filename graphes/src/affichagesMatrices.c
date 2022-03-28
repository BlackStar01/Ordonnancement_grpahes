void yellow() {
  printf("\033[1;33m");
}
void red() {
  printf("\033[1;31m");
}
void green() {
  printf("\033[1;32m");
}
void resetColor()
{
    printf("\033[0m");
}
void afficherMatriceBooleenne(bool **liste, int taille, int *tableauDeSommets)
{
    printf("      ");
    for (int j = 0; j < taille; j++)
    {
        if (tableauDeSommets[j] < 10)
        {
           printf("%d    ", tableauDeSommets[j]);
        }
        else if (tableauDeSommets[j] < 100)
        {
           printf("%d   ", tableauDeSommets[j]);
        }   
        else
        {
           printf("%d ", tableauDeSommets[j]);
        }
    }
    printf("\n\n");
    for (int i = 0; i < taille; i++)
    {
        if (tableauDeSommets[i] < 10)
        {
            printf("%d   ", tableauDeSommets[i]);
        }
        else if (tableauDeSommets[i] < 100)
        {
           printf("%d  ", tableauDeSommets[i]);
        }   
        else
        {
           printf("%d  ", tableauDeSommets[i]);
        }
        
        for (int j = 0; j < taille; j++)
        {
            if (liste[i][j] != 1)
            {
                red();
                printf("  %d  ", liste[i][j]);
                resetColor();
            }
            else
            {
                yellow();
                printf("  %d  ", liste[i][j]);
                resetColor();
            }
            
            /* printf("%d ", j); */
        }
        printf("\n\n");
    }
}
void afficherMatriceNormale(int **liste, int taille, int *tableauDeSommets)
{
    printf("     ");
    for (int j = 0; j < taille; j++)
    {
        
        if (tableauDeSommets[j] < 10)
        {
           printf("%d    ", tableauDeSommets[j]);
        }
        else
        {
           printf("%d   ", tableauDeSommets[j]);
        }   
    }
    printf("\n\n");
    for (int i = 0; i < taille; i++)
    {
        if (tableauDeSommets[i] < 10)
        {
            printf("%d  ", tableauDeSommets[i]);
        }
        else
        {
            printf("%d ", tableauDeSommets[i]);
        }
        
        for (int j = 0; j < taille; j++)
        {
            if (liste[i][j] != 0)
            {
                green();
                printf("  %d  ", liste[i][j]);
                resetColor();
            }
            else
            {
                red();
                printf("  %d  ", liste[i][j]);
                resetColor();
            }
            
            /* printf("%d ", j); */
        }
        printf("\n\n");
    }
}
