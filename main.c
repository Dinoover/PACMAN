#include "console.h"
#include "menu.h"
#include "niveau.h"

int chargement(int *level)
{
    int score=0;
    FILE *fic=NULL;
    fic=fopen("./save.txt","r");
    if(fic==NULL)
    {
        printf("Erreur ouverture fichier");
        exit(1);
    }

    fscanf(fic,"%d",&score);
    fscanf(fic,"%d",&(*level));

    fclose(fic);
    return score;
}

int main(int argc, char *argv[])
{
    //*********DECLARATION DES VARIABLES*************//

    char key=0;     //variable contenant la touche du clavier pressé
    int x=8,y=45;   //position du curseur
    int choix=0;    //choix de l'utlisateur dans le menu
    int select=0;   //selection du choix
    int level=0;    //level actuelle du jeu
    int score=0;    //score de la partie
    int i;

    ///BORDURES ET VITESSES
    int delai=3;    //cadence du jeu par default
    int bordures=0; //bordure de la map

    //création des entités joueurs et ennemis
    t_pacman pac;
    t_fantome fan[4];


    for(i=0 ; i<4 ; i++)
    {
        fan[i].dir = 0;
    }

    pac.vie=5;  ///PACMAN initialise à 5 vie
    pac.power_up=0;

    //************************************************//

    srand(time(NULL));  //initialisation de l'aleatoire

    title();    ///affichage de l'écran titre + noms de l'équipe

    //appuyer sur une touche pour continuer
    while(!kbhit());
    system("cls");

    menu(); //affichege du menu de sélection

    while(select!=1)
    {
        if(kbhit())
        {
            key=getch();

            Beep(1000,50);  //bruitage

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

                //selection du menu
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
                case 2: //NEW GAME
                    pac.vie=5;
                    system("cls");
                    level=0;
                    score=0;
                    gameplay(&pac,fan,delai,bordures,&level,&score);
                    system("cls");
                    choix=0;
                    color(BLANC,NOIR);
                    menu();
                    break;
                case 3: //CONTINUE
                    pac.vie=5; ///REGAIN DES PV DU PACMAN
                    system("cls");
                    score=chargement(&level);   //Chargement du niveau en cours
                    gameplay(&pac,fan,delai,bordures,&level,&score);
                    system("cls");
                    choix=0;
                    color(BLANC,NOIR);
                    menu();
                    break;
                case 4: //EXIT
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

    gotoligcol(20,10);
    color(BLANC,NOIR);

    return 0;
}
