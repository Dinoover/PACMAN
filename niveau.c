#include "niveau.h"


///SAUVEGARDE DU TABLEAU ACTUEL
void sauvegarde(int *level, int score)
{
    FILE *fic=NULL;
    fic=fopen("./save.txt","w");
    if(fic==NULL)   //verification de l'ouverture
    {
        printf("Erreur ouverture");
        exit(1);
    }

    fprintf(fic,"%d\n%d",score,*level);

    fclose(fic);
}

void gameplay(t_pacman *pac, t_fantome *fan, int delai, int bordures, int* level, int score)
{
    int laby[LARGEUR][HAUTEUR]={0};
    int mode=0;
    int return_menu=0;  //retour au menu
    int fin=0;          //fin du tableau actuelle
    char key=0;
    int next_dep=0;
    int score_max=0,game_over=0;
    int t=0;
    int i,j;
    int score_tableau=0; //Score de la partie

    //*level=2;

    while(return_menu!=1)
    {
        //reset
        fin=0;
        for(i=0;i<4;i++)
            fan[i].dir=0;

        score=score+score_tableau;

        if(*level==0)
        {
            system("cls");
            score_max=5;
            niveau_1(pac,fan,laby,bordures);
            next_dep=rand()%4+1;    ///DEPLACEMNET ALEATOIRE DE DEPART
        }

        if(*level==1)
        {
            system("cls");
            game_over=0;
            score_max=5;
            niveau_2(pac,fan,laby,bordures);
            next_dep=rand()%4+1;    ///DEPLACEMNET ALEATOIRE DE DEPART
        }

        if(*level==2)
        {
            system("cls");
            game_over=0;
            score_max=5;
            niveau_3(pac,fan,laby,bordures);
            next_dep=rand()%4+1;
        }

        if(*level==3)   //fin de la partie retour au menu
        {
            return_menu++;
        }

        gotoligcol(2,20);
        color(NOIR,BLANC);
        printf(" NIVEAU %d ", *level+1);

        color(BLANC,NOIR);
        gotoligcol(2,40);
        printf("VIE : %d", pac->vie);
        gotoligcol(2,50);
        printf("SCORE : %d  ", score_tableau);


        //score_max=lecture(laby);
        affichage(laby,pac,fan);

        gotoligcol(0,0);printf("fan 1 : %d",fan[1].dir);

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
                case 'y':   ///RETOUR AU MENU
                    sauvegarde(level,score); //sauvegarde de la partie actuelle
                    fin++;
                    return_menu++;
                    break;
                case 'p': ///PAUSE
                    pause();
                    break;
                default :
                    break;
                }
            }

            game_over=game_over+deplacement_pacman(pac,fan,next_dep,laby);

            ///LVL 2
            if(*level==1)
            {
                for(i=0;i<4;i++)
                    game_over=game_over+deplacement_fantome(&fan[i],pac,laby,bordures);

            }

            ///LVL 3
            if(*level==2)
            {
                for(i=0;i<3;i++)
                    game_over=game_over+deplacement_fantome(&fan[i],pac,laby,bordures);

                ///FANTOME INTELLIGENT
                game_over=game_over+deplacement_fantome_lvl3(&fan[3],pac,laby);
            }

            //durée du power up
            if(pac->power_up==1)
            {
                t++;
                if(t==100)
                    pac->power_up=0;
            }

            if(game_over==score_max)    //TABLEAU COMPLETE / NIVEAU SUIVANT
            {
                score_tableau=game_over;
                *level=*level+1;
                fin++;
            }
            if(game_over<0) //GAME_OVER RETOUR AU MENU
            {
                fin++;
                return_menu++;
            }

            gotoligcol(2,40);
            color(BLANC,NOIR);
            printf("VIE : %d",pac->vie);

            gotoligcol(2,50);
            printf("SCORE : %d", score_tableau+(game_over*10));

            //debug info

            color(VERT,NOIR);
            gotoligcol(10,80);
            color(ROUGE,NOIR);
            printf("POINTS : %d    %d   ",score_tableau,score);
            gotoligcol(15,80);
            printf("pac_x = %d pac_y = %d ",pac->pos_x,pac->pos_y);
            gotoligcol(17,80);
            //printf("fan_x = %d fan_y = %d ",fan->pos_x,fan->pos_y);
            gotoligcol(19,80);
            printf("score = %d      vie = %d        t = %d",game_over,pac->vie,t);


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
        //reset
        pac->power_up=0;
    }
}

void niveau_1(t_pacman *pac, t_fantome *fan, int laby[LARGEUR][HAUTEUR], int bordures)
{
    int i,j;
    int posx_pac,posy_pac;  //position du pacman
    int posx_dia,posy_dia;  //position des diamants
    int score=0;    //score de la partie

    if(bordures==1) //LES BORDURES SONT ACTIVES / DIAMANTS ET PACMAN HORS DES MURS
    {
        for(i=0;i<LARGEUR;i++)
        {
            laby[i][0]=1;
            laby[i][HAUTEUR-1]=1;

        }
        for(j=0;j<HAUTEUR;j++)
        {
            laby[0][j]=1;
            laby[LARGEUR-1][j]=1;
        }

        //les diamants n'apparaissent pas sur les murs
        for(i=0;i<6;i++)
        {
            do
            {
                posx_dia=rand()%(HAUTEUR-2)+1;
                posy_dia=rand()%(LARGEUR-2)+1;

            }while(laby[posy_dia][posx_dia]!=0);

            laby[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas dans les bords et sur les diamants
        do
        {
            posx_pac=rand()%(18)+1;
            posy_pac=rand()%(48)+1;

        }while(laby[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        laby[posy_pac][posx_pac]=2;

    }
    else    //BORDURES DESACTIVES
    {
        //les diamants apparaisent aléatoirement
        for(i=0;i<6;i++)
        {
            do  //PAS 2 DIAMANTS SUR LA MEME CASE
            {
                posx_dia=rand()%HAUTEUR+1;
                posy_dia=rand()%LARGEUR+1;

            }while(laby[posy_dia][posx_dia]!=0);

            laby[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas sur les diamants
        do
        {
            posx_pac=rand()%21;
            posy_pac=rand()%51;

        }while(laby[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        laby[posy_pac][posx_pac]=2;
    }
}


void niveau_2(t_pacman *pac, t_fantome *fan, int laby[LARGEUR][HAUTEUR], int bordures)
{
    int i,j;
    int posx_pac,posy_pac;  //position du pacman
    int posx_dia,posy_dia;  //position des diamants
    int score=0;    //score de la partie

    fan->pos_x=2;
    fan->pos_y=2;

    //reset du tableau
    for(i=0;i<LARGEUR;i++)
    {
        for(j=0;j<HAUTEUR;j++)
        {
            laby[i][j]=0;
        }
    }

    if(bordures==1) //LES BORDURES SONT ACTIVES / DIAMANTS ET PACMAN HORS DES MURS
    {
        for(i=0;i<LARGEUR;i++)
        {
            laby[i][0]=1;
            laby[i][HAUTEUR-1]=1;

        }
        for(j=0;j<HAUTEUR;j++)
        {
            laby[0][j]=1;
            laby[LARGEUR-1][j]=1;
        }

        //les diamants n'apparaissent pas sur les murs
        for(i=0;i<6;i++)
        {
            do
            {
                posx_dia=rand()%(HAUTEUR-2)+1;
                posy_dia=rand()%(LARGEUR-2)+1;

            }while(laby[posy_dia][posx_dia]!=0);

            laby[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas dans les bords et sur les diamants
        do
        {
            posx_pac=rand()%(18)+1;
            posy_pac=rand()%(48)+1;

        }while(laby[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        laby[posy_pac][posx_pac]=2;

    }
    else    //BORDURES DESACTIVES
    {
        //les diamants apparaisent aléatoirement
        for(i=0;i<6;i++)
        {
            do  //PAS 2 DIAMANTS SUR LA MEME CASE
            {
                posx_dia=rand()%HAUTEUR+1;
                posy_dia=rand()%LARGEUR+1;

            }while(laby[posy_dia][posx_dia]!=0);

            laby[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas sur les diamants
        do
        {
            posx_pac=rand()%21;
            posy_pac=rand()%51;

        }while(laby[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        laby[posy_pac][posx_pac]=2;

    }
    for(i=0;i<4;i++)
    {
        fan[i].pos_x=rand()%21;
        fan[i].pos_y=rand()%51;
    }

}

void niveau_3(t_pacman *pac, t_fantome *fan, int laby[LARGEUR][HAUTEUR], int bordures)
{
    int i,j;
    int posx_pac,posy_pac;  //position du pacman
    int posx_dia,posy_dia;  //position des diamants
    int score=0;    //score de la partie

    fan->pos_x=2;
    fan->pos_y=2;

    //reset du tableau
    for(i=0;i<LARGEUR;i++)
    {
        for(j=0;j<HAUTEUR;j++)
        {
            laby[i][j]=0;
        }
    }

    if(bordures==1) //LES BORDURES SONT ACTIVES / DIAMANTS ET PACMAN HORS DES MURS
    {
        for(i=0;i<LARGEUR;i++)
        {
            laby[i][0]=1;
            laby[i][HAUTEUR-1]=1;

        }
        for(j=0;j<HAUTEUR;j++)
        {
            laby[0][j]=1;
            laby[LARGEUR-1][j]=1;
        }

        //les diamants n'apparaissent pas sur les murs
        for(i=0;i<6;i++)
        {
            do
            {
                posx_dia=rand()%(HAUTEUR-2)+1;
                posy_dia=rand()%(LARGEUR-2)+1;

            }while(laby[posy_dia][posx_dia]!=0);

            laby[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas dans les bords et sur les diamants
        do
        {
            posx_pac=rand()%(18)+1;
            posy_pac=rand()%(48)+1;

        }while(laby[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        laby[posy_pac][posx_pac]=2;

    }
    else    //BORDURES DESACTIVES
    {
        //les diamants apparaisent aléatoirement
        for(i=0;i<6;i++)
        {
            do  //PAS 2 DIAMANTS SUR LA MEME CASE
            {
                posx_dia=rand()%HAUTEUR+1;
                posy_dia=rand()%LARGEUR+1;

            }while(laby[posy_dia][posx_dia]!=0);

            laby[posy_dia][posx_dia]=3;  //génération des diamants
        }

        //pacman n'apparit pas sur les diamants
        do
        {
            posx_pac=rand()%21;
            posy_pac=rand()%51;

        }while(laby[posy_pac][posx_pac]!=3);

        //position aléatoire de pacman
        laby[posy_pac][posx_pac]=2;

    }
    for(i=0;i<4;i++)
    {
        fan[i].pos_x=rand()%21;
        fan[i].pos_y=rand()%51;
    }

}





