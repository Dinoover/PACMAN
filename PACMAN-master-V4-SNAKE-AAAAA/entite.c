#include "entite.h"
/** CHANGELIST snake

    ajout des variables taille, oldx et oldy dans la struct pacman
    ajout de taille++ quand pacman mange gomme dans deplacement_pacman
    ajout de la fonction snake
    appel de snake dans le main au niveau de l'appel de déplacement pacman
*/


///Procédure de la détection de collision
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

///Procédure de la détection de collision
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
    int i;
    color(JAUNE,NOIR);

        pac->oldx = pac->pos_x;
        pac->oldy = pac->pos_y;

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
    default:
        break;
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
        pac->taille++;
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

///FONCTION DEPLACMENT LVL 3
int deplacement_fantome_lvl3(t_fantome *fan, t_pacman *pac,int laby[LARGEUR][HAUTEUR])
{
    color(ROUGE,NOIR);
    int game_over=0;
    int next_dep=0;
    //Les variables murs servent à déterminer si il y a un mur dans telle direction, si il n'y en pas alors elle est nulle
    int mur_haut = 0;
    int mur_droite = 0;
    int mur_gauche = 0;
    int mur_bas = 0;


    if(pac->pos_y > fan->pos_y)//pacman + à droite que le fan
    {
        //next dep devra etre diff de gauche
        mur_gauche = 3;
    }
    else if(pac->pos_y < fan->pos_y)//pacman + à gauche que le fan
    {
        //next dep devra etre diff de droite
        mur_droite =1;
    }
    if(pac->pos_x > fan->pos_x)//pacman + bas que le fan
    {
        //next dep devra etre diff de haut
        mur_haut=4;
    }
    else if(pac->pos_x < fan->pos_x)//pacman + haut que le fan
    {
        //next dep devra etre diff de bas
        mur_bas=2;
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


    if(pac->pos_x == fan->pos_x && pac->pos_y < fan->pos_y)
    {
        next_dep = 3;
    }

    else if(pac->pos_x == fan->pos_x && pac->pos_y > fan->pos_y)
    {
        next_dep=1;
    }

    else if(pac->pos_y == fan->pos_y && pac->pos_x < fan->pos_x)
    {
        next_dep = 4;
    }

    else if(pac->pos_y == fan->pos_y && pac->pos_x > fan->pos_x)
    {
        next_dep=2;
    }


    ///déplacement aléatoire
    else
    {
        do
        {
            next_dep=rand()%4+1;
        }//La valeur aléatoire sera toujours différente de la dir. du mur ou de 0
        while(next_dep == mur_bas || next_dep == mur_droite || next_dep == mur_gauche || next_dep == mur_haut);
    }

    fan->dir = next_dep;

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


int snake(t_pacman *pac, t_fantome *fan, int next_dep, int laby[LARGEUR][HAUTEUR])
{
    int i;
    int game_over=0;
    //tableau dynamique de pointeurs de pacman
    if(pac->taille !=0)
    {
        t_pacman ** tab_pac = malloc((pac->taille)+1 * sizeof(t_pacman*));
        if(tab_pac==NULL)//si l'alloc a échoué
        {
            exit(1);
        }

        /*  tentative en liste chainee

        t_pacman *curseur = NULL;
        t_pacman *pac_ajout = NULL;
        pac_ajout = malloc(sizeof(t_pacman));
        if(pac_ajout==NULL)//si l'alloc a échoué
        {
            exit(1);
        }
        else
        {
            pac_ajout->suiv=NULL;//car pac_ajout sera le dernier élément de la liste

            if(pac->taille!=0)
            {
                ///ajout en queue quand on mange un diamant
                curseur = pac;
                pac->suiv=pac_ajout;
                //On parcourt la liste jusqu'au dernier élément
                while(curseur !=NULL)
                {
                    curseur = curseur->suiv;
                }
                curseur = pac_ajout;
                game_over = deplacement_pacman(pac,fan,next_dep,laby);
                pac_ajout->pos_x = pac->oldx;
                pac_ajout->pos_y = pac->oldy;
                game_over = game_over +deplacement_pacman(pac_ajout,fan,next_dep,laby);

                free(pac_ajout);
            }*/

        else
        {
            tab_pac[0]= pac;//La tete est le pacman que nous dirigeons
            game_over = deplacement_pacman(tab_pac[0],fan,next_dep,laby);//la tete bouge (sa position précédente est sauvegardée)

            for(i=1; i<=pac->taille; i++)
            {
                tab_pac[i]->oldx = tab_pac[i]->pos_x;
                tab_pac[i]->oldy = tab_pac[i]->pos_y;
                tab_pac[i]->pos_x = tab_pac[i-1]->oldx;//On initialise les nouveaux membres à l'ancienne pos du précédent
                tab_pac[i]->pos_y = tab_pac[i-1]->oldy;

                /**
                    bug : tab_pac[0]->old x ou y est différent de pac -> old x ou y
                    or tab_pac[0] = pac
                */
                //affichage debug
                gotoligcol(tab_pac[i]->pos_x+POSX,tab_pac[i]->pos_y+POSY);
                printf("X");
                gotoligcol(25,40);
                printf("tab[%d] = x : %d, y : %d              ",i,tab_pac[i]->pos_x, tab_pac[i]->pos_y);
                gotoligcol(27,40);
                printf("tab[%d] = oldx : %d, oldy : %d        ",i-1, tab_pac[i-1]->oldx, tab_pac[i-1]->oldy);
            }
/*
            for(i=1; i<=pac->taille; i++)
                {
                    tab_pac[i]->oldx = tab_pac[i]->pos_x;
                    tab_pac[i]->oldy = tab_pac[i]->pos_y;

                    tab_pac[i]->pos_x = tab_pac[i-1]->oldx;
                    tab_pac[i]->pos_y = tab_pac[i-1]->oldy;
                }*/
                free(tab_pac);
        }
        }

    else if(pac->taille ==0)//si la taille de pacman est à 0 il se comporte comme le pacman des autres niveaux
    {
        game_over = deplacement_pacman(pac,fan,next_dep,laby);
    }

    gotoligcol(23,40);
    printf("%d", pac->taille);

    return game_over;
}
