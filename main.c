#include <string.h>
#include <conio.h>
#include "console.h"
#include "terrain.h"

#define DELAY 8000

int main(int argc, char *argv[])
{
    int laby[LARGEUR][HAUTEUR];
    char key=0;
    int next_dep=0;
    int fin=0;
    int i, j;
    int score_max=0,game_over=0;

    t_pacman pac;
    t_fantome fan;

    srand(time(NULL));

    score_max=lecture(laby);

    affichage(laby,&pac,&fan);

    pac.vie=3;

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
        game_over=game_over+deplacement_fantome(&fan,&pac,laby);

        if(game_over<0 || game_over==score_max)
            fin++;

        //debug info
        color(VERT,NOIR);
        gotoligcol(15,40);
        printf("pac_x = %d pac_y = %d ",pac.pos_x,pac.pos_y);
        gotoligcol(17,40);
        printf("fan_x = %d fan_y = %d ",fan.pos_x,fan.pos_y);
        gotoligcol(19,40);
        printf("score = %d      vie = %d",game_over,pac.vie);

        title();

        //delai
        for(i=0;i<DELAY;i++)
        {
            for(j=0;j<DELAY;j++);
        }
    }

    gotoligcol(20,10);
    color(BLANC,NOIR);

    return 0;
}
