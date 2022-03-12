#ifndef _ENTITY_HEADER_
#define _ENTITY_HEARDER_

#define RIGHT 0
#define LEFT 1
#define PLAYER_W 4
#define PLAYER_H 2
#define NB_ENNEMY 15


#include <stdlib.h>

typedef struct Player
{
    float x;
    float y;
    int h;
    int w;
    float xSpeed;
    float ySpeed;
    int direction;
    int isGrounded;
    int id;
    int mana;
    struct Player * suiv;
} Player_t;

extern int EnnemiesCount;

extern Player_t * ListeEnnemies[NB_ENNEMY];

extern Player_t Joueur;

void initPlayer(Player_t * pJoueur, float x, float y, int id);

void initListeEnnemies(Player_t * ListeEnnemies[NB_ENNEMY], int * EnnemiesCount);

void removeEnnemy(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount);

void addEnnemytoList(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount);

Player_t * CreateEnnemy();


#endif