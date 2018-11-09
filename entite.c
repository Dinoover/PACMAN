#include "entite.h"


///Proédure de la détection de collision
void collision_pacman(t_pacman *pac, int mat[LARGEUR][HAUTEUR], int next_dep)
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

///Proédure de la détection de collision
void collision_fantome(t_fantome *fan, int mat[LARGEUR][HAUTEUR], int next_dep)
{
    if(fan->pos_x<=-1)    //sortie haute
    {
        fan->pos_x=HAUTEUR-1;
    }
    if(fan->pos_x>=HAUTEUR)  //sortie bas
    {
        fan->pos_x=0;
    }
    if(fan->pos_y<=-1)    //sortie gauche
    {
        fan->pos_y=LARGEUR-1;
    }
    if(fan->pos_y>=LARGEUR)  //sortie droite
    {
        fan->pos_y=0;
    }
    if(next_dep==1 && mat[fan->pos_x][fan->pos_y]==1)
    {
        fan->pos_y--;
    }
    if(next_dep==2 && mat[fan->pos_x][fan->pos_y]==1)
    {
        fan->pos_x--;
    }
    if(next_dep==3 && mat[fan->pos_x][fan->pos_y]==1)
    {
        fan->pos_y++;
    }
    if(next_dep==4 && mat[fan->pos_x][fan->pos_y]==1)
    {
        fan->pos_x++;
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
                collision_pacman(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement à droite
                printf("X");
                break;
            case 2:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_x++;
                collision_pacman(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement en bas
                printf("X");
                break;
            case 3:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_y--;
                collision_pacman(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement à gauche
                printf("X");
                break;
            case 4:
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY);
                printf(" ");
                pac->pos_x--;
                collision_pacman(pac,laby,next_dep);
                game_over=mort(pac,fan);
                gotoligcol(pac->pos_x+POSX,pac->pos_y+POSY); //deplacement en haut
                printf("X");
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

int deplacement_fantome(t_fantome *fan, t_pacman *pac,int laby[LARGEUR][HAUTEUR])
{
    color(ROUGE,NOIR);
    int game_over=0;
    int next_dep=rand()%4+1;
    switch(next_dep)
    {
        case 1:
            color(BLANC,NOIR);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
            if(laby[fan->pos_x][fan->pos_y]==3)
                    printf("o");
                else
                    printf(" ");
            fan->pos_y++;
            collision_fantome(fan,laby,next_dep);
            game_over=mort(pac,fan);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement à droite
            color(ROUGE,NOIR);
            printf("F");
            break;
        case 2:
            color(BLANC,NOIR);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
            if(laby[fan->pos_x][fan->pos_y]==3)
                    printf("o");
                else
                    printf(" ");
            fan->pos_x++;
            collision_fantome(fan,laby,next_dep);
            game_over=mort(pac,fan);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement en bas
            color(ROUGE,NOIR);
            printf("F");
            break;
        case 3:
            color(BLANC,NOIR);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
            if(laby[fan->pos_x][fan->pos_y]==3)
                    printf("o");
                else
                    printf(" ");
            fan->pos_y--;
            collision_fantome(fan,laby,next_dep);
            game_over=mort(pac,fan);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement à gauche
            color(ROUGE,NOIR);
            printf("F");
            break;
        case 4:
            color(BLANC,NOIR);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
            if(laby[fan->pos_x][fan->pos_y]==3)
                    printf("o");
                else
                    printf(" ");
            fan->pos_x--;
            collision_fantome(fan,laby,next_dep);
            game_over=mort(pac,fan);
            gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement en haut
            color(ROUGE,NOIR);
            printf("F");
            break;
        default:break;
    }

    return game_over;
}

int mort(t_pacman *pac, t_fantome *fan)
{
    int ded=0;

    if(pac->pos_x==fan->pos_x && pac->pos_y==fan->pos_y)
    {
        pac->vie--;
        pac->pos_x=1;
        pac->pos_y=1;
    }
    if(pac->vie==0)
    {
        gotoligcol(LARGEUR+POSX,HAUTEUR+POSY);
        color(ROUGE,NOIR);
        printf("VOUS ETES MORT");
        ded=-255;
    }

    return ded;
}
