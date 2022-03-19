void yellow() {
  printf("\033[1;33m");
}
void red() {
  printf("\033[1;31m");
}
void resetColor()
{
    printf("\033[0m");
}
void afficherMatriceBooleenne(bool **liste, int taille)
{
    printf("\nAffichage de la matrice d'adjacence\n\n");
    printf("     ");
    for (int j = 0; j < taille; j++)
    {
        
        if (j < 9)
        {
           printf("%d    ", j+1);
        }
        else
        {
           printf("%d   ", j+1);
        }   
    }
    printf("\n\n");
    for (int i = 0; i < taille; i++)
    {
        if (i < 9)
        {
            printf("%d  ", i+1);
        }
        else
        {
            printf("%d ", i+1);
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
void afficherMatriceNormale(int **liste, int taille)
{
    printf("\nAffichage de la matrice des valeurs \n\n");
    printf("     ");
    for (int j = 0; j < taille; j++)
    {
        
        if (j < 9)
        {
           printf("%d    ", j+1);
        }
        else
        {
           printf("%d   ", j+1);
        }   
    }
    printf("\n\n");
    for (int i = 0; i < taille; i++)
    {
        if (i < 9)
        {
            printf("%d  ", i+1);
        }
        else
        {
            printf("%d ", i+1);
        }
        
        for (int j = 0; j < taille; j++)
        {
            if (liste[i][j] != 0)
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
