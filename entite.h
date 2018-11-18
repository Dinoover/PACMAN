#include "console.h"
#include <time.h>

//Dimensions du labyrinthe
#define HAUTEUR 20
#define LARGEUR 50

#define POSX 5
#define POSY 20

///Entités pacman (joueur) et fantomes (IA)

typedef struct pacman
{
    int pos_x, pos_y; //position de pacman
    int dir; //direction de pacman
    int power_up;
    int vie;

}t_pacman;

typedef struct fantome
{
    int pos_x, pos_y;
    int dir;
    int vulne;
    int spawn;

}t_fantome;


void collision_pacman(t_pacman *pac, int mat[LARGEUR][HAUTEUR], int next_dep);

int deplacement_pacman(t_pacman *pac, t_fantome *fan, int next_dep, int laby[LARGEUR][HAUTEUR]);

void collision_fantome(t_fantome *fan, int mat[LARGEUR][HAUTEUR], int next_dep);

//int deplacement_fantome(t_fantome *fan, t_pacman *pac, int laby[LARGEUR][HAUTEUR], int mode);

int deplacement_fantome(t_fantome *fan, t_pacman *pac,int laby[LARGEUR][HAUTEUR], int bordures);

int deplacement_fantome_lvl3(t_fantome *fan, t_pacman *pac,int laby[LARGEUR][HAUTEUR]);

int mort(t_pacman *pac, t_fantome *fan);




