#include "entite.h"

void gameplay(t_pacman* pac, t_fantome *fan, int delai, int bordures, int *level, int score);

void niveau_1(t_pacman* pac, t_fantome* fan, int laby[LARGEUR][HAUTEUR], int bordure);

void niveau_2(t_pacman *pac, t_fantome *fan, int laby[LARGEUR][HAUTEUR], int bordures);

void niveau_3(t_pacman *pac, t_fantome *fan, int laby[LARGEUR][HAUTEUR], int bordures);

void sauvegarde(int *level, int score);
