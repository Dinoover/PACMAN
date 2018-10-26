#include "entite.h"


///Proédure de la détection de collision
void collision(t_pacman *pac, int mat[LARGEUR][HAUTEUR], int next_dep)
{
    if(pac->pos_x<=-1)    //sortie haute
    {
        pac->pos_x=HAUTEUR-1;
    }
    if(pac->pos_x>=HAUTEUR)  //sortie bas
    {
        pac->pos_x=0;
    }
    if(pac->pos_y<=-1)    //sortie gauche
    {
        pac->pos_y=LARGEUR-1;
    }
    if(pac->pos_y>=LARGEUR)  //sortie droite
    {
        pac->pos_y=0;
    }
    if(next_dep==1 && mat[pac->pos_x][pac->pos_y]==1)
    {
        pac->pos_y--;
    }
    if(next_dep==2 && mat[pac->pos_x][pac->pos_y]==1)
    {
        pac->pos_x--;
    }
    if(next_dep==3 && mat[pac->pos_x][pac->pos_y]==1)
    {
        pac->pos_y++;
    }
    if(next_dep==4 && mat[pac->pos_x][pac->pos_y]==1)
    {
        pac->pos_x++;
    }
}

///Fonction de déplacement de pacman
int deplacement_pacman(t_pacman *pac, t_fantome *fan, int next_dep, int laby[LARGEUR][HAUTEUR])
{
    //Déplacement automatique dans une direction
        int game_over=0;
        color(JAUNE,NOIR);
        switch(next_dep)
        {
            case 1:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_y++;
                collision(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement à droite
                printf("O");
                break;
            case 2:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_x++;
                collision(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement en bas
                printf("O");
                break;
            case 3:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_y--;
                collision(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement à gauche
                printf("O");
                break;
            case 4:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_x--;
                collision(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement en haut
                printf("O");
                break;
            default:break;
        }

        //MIAM
        if(laby[pac->pos_x][pac->pos_y]==3)
        {
            game_over++;
            laby[pac->pos_x][pac->pos_y]=0;
        }

        return game_over;
}

int mort(t_pacman *pac, t_fantome *fan)
{
    int ded=0;

    if(pac->pos_x==fan->pos_x && pac->pos_y==fan->pos_y)
    {
        gotoligcol(LARGEUR+POSX,HAUTEUR+POSY);
        color(ROUGE,NOIR);
        printf("VOUS ETES MORT");
        ded=-255;
    }

    return ded;
}
