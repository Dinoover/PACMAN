#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define NOIR 0
#define BLEU_FONCE 1
#define VERT_FONCE 2
#define BLEU_GRIS 3
#define MARRON 4
#define POURPRE 5
#define KAKI 6
#define GRIS_CLAIR 7
#define GRIS 8
#define BLEU 9
#define VERT 10
#define TURQUOISE 11
#define ROUGE 12
#define ROSE 13
#define JAUNE 14
#define BLANC 15

void color(int couleurDuTexte,int couleurDeFond);

void gotoligcol( int lig, int col );

void title();
