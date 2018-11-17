#include "console.h"
#include <time.h>

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
    int vie;

}t_pacman;

typedef struct fantome
{
    int pos_x, pos_y;
    int dir;
    int vulne;
    int spawn;
    int vivant;//Booléen qui sera faux (0) lorsque le fantome n'est pas à l'écran, vrai (1) sinon

}t_fantome;


void collision_pacman(t_pacman *pac, int mat[LARGEUR][HAUTEUR], int next_dep);

int deplacement_pacman(t_pacman *pac, t_fantome *fan, int next_dep, int laby[LARGEUR][HAUTEUR]);

void collision_fantome(t_fantome *fan, int mat[LARGEUR][HAUTEUR], int next_dep);

int deplacement_fantome(t_fantome *fan, t_pacman *pac, int laby[LARGEUR][HAUTEUR], int bordures);

int mort(t_pacman *pac, t_fantome *fan);

void niveau1(t_pacman* pac);
