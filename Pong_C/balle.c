#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "pong.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780


/*************************************************************************************************
BUT : Initialize la balle
ENTREE : L'adresse de la balle
SORTIE : balle init
*************************************************************************************************/

void InitBalle(cercle *balle){

    balle->pos.x=SCREEN_WIDTH/2;
    balle->pos.y=SCREEN_HEIGHT/2;
    balle->vitesse=5;
    balle->rayon=15;
    balle->HautBas=rand()%2;
    balle->GaucheDroite=rand()%2;
}

/*************************************************************************************************
BUT : Dessine une balle
ENTREE : un game et une balle
SORTIE : Affiche la raquette
*************************************************************************************************/

void DessineCercle(game *myGame,cercle *balle){

int d, y, x;

  d = 3 - (2 * balle->rayon);
  x = 0;
  y = balle->rayon;

    while(y>=x){

        SDL_Rect r;

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        r.x = balle->pos.x - x;
        r.y = balle->pos.y - y;
        r.w = 2 * x + 1;
        r.h = 1;

        SDL_RenderFillRect(myGame->g_pRenderer,&r);

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        r.x = balle->pos.x - x;
        r.y = balle->pos.y + y;
        r.w = 2 * x + 1;
        r.h = 1;

        SDL_RenderFillRect(myGame->g_pRenderer,&r);

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        r.x = balle->pos.x - y;
        r.y = balle->pos.y - x;
        r.w = 2 * y + 1;
        r.h = 1;

        SDL_RenderFillRect(myGame->g_pRenderer,&r);

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        r.x = balle->pos.x - y;
        r.y = balle->pos.y + x;
        r.w = 2 * y + 1;
        r.h = 1;

        SDL_RenderFillRect(myGame->g_pRenderer,&r);

        if (d < 0)
        d = d + (4 * x) + 6;
        else {
        d = d + 4 * (x - y) + 10;
        y--;
        }
        x++;
    }
}

/*************************************************************************************************
BUT : Deplace la balle
ENTREE : la balle
SORTIE : La balle se deplace
*************************************************************************************************/

void DeplaceBalle(cercle *balle,raquette *J1,raquette *J2){

int i;

    if(balle->HautBas==0){
        balle->pos.y+=balle->vitesse+balle->modif;
    }else if(balle->HautBas==1){
        balle->pos.y-=balle->vitesse-balle->modif;
    }

    if(balle->GaucheDroite==0){
        balle->pos.x+=balle->vitesse;
            for(i=0;i<J2->h;i++){
                if((balle->pos.y-balle->rayon)-(SCREEN_HEIGHT-J2->h)+((SCREEN_HEIGHT-J2->h+J2->pos.y))==i){
                    balle->modif=i/20;
                }
            }
    }else if(balle->GaucheDroite==1){
        balle->pos.x-=balle->vitesse;
            for(i=0;i<J1->h;i++){
                if((balle->pos.y+balle->rayon)-(SCREEN_HEIGHT-J1->h)+((SCREEN_HEIGHT-J1->h+J1->pos.y))==i){
                    balle->modif=i/20;
                }
            }
    }
}

/*************************************************************************************************
BUT : Gere la direction de la balle
ENTREE : la balle et les raquette
SORTIE : La balle change de direction si elle touche les raquette ou le bord de l'ecran
*************************************************************************************************/

void DirectionBalle(cercle *balle,raquette *J1,raquette *J2){

    if((VerifCollEcran(balle)==Haut)
    ||(VerifRenvoiBalle(balle,J1,J2)==GaucheBas)
    ||(VerifRenvoiBalle(balle,J1,J2)==DroiteBas)){

        balle->HautBas=0;
    }else if((VerifCollEcran(balle)==Bas)
    ||(VerifRenvoiBalle(balle,J1,J2)==GaucheHaut)
    ||(VerifRenvoiBalle(balle,J1,J2)==DroiteHaut)){

        balle->HautBas=1;
    }else if(VerifRenvoiBalle(balle,J1,J2)==Gauche){

        balle->GaucheDroite=0;
    }else if(VerifRenvoiBalle(balle,J1,J2)==Droite){

        balle->GaucheDroite=1;
    }
}

/*************************************************************************************************
BUT : Verifie la sortie de l'ecran
ENTREE : Des coordonne
SORTIE : Le coté de l'ecran ou l'objet est sortie
*************************************************************************************************/

int VerifCollEcran(cercle *balle){

    if(balle->pos.y<=0+balle->rayon){

        return Haut;
    }else if(balle->pos.y>=SCREEN_HEIGHT-balle->rayon){

        return Bas;
    }else if(balle->pos.x<=0+balle->rayon){

        return Gauche;
    }else if(balle->pos.x>=SCREEN_WIDTH-balle->rayon){

        return Droite;
    }
    return 4;
}

/*************************************************************************************************
BUT : Gere le score
ENTREE : la balle et les raquette
SORTIE : incremente le score si la balle sort de l'ecran
*************************************************************************************************/

void GestScore(cercle *balle,raquette *J1,raquette *J2,int key[]){

    if(VerifCollEcran(balle)==Gauche){
        J1->score+=1;
        ReInitJ1(J1);
        ReInitJ2(J2);
        InitBalle(balle);
        key[5]=0;
    }else if(VerifCollEcran(balle)==Droite){
        J2->score+=1;
        ReInitJ1(J1);
        ReInitJ2(J2);
        InitBalle(balle);
        key[5]=0;
    }
}
