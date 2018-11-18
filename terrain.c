#include "terrain.h"

///Fonction de lecture du fichier txt
int lecture(int mat[LARGEUR][HAUTEUR],t_pacman *pac, t_fantome *fan,int bordures, int nb_dia)
{
    int score_max=0; int posx_pac; int posy_pac; int posx_dia,posy_dia;
    int i,j;
    FILE* fic;
    if ((fic = fopen("./default.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }


    //reset du tableau
    for(i=0;i<LARGEUR;i++)
    {
        for(j=0;j<HAUTEUR;j++)
        {
            mat[i][j]=0;
        }
    }

    for(i=0;i<HAUTEUR;i++)
    {
        for(j=0;j<LARGEUR;j++)
        {
            fscanf(fic,"%d",&mat[j][i]);
            //if(mat[i][j]==3)
              //  score_max++;
        }
    }

    if(bordures==1) //LES BORDURES SONT ACTIVES / DIAMANTS ET PACMAN HORS DES MURS
    {
        for(i=0;i<LARGEUR;i++)
        {
            mat[i][0]=1;
            mat[i][HAUTEUR-1]=1;

        }
        for(j=0;j<HAUTEUR;j++)
        {
            mat[0][j]=1;
            mat[LARGEUR-1][j]=1;
        }

        //les diamants n'apparaissent pas sur les murs
        for(i=0;i<nb_dia;i++)
        {
            do
            {
                posx_dia=rand()%(HAUTEUR-2)+1;
                posy_dia=rand()%(LARGEUR-2)+1;

            }while(mat[posy_dia][posx_dia]!=0);

            mat[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas dans les bords et sur les diamants
        do
        {
            posx_pac=rand()%(18)+1;
            posy_pac=rand()%(48)+1;

        }while(mat[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        mat[posy_pac][posx_pac]=2;

        for(i=0;i<4;i++)
        {
            fan[i].pos_x=rand()%18+1;
            fan[i].pos_y=rand()%48+1;
        }

    }
    else    //BORDURES DESACTIVES
    {
        //les diamants apparaisent aléatoirement
        for(i=0;i<nb_dia;i++)
        {
            do  //PAS 2 DIAMANTS SUR LA MEME CASE
            {
                posx_dia=rand()%HAUTEUR+1;
                posy_dia=rand()%LARGEUR+1;

            }while(mat[posy_dia][posx_dia]!=0);

            mat[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas sur les diamants
        do
        {
            posx_pac=rand()%21;
            posy_pac=rand()%51;

        }while(mat[posy_pac][posx_pac]!=3);


        //position aléatoire de pacman
        mat[posy_pac][posx_pac]=2;

        for(i=0;i<4;i++)
        {
            fan[i].pos_x=rand()%21;
            fan[i].pos_y=rand()%51;
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
    for(i=0;i<HAUTEUR;i++)
    {
        for(j=0;j<LARGEUR;j++)
        {
            if(laby[j][i]==0)
                gotoligcol(i+POSX,j+1+POSY);

            //affichage des murs
            color(BLANC,BLEU);
            if(laby[j][i]==1)
                printf(" ");

            color(JAUNE,NOIR);
            if(laby[j][i]==2)   //position initiale de pacman
            {
                pac->pos_x=i;
                pac->pos_y=j;
                printf("X");
            }

            color(BLANC,NOIR);
            if(laby[j][i]==3)
            {
                printf("o");
            }

            color(BLEU,NOIR);

            if(laby[j][i]==4)
            {
                fan->pos_x=i;
                fan->pos_y=j;
                printf("F");
            }
            if(laby[j][i]==5)
            {
                color(BLANC,NOIR);
                printf("@");
            }
        }
        gotoligcol(i+1+POSX,POSY);
    }
}
