#include <string.h>
#include <conio.h>
#include <time.h>
#include "console.h"
#include "terrain.h"

#define DELAY 10000

int main()
{
    int laby[LARGEUR][HAUTEUR];
    char key=0;
    int next_dep=0;
    int fin=0;
    int i, j;
    int score_max=0,game_over=0;

    t_pacman pac;
    t_fantome fan;

    score_max=lecture(laby);

    affichage(laby,&pac,&fan);

    ///Boule d'évènement
    while(fin!=1)
    {
        if(kbhit())
        {
            key=getch();

            switch(key)
            {
                case 'd':
                    next_dep=1;
                    break;
                case 's':
                    next_dep=2;
                    break;
                case 'q':
                    next_dep=3;
                    break;
                case 'z':
                    next_dep=4;
                    break;
                case 'y':
                    fin++;
                    break;
                default :
                    break;
            }
        }

        game_over=game_over+deplacement_pacman(&pac,&fan,next_dep,laby);

        if(game_over<0 || game_over==score_max)
            fin++;

        gotoligcol(20,70);
        printf("x = %d y = %d   score: %d  ",pac.pos_x,pac.pos_y,game_over);

        //delai
        for(i=0;i<DELAY;i++)
        {
            for(j=0;j<DELAY;j++);
        }
    }

    color(BLANC,NOIR);

    return 0;
}
