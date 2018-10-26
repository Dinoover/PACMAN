#include "console.h"

//Dimensions du labyrinthe
#define HAUTEUR 15
#define LARGEUR 15

#define POSX 5
#define POSY 5

///Entités pacman (joueur) et fantomes (IA)

typedef struct pacman
{
    int pos_x, pos_y; //position de pacman
    int dir; //direction de pacman
    int power_up;

}t_pacman;

typedef struct fantome
{
    int pos_x, pos_y;
    int dir;
    int vulne;
    int spawn;

}t_fantome;


void collision(t_pacman *pac, int mat[LARGEUR][HAUTEUR], int next_dep);

int deplacement_pacman(t_pacman *pac, t_fantome *fan, int next_dep, int laby[LARGEUR][HAUTEUR]);

int mort(t_pacman *pac, t_fantome *fan);
