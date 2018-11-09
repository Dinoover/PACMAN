#include "terrain.h"

///Fonction de lecture du fichier txt
int lecture(int mat[LARGEUR][HAUTEUR])
{
    int score_max=0;
    int i,j;
    FILE* fic;
    if ((fic = fopen("./default.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    for(i=0;i<LARGEUR;i++)
    {
        for(j=0;j<HAUTEUR;j++)
        {
            fscanf(fic,"%d",&mat[i][j]);
            if(mat[i][j]==3)
                score_max++;
        }
    }
    fclose(fic);
    return score_max;
}

///Procédure daffichage à l'écran
void affichage(int laby[LARGEUR][HAUTEUR], t_pacman *pac, t_fantome *fan)
{
    int i,j;
    //Terrain
    color(BLEU,NOIR);
    gotoligcol(POSX,POSY);
    for(i=0;i<LARGEUR;i++)
    {
        for(j=0;j<HAUTEUR;j++)
        {
            if(laby[i][j]==0)
                gotoligcol(i+POSX,j+1+POSY);

            //affichage des murs
            color(BLANC,BLEU);
            if(laby[i][j]==1)
                printf(" ");

            color(JAUNE,NOIR);
            if(laby[i][j]==2)   //position initiale de pacman
            {
                pac->pos_x=i;
                pac->pos_y=j;
                printf("X");
            }

            color(BLANC,NOIR);
            if(laby[i][j]==3)
                printf("o");

            color(BLEU,NOIR);

            if(laby[i][j]==4)
            {
                fan->pos_x=i;
                fan->pos_y=j;
                printf("F");
            }
        }
        gotoligcol(i+1+POSX,POSY);
    }
}
