#include "entity.h"

Player_t Joueur;

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 0;
    pJoueur->y = 0;
    pJoueur->isGrounded = 0;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
}

