#include "entity.h"

Player_t Joueur;

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 20;
    pJoueur->y = 15;
    pJoueur->isGrounded = 0;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
}

