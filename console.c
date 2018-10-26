#include "console.h"

///Procédure de changement de couleur de la console
void color(int couleurDuTexte,int couleurDeFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

///Procédure de deplacement du curseur à l'écran
void gotoligcol( int lig, int col )
{
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
