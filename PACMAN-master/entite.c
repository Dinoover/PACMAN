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

        //MEGA GOMME
        if(laby[pac->pos_x][pac->pos_y]==5)
        {
            pac->power_up=1;
            laby[pac->pos_x][pac->pos_y]=0;//suppresion de l'objet de la case
        }

        //MIAM
        if(laby[pac->pos_x][pac->pos_y]==3)
        {
            game_over++;
            laby[pac->pos_x][pac->pos_y]=0;
        }

        return game_over;
}

///FONCTION DEPLACMENT LVL 2
int deplacement_fantome(t_fantome *fan, t_pacman *pac,int laby[LARGEUR][HAUTEUR], int bordures)
{
    color(ROUGE,NOIR);
    int game_over=0;
    int next_dep=0;
    //Les variables murs servent à déterminer si il y a un mur dans telle direction, si il n'y en pas alors elle est nulle
    int mur_haut = 0;
    int mur_droite = 0;
    int mur_gauche = 0;
    int mur_bas = 0;

    //Permet de garder la direction en mémoire
    if(fan->dir==0)
    {
        next_dep=rand()%4+1;
        fan->dir = next_dep;
    }

    if(laby[(fan->pos_x)-1][fan->pos_y]==1)//Si case au-dessus est un mur
    {
        mur_haut=4;
    }

    if(laby[(fan->pos_x)+1][fan->pos_y]==1)//Si case en-dessous est un mur
    {
        mur_bas = 2;
    }

    if(laby[(fan->pos_x)][(fan->pos_y)-1]==1)//Si case à gauche est un mur
    {
        mur_gauche = 3;
    }

    if(laby[(fan->pos_x)][(fan->pos_y)+1]==1)//Si case à droite est un mur
    {
        mur_droite = 1;
    }
    /*
    ///déplacement aléatoire
            do{
            next_dep=rand()%4+1;
            }while(next_dep == mur_bas || next_dep == mur_droite || next_dep == mur_gauche || next_dep == mur_haut);//La valeur aléatoire sera toujours différente de la dir. du mur ou de 0
    */

    switch(fan->dir)
    {
    case 1:
        color(BLANC,NOIR);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
        if(laby[fan->pos_x][fan->pos_y]==3)
            printf("o");
        else
            printf(" ");
        fan->pos_y++;
        collision_fantome(fan,laby,fan->dir);
        game_over=mort(pac,fan);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement à droite
        color(ROUGE,NOIR);
        printf("F");

        if(bordures !=0)
        {
            //Rebondissement
            if(mur_droite!=0)
            {
                fan->dir =3;
            }
        }
        break;
    case 2:
        color(BLANC,NOIR);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
        if(laby[fan->pos_x][fan->pos_y]==3)
            printf("o");
        else
            printf(" ");
        fan->pos_x++;
        collision_fantome(fan,laby,fan->dir);
        game_over=mort(pac,fan);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement en bas
        color(ROUGE,NOIR);
        printf("F");

        if(bordures !=0)
        {

            //Rebondissement
            if(mur_bas!=0)
            {
                fan->dir =4;
            }
        }
        break;
    case 3:
        color(BLANC,NOIR);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
        if(laby[fan->pos_x][fan->pos_y]==3)
            printf("o");
        else
            printf(" ");
        fan->pos_y--;
        collision_fantome(fan,laby,fan->dir);
        game_over=mort(pac,fan);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement à gauche
        color(ROUGE,NOIR);
        printf("F");
        if(bordures !=0)
        {
            //Rebondissement
            if(mur_gauche!=0)
            {
                fan->dir =1;
            }

        }
        break;
    case 4:
        color(BLANC,NOIR);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY);
        if(laby[fan->pos_x][fan->pos_y]==3)
            printf("o");
        else
            printf(" ");
        fan->pos_x--;
        collision_fantome(fan,laby,fan->dir);
        game_over=mort(pac,fan);
        gotoligcol(fan->pos_x+POSX,fan->pos_y+POSY); //deplacement en haut
        color(ROUGE,NOIR);
        printf("F");
        if(bordures !=0)
        {

            //Rebondissement
            if(mur_haut!=0)
            {
                fan->dir=2;
            }
        }
        break;
    default:
        break;
    }

    return game_over;
}

int mort(t_pacman *pac, t_fantome *fan)
{
    int ded=0;

    if(pac->pos_x==fan->pos_x && pac->pos_y==fan->pos_y && pac->power_up==0)
    {
        pac->vie--;
        pac->pos_x=1;
        pac->pos_y=1;
    }
    if(pac->pos_x==fan->pos_x && pac->pos_y==fan->pos_y && pac->power_up==1)//super pacman
    {
        fan->pos_x=1;
        fan->pos_y=1;
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
