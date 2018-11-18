#include "menu.h"


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

void pause()
{
    int key;
    gotoligcol(10,40);
    color(NOIR,BLANC);
    printf("PAUSE");
    do
    {
        key=0;
        key=getch();

    }
    while(key!='p');

    gotoligcol(10,40);
    color(BLANC,NOIR);
    printf("     ");
}
