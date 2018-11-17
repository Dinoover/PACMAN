#include "terrain.h"

///Fonction de lecture du fichier txt
int lecture(int mat[LARGEUR][HAUTEUR] /*int terrain, int nombre_diamants*/)
{

    int score_max=0;
    int i,j,k;
/*
    for(i=0;i<LARGEUR;i++)
    {
        for(j=0;j<HAUTEUR;j++)
        {
            mat[i][j]=0;//met des 0 sur toute la surface

            if(i==0 || j == 0 || i == LARGEUR-1 || j == HAUTEUR-1)//Crée les murs représentés par les 1
            {
                mat[i][j]=1;
            }
        }
    }
    //On a donc une matrice composée de 0 et encadrée par des 1

    //Positionnement des diamants
    for(k=0;k<nombre_diamants;k++)
    {
           do
            {
                i = rand()%(LARGEUR-1)+1;
                j = rand()%(HAUTEUR-1)+1;
            }while(mat[i][j]!=0);

           mat[i][j]=3;
    }

    //Positionnement de pacman
    do
    {
        i = rand()%(LARGEUR-1)+1;
        j = rand()%(HAUTEUR-1)+1;
    }while(mat[i][j]!=0);

    mat[i][j]=2;

    if(terrain == 2 || terrain == 3)//car fantomes présents uniquement dans terrains 2 et 3
    {
        //Positionnement des fantomes
        for(k=0;k<4;k++)
        {
            do
                {
                    i = rand()%(LARGEUR-1)+1;
                    j = rand()%(HAUTEUR-1)+1;
                }while(mat[i][j]!=0);
                mat[i][j]=4;
        }
    }

    //Positionnement de la super gomme
     do
            {
                i = rand()%(LARGEUR-1)+1;
                j = rand()%(HAUTEUR-1)+1;
            }while(mat[i][j]!=0);
            mat[i][j]=5;

    score_max = nombre_diamants;
    return score_max;
*/
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
void affichage(int laby[LARGEUR][HAUTEUR], t_pacman *pac, t_fantome fan[4])
{
    int i,j;
    int compteur =0;
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



            ///TABLEAU DE FANTOMES
            if(laby[i][j]==4)
            {
                    color(ROUGE,NOIR);
                    fan[compteur].pos_x=i;
                    fan[compteur].pos_y=j;
                    if(compteur==3)
                    {
                        color(TURQUOISE, NOIR);
                    }
                    printf("F");

                    //Le compteur sert à voir quel fantome est deja présent sur le terrain, le rang du compteur correspond au rang du prochain fantome dans le tableau qui apparaitra
                    compteur++;
            }

            if(laby[i][j]==5)
            {
                color(BLANC,NOIR);
                printf("@");
            }
        }
        gotoligcol(i+1+POSX,POSY);
    }
}

void niveau1(t_pacman *pac)
{
   //int tab[]
}
