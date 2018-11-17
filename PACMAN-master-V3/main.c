#include <string.h>
#include <conio.h>
#include "console.h"
#include "terrain.h"


void menu()
{
    ///menu
    int x=8,y=45;
    int i;
    gotoligcol(x,y);
    printf("%c",201); //coin haut gauche
    for(i=0; i<30; i++) //bordure haute
        printf("%c",205);
    printf("%c",187); //coin haut droit
    for(i=0; i<9; i++) //bordure gauche et droite
    {
        gotoligcol(x+i+1,y);
        printf("%c",186);
        gotoligcol(x+i+1,y+30+1);
        printf("%c",186);
    }
    gotoligcol(i+x+1,y);
    printf("%c",200);   //coin bas gauche
    for(i=0; i<30; i++)
        printf("%c",205);
    printf("%c",188);

    gotoligcol(x+3,y+8);
    printf("Regles du jeu");
    gotoligcol(x+4,y+8);
    printf("Options");
    gotoligcol(x+5,y+8);
    printf("Nouvelle partie");
    gotoligcol(x+6,y+8);
    printf("Reprendre partie");
    gotoligcol(x+7,y+8);
    printf("Quitter");
    gotoligcol(x+3,y+5);
    printf(">");

}

void options(int *vitesse, int *bordures)
{
    int choix=0;    //
    int select=0;   //
    int key;

    int x=8,y=45;
    gotoligcol(x+3,y+8);
    printf("Vitesse : 1 2 3");
    gotoligcol(x+4,y+8);
    printf("Bordures : ON OFF   ");
    gotoligcol(x+5,y+8);
    printf("Retour                 ");
    gotoligcol(x+6,y+8);
    printf("                    ");
    gotoligcol(x+7,y+8);
    printf("             ");

    //SURLIGNER LE MODE ACTUELLE
    if(*vitesse==1)
    {
        gotoligcol(x+3,y+18);
        color(NOIR,BLANC);
        printf("1");
        color(BLANC,NOIR);
    }
    if(*vitesse==2)
    {
        gotoligcol(x+3,y+20);
        color(NOIR,BLANC);
        printf("2");
        color(BLANC,NOIR);
    }
    if(*vitesse==3)
    {
        gotoligcol(x+3,y+22);
        color(NOIR,BLANC);
        printf("3");
        color(BLANC,NOIR);
    }
    if(*bordures==1)
    {
        gotoligcol(x+4,y+19);
        color(NOIR,BLANC);
        printf("ON");
        color(BLANC,NOIR);
    }
    if(*bordures==0)
    {
        gotoligcol(x+4,y+22);
        color(NOIR,BLANC);
        printf("OFF");
        color(BLANC,NOIR);
    }

    gotoligcol(x+4,y+5);
    printf(" ");
    gotoligcol(x+3,y+5);
    printf(">");

    while(select!=1)
    {
        if(kbhit())
        {
            key=getch();
            Beep(200,50);

            switch(key)
            {
            case 's' :
                choix++;
                if(choix>2)
                {
                    choix--;
                }
                else
                {
                    gotoligcol(x+3+choix-1,y+5);
                    printf(" ");
                    gotoligcol(x+3+choix,y+5);
                    printf(">");
                }
                break;
            case 'z' :
                choix--;
                if(choix<0)
                {
                    choix++;
                }
                else
                {
                    gotoligcol(x+3+choix+1,y+5);
                    printf(" ");
                    gotoligcol(x+3+choix,y+5);
                    printf(">");
                }
                break;
            case 'd':
                switch(choix)
                {
                case 0:
                    if(*vitesse==1)
                        *vitesse=*vitesse+1;
                    else if(*vitesse==2)
                        *vitesse=*vitesse+1;
                    else if(*vitesse==3)
                        *vitesse=1;

                    //SURLIGNER LE MODE ACTUELLE
                    if(*vitesse==1)
                    {
                        gotoligcol(x+3,y+18);
                        color(NOIR,BLANC);
                        printf("1");
                        color(BLANC,NOIR);
                        gotoligcol(x+3,y+22);
                        printf("3");
                    }
                    if(*vitesse==2)
                    {
                        gotoligcol(x+3,y+20);
                        color(NOIR,BLANC);
                        printf("2");
                        color(BLANC,NOIR);
                        gotoligcol(x+3,y+18);
                        printf("1");
                    }
                    if(*vitesse==3)
                    {
                        gotoligcol(x+3,y+22);
                        color(NOIR,BLANC);
                        printf("3");
                        color(BLANC,NOIR);
                        gotoligcol(x+3,y+20);
                        printf("2");
                    }
                    gotoligcol(x+3+choix,y+5);
                    printf(">");
                    break;
                case 1:
                    if(*bordures==0)
                        *bordures=*bordures+1;
                    else if(*bordures==1)
                        *bordures=0;
                    if(*bordures==1)
                    {
                        gotoligcol(x+4,y+19);
                        color(NOIR,BLANC);
                        printf("ON");
                        color(BLANC,NOIR);
                        gotoligcol(x+4,y+22);
                        printf("OFF");
                    }
                    if(*bordures==0)
                    {
                        gotoligcol(x+4,y+22);
                        color(NOIR,BLANC);
                        printf("OFF");
                        color(BLANC,NOIR);
                        gotoligcol(x+4,y+19);
                        printf("ON");
                    }
                    gotoligcol(x+3+choix,y+5);
                    printf(">");
                    break;
                case 2:
                    select++;
                    break;
                default:
                    break;
                }

            default:
                break;
            }
        }
    }
}

void affichage_regles()
{
    FILE* fic=NULL;
    char c;
    fic=fopen("./doc.txt","r");
    if(fic!=NULL)
    {
        while(c!=EOF)
        {
            c=fgetc(fic);
            printf("%c",c);
        }
    }
    else
    {
        exit(1);
    }

    fclose(fic);

    color(NOIR,BLANC);
    printf("\nAppuyer sur une touche pour continuer");
    color(BLANC,NOIR);

    while(!kbhit());
}


int main(int argc, char *argv[])
{
    int laby[LARGEUR][HAUTEUR];
    char key=0;
    int x=8,y=45;
    int next_dep=0;
    int fin=0;
    int return_menu=0;
    int i, j;
    int score_max=0,game_over=0;
    int t=0;

    int choix=0;
    int select=0;

    int terrain = 3;///VARIABLE QUI CHOISIT LE NUMERO DU TERRAIN (A METTRE DANS UN PROG)
    int nombre_diamants = 5;

    ///BORDURES ET VITESSES
    int delai=1;//cadence du jeu par default
    int bordures=1; //bordure de la map

    t_pacman pac;
    t_fantome fan[4];


    for(i=0 ; i<4 ; i++)
    {
        fan[i].dir = 0;
    }

    srand(time(NULL));

    pac.vie=5;  ///PACMAN initialise à 5 vies
    pac.power_up=0;

    title();    ///affichage de l'écran titre + noms de l'équipe

    //appuyer sur une touche pour continuer
    while(!kbhit());
    fin=0;
    system("cls");

    menu();

    while(select!=1)
    {
        if(kbhit())
        {
            key=getch();

            Beep(1000,50);

            switch(key)
            {
            case 's' :
                choix++;
                if(choix>4)
                {
                    choix--;
                }
                else
                {
                    gotoligcol(x+3+choix-1,y+5);
                    printf(" ");
                    gotoligcol(x+3+choix,y+5);
                    printf(">");
                }
                break;
            case 'z' :
                choix--;
                if(choix<0)
                {
                    choix++;
                }
                else
                {
                    gotoligcol(x+3+choix+1,y+5);
                    printf(" ");
                    gotoligcol(x+3+choix,y+5);
                    printf(">");
                }
                break;
            case 'd':
                switch(choix)
                {
                case 0:
                    gotoligcol(0,0);
                    system("cls");
                    affichage_regles();
                    system("cls");
                    menu();
                    break;
                case 1:
                    options(&delai,&bordures);
                    system("cls");
                    menu();
                    gotoligcol(x+3,y+5);
                    printf(" ");
                    gotoligcol(x+4,y+5);
                    printf(">");
                    break;
                case 2:
                    select=1;
                    system("cls");
                    break;
                case 4:
                    fin=1;
                    select=1;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }

    if(fin!=1)//jeu lancé
    {
        score_max=lecture(laby/*,terrain,nombre_diamants*/);
        affichage(laby,&pac,fan);
    }

    //Boule d'évènement
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

        game_over=game_over+deplacement_pacman(&pac,fan,next_dep,laby);

        if(terrain==3)
        {

            for(i=0 ; i<3 ; i ++)
            {
                game_over=game_over+deplacement_fantome(&fan[i],&pac,laby,bordures);
            }
            game_over=game_over+deplacement_fantome_lvl3(&fan[3],&pac,laby);

        }

        //Si on est dans le terrain 2 ou 3 (il n'y a pas de fantomes dans 1 et 4)
        if(terrain ==2)
        {
            for(i=0 ; i<4 ; i ++)
            {
                game_over=game_over+deplacement_fantome(&fan[i],&pac,laby,bordures);
            }
        }

        //durée du power up
        if(pac.power_up==1)
        {
            t++;
            if(t==100)
                pac.power_up=0;
        }

        if(game_over<0 || game_over==score_max)
            fin++;

        //debug info
        color(VERT,NOIR);
        gotoligcol(15,40);
        printf("pac_x = %d pac_y = %d ",pac.pos_x,pac.pos_y);
        gotoligcol(17,40);
        printf("fan_x = %d fan_y = %d ",fan[3].pos_x,fan[3].pos_y);
        gotoligcol(19,40);
        printf("score = %d      vie = %d        t = %d",game_over,pac.vie,t);

        //delai

        if(delai==1)
            delai=12000;
        if(delai==2)
            delai=10000;
        if(delai==3)
            delai=8000;

        for(i=0; i<delai; i++)
        {
            for(j=0; j<delai; j++);
        }
    }

    gotoligcol(20,10);
    color(BLANC,NOIR);

   // free(fan);
    return 0;
}
