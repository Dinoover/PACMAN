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

void title()
{
    color(JAUNE,NOIR);
    gotoligcol(3,30);
    printf(" _______       _         ______    ___      ___        _        ___     _");
    gotoligcol(4,30);
    printf("|  ___  |     / \\       /  ____|  |   \\    /   |      / \\      |   \\   | |");
    gotoligcol(5,30);
    printf("| |___| |    / _ \\     |  /       | |\\ \\  / /| |     / _ \\     | |\\ \\  | |");
    gotoligcol(6,30);
    printf("|  _____|   / /_\\ \\    | |        | | \\ \\/ / | |    / /_\\ \\    | | \\ \\ | |");
    gotoligcol(7,30);
    printf("| |        / _____ \\   |  \\____   | |  \\__/  | |   / _____ \\   | |  \\ \\| | ");
    gotoligcol(8,30);
    printf("|_|       /_/     \\_\\   \\______|  |_|        |_|  /_/     \\_\\  |_|   \\___|");

    color(ROUGE,NOIR);
    gotoligcol(15,10);
    printf("MILETIC Petar");
    gotoligcol(16,10);
    printf("LASOU Guillaume");
    gotoligcol(17,10);
    printf("JULLEMIER Arnaud");

    color(NOIR,BLANC);
    gotoligcol(20,20);
    printf("Appuyer sur une touche pour continuer");
    color(BLANC,NOIR);
}
