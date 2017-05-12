#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>
#include "pong.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780


//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32

/*************************************************************************************************
BUT : Jeux Pong
ENTREE : ZS (Raquette gauche) Haut bas (raquette droite) espace (lance la partie et la reprendre apres un point) et echap (sortir)
SORTIE :
*************************************************************************************************/

int main(int argc, char *argv[])
{

    game myGame;
    gameState state;
    font mFont;


    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;

    raquette J1,J2;
    cercle balle;
    int key[6]={0,0,0,0,0,0};

    if(init("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame,&mFont)){
                state.g_bRunning=1;
    }else{
        return 1;//something's wrong
    }

    //Create texture for drawing in texture or load picture
    myGame.g_texture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
    InitJ1(&J1);
    InitJ2(&J2);
    InitBalle(&balle);

    while(state.g_bRunning){

            SDL_SetRenderDrawColor(myGame.g_pRenderer,0,0,0,255);
            SDL_RenderClear(myGame.g_pRenderer);

            DessineRaquette(&myGame,&J1);
            DessineRaquette(&myGame,&J2);
            DessineCercle(&myGame,&balle);
            SDL_RenderDrawLine(myGame.g_pRenderer,SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);

            writeSDL(&myGame,mFont,&J1,&J2);

            UpdateEvents(&state,key);

            if(key[5]==1){
                handleEvents(&state,&J1,&J2,key);

                DirectionBalle(&balle,&J1,&J2);
                DeplaceBalle(&balle,&J1,&J2);
            }

            GestScore(&balle,&J1,&J2,key);

            // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;

            SDL_RenderPresent(myGame.g_pRenderer); // Affichage

            if((J1.score==10)||(J2.score==10)){

                state.g_bRunning=0;
            }

    }

         destroy(&myGame,&mFont);

         TTF_Quit();
         SDL_Quit();

  return 0;
}


