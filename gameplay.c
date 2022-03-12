#include "gameplay.h"

void PlayerMoveX(Player_t * pEntity){
    pEntity->xSpeed += GROUND_MVT * (Keys[1] - Keys[3]);
    pEntity->x += pEntity->xSpeed;
    (pEntity->xSpeed > 0) ? (pEntity->xSpeed -= GROUND_MVT/1.32) : (pEntity->xSpeed += GROUND_MVT/1.32);
}

void gestPhysique(){
    PlayerMoveX(&Joueur);
}