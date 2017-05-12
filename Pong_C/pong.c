#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "pong.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

/*************************************************************************************************
BUT : Initialize la SDL et la ttf
ENTREE : Le titre de la fenetre, la position, taille et
SORTIE : SDL et ttf initializer
*************************************************************************************************/

int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame, font *mFont){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);
            }
    }else{
        return 0;
    }
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    mFont->g_font=TTF_OpenFont("./assets/fonts/American/American Captain.ttf",65);

    return 1;
}

/*************************************************************************************************
BUT : Ecrit dans la surface
ENTREE : La fenetre et la police
SORTIE : Affiche le texte dans la fenetre
*************************************************************************************************/

void writeSDL(game *myGame,font mFont,raquette *J1,raquette *J2) {

char score[] ="";


        sprintf(score,"%i - %i",J2->score,J1->score);

        SDL_Color fontColor={255,255,255};

        myGame->g_surface=TTF_RenderText_Blended(mFont.g_font, score, fontColor);//Charge la police

        if(myGame->g_surface){


                //Définition du rectangle dest pour blitter la chaine
                SDL_Rect rectangle;
                rectangle.x=(SCREEN_WIDTH/2)-100;//debut x
                rectangle.y=(SCREEN_HEIGHT/2)-350;//debut y
                rectangle.w=200; //Largeur
                rectangle.h=100; //Hauteur


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation de la texture pour la chaine
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                 if(myGame->g_texture){

                        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,NULL,&rectangle); // Copie du sprite grâce au SDL_Renderer
                 }
                 else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de creation surface pour chaine (%s)\n",SDL_GetError());
        }
}

/*************************************************************************************************
BUT : Limite les fps
ENTREE : la frameLimit
SORTIE :
*************************************************************************************************/

void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks+16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}



/*************************************************************************************************
BUT : Destruction des composant de la fenetre
ENTREE : Le game et la police
SORTIE : Fin de programe
*************************************************************************************************/

void destroy(game *myGame,font *mFont){


    if(mFont->g_font!=NULL){
        TTF_CloseFont(mFont->g_font); /* Doit être avant TTF_Quit() */
        mFont->g_font=NULL;
    }

    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);


    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}
