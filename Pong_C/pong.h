
typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct font{

    TTF_Font *g_font;

}font;


typedef struct coordonnees{

    double x;
    double y;

}coordonnees;

typedef struct raquette{

    coordonnees pos;
    int h;
    int w;
    int vitesse;
    int score;

}raquette;

typedef struct cercle{

    coordonnees pos;
    int rayon;
    float vitesse;
    float modif;
    int HautBas;
    int GaucheDroite;

}cercle;

enum VerifEcran { Haut,Bas,Gauche,Droite,GaucheHaut,GaucheBas,DroiteHaut,DroiteBas };

//Pong.c
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame, font *mFont);
void writeSDL(game *myGame,font mFont,raquette *J1,raquette *J2);
int VerifCollEcran(cercle *balle);
void delay(unsigned int frameLimit);
void destroy(game *myGame,font *mFont);

//Raquette.c
void InitJ1(raquette *J1);
void ReInitJ1(raquette *J1);
void InitJ2(raquette *J2);
void ReInitJ2(raquette *J2);
void DessineRaquette(game *myGame,raquette *joueur);
void handleEvents(gameState *state,raquette *J1,raquette *J2,int key[]);
void UpdateEvents(gameState *state,int key[]);
int VerifCollRaquette(raquette *J1);
int VerifRenvoiBalle(cercle *balle,raquette *J1,raquette *J2);

//Balle.c
void DessineCercle(game *myGame,cercle *balle);
void InitBalle(cercle *balle);
void DirectionBalle(cercle *balle,raquette *J1,raquette *J2);
void DeplaceBalle(cercle *balle,raquette *J1,raquette *J2);
void GestScore(cercle *balle,raquette *J1,raquette *J2,int key[]);
