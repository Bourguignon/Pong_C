#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "pong.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

/*************************************************************************************************
BUT : Initialize le joueur
ENTREE : L'adresse du joueur
SORTIE : joueur init
*************************************************************************************************/

void InitJ1(raquette *J1){

    J1->w=30;
    J1->h=100;
    J1->pos.x=SCREEN_WIDTH-J1->w;
    J1->pos.y=(SCREEN_HEIGHT/2)-J1->h/2;
    J1->vitesse=10;
    J1->score=0;
}

/*************************************************************************************************
BUT : Initialize le joueur
ENTREE : L'adresse du joueur
SORTIE : joueur init
*************************************************************************************************/

void InitJ2(raquette *J2){

    J2->w=30;
    J2->h=100;
    J2->pos.x=0;
    J2->pos.y=(SCREEN_HEIGHT/2)-J2->h/2;
    J2->vitesse=10;
    J2->score=0;

}

/*************************************************************************************************
BUT : Reinitialize le joueur apres un point
ENTREE : L'adresse du joueur
SORTIE : joueur init
*************************************************************************************************/

void ReInitJ2(raquette *J2){

    J2->w=30;
    J2->h=100;
    J2->pos.x=0;
    J2->pos.y=(SCREEN_HEIGHT/2)-J2->h/2;
    J2->vitesse=10;

}

/*************************************************************************************************
BUT : Reinitialize le joueur apres un point
ENTREE : L'adresse du joueur
SORTIE : joueur init
*************************************************************************************************/

void ReInitJ1(raquette *J1){

    J1->w=30;
    J1->h=100;
    J1->pos.x=SCREEN_WIDTH-J1->w;
    J1->pos.y=(SCREEN_HEIGHT/2)-J1->h/2;
    J1->vitesse=10;

}

/*************************************************************************************************
BUT : Modifie les position raquette
ENTREE : Le gameState, les raquette et le tableau d'entier
SORTIE : position raquette
*************************************************************************************************/

void handleEvents(gameState *state,raquette *J1,raquette *J2,int key[]){


        if((key[1]==1)&&(VerifCollRaquette(J1)!=Haut)){
            J1->pos.y-=J1->vitesse;

        }else if((key[2]==1)&&(VerifCollRaquette(J1)!=Bas)){
            J1->pos.y+=J1->vitesse;
        }

        if((key[3]==1)&&(VerifCollRaquette(J2)!=Haut)){
            J2->pos.y-=J2->vitesse;

        }else if((key[4]==1)&&(VerifCollRaquette(J2)!=Bas)){
            J2->pos.y+=J2->vitesse;
        }

        if(key[0]==1){

            state->g_bRunning=0;
        }
}

/*************************************************************************************************
BUT : Recupere les entrés clavier
ENTREE : Le gameState, tableau d'entier
SORTIE : Input clavier
*************************************************************************************************/

void UpdateEvents(gameState *state,int key[]){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_SPACE:key[5]=1;break;
                                case SDLK_UP:key[1]=1;break;
                                case SDLK_DOWN:key[2]=1;break;
                                case SDLK_z:key[3]=1;break;
                                case SDLK_s:key[4]=1;break;
                                case SDLK_ESCAPE:key[0]=1;break;                            }
                            break;

        case SDL_KEYUP:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_UP:key[1]=0;break;
                                case SDLK_DOWN:key[2]=0;break;
                                case SDLK_z:key[3]=0;break;
                                case SDLK_s:key[4]=0;break;
                            }
                            break;
        default:break;

        }
    }
}

/*************************************************************************************************
BUT : Verifie la collision des raquette sur le bord de l'ecran
ENTREE : la raquette
SORTIE : Renvoi si la raquette collisionne avec le haut ou le bas
*************************************************************************************************/

int VerifCollRaquette(raquette *J1){

    if(J1->pos.y<=0){

        return Haut;
    }else if(J1->pos.y>=SCREEN_HEIGHT-J1->h){

        return Bas;
    }
    return 2;
}

/*************************************************************************************************
BUT : Gere le renvoi de la balle sur les raquette
ENTREE : la balle et les raquette
SORTIE : La balle change de direction si elle touche les raquettes
*************************************************************************************************/

int VerifRenvoiBalle(cercle *balle,raquette *J1,raquette *J2){

    if(((balle->pos.x-balle->rayon)<=(J2->pos.x+J2->w))
       &&((balle->pos.y+balle->rayon)<=J2->pos.y+J2->h)
       &&((balle->pos.y-balle->rayon)>=J2->pos.y)){

        balle->vitesse+=0.1;
        return Gauche;
    }else if(((balle->pos.x+balle->rayon)>=(J1->pos.x))
             &&((balle->pos.y+balle->rayon)<=J1->pos.y+J1->h)
             &&((balle->pos.y-balle->rayon)>=J1->pos.y)){

        balle->vitesse+=0.1;
        return Droite;
        //Gere le haut et le bas des raquette
    }
    if((balle->pos.x-balle->rayon)<=(J2->pos.x+J2->w)
            &&(balle->pos.x-balle->rayon)>=(J2->pos.x)
            &&(balle->pos.y+balle->rayon)>=(J2->pos.y)
            &&(balle->pos.y-balle->rayon)<=(J2->pos.y+J2->h)
            &&(balle->HautBas==0)){

        return GaucheHaut;
    }
    if((balle->pos.x-balle->rayon)<=(J2->pos.x+J2->w)
            &&(balle->pos.x-balle->rayon)>=(J2->pos.x)
            &&(balle->pos.y+balle->rayon)>=(J2->pos.y)
            &&(balle->pos.y-balle->rayon)<=(J2->pos.y+J2->h)
            &&(balle->HautBas==1)){

        return GaucheBas;
    }
    if((balle->pos.x+balle->rayon)>=(J1->pos.x)
            &&(balle->pos.x+balle->rayon)<=(J1->pos.x+J1->w)
            &&(balle->pos.y+balle->rayon)>=(J1->pos.y)
            &&(balle->pos.y-balle->rayon)<=(J1->pos.y+J1->h)
            &&(balle->HautBas==1)){

        return DroiteBas;
    }
    if((balle->pos.x+balle->rayon)>=(J1->pos.x)
            &&(balle->pos.x+balle->rayon)<=(J1->pos.x+J1->w)
            &&(balle->pos.y+balle->rayon)>=(J1->pos.y)
            &&(balle->pos.y-balle->rayon)<=(J1->pos.y+J1->h)
            &&(balle->HautBas==0)){

        return DroiteHaut;
    }
    return 0;
}

/*************************************************************************************************
BUT : Dessine une raquette
ENTREE : un game et une raquette
SORTIE : Affiche la raquette
*************************************************************************************************/

void DessineRaquette(game *myGame,raquette *joueur){

    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    rectangle.x=joueur->pos.x;//debut x
    rectangle.y=joueur->pos.y;//debut y
    rectangle.w=joueur->w; //Largeur
    rectangle.h=joueur->h; //Hauteur

    SDL_RenderFillRect(myGame->g_pRenderer,&rectangle);
}













