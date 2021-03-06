#ifndef _ENTITY_HEADER_
#define _ENTITY_HEADER_

#define RIGHT 0
#define LEFT 1
#define PLAYER_W 4
#define PLAYER_H 2

#define MANA_MAX 5000
#define HP_MAX 5000

#define NB_ENNEMY 10
#define NB_CHEST 5

#define REFILL_AUTO 0
#define REFILL_MANA 1
#define JUMP_BOOST 2

#include <stdlib.h>
#include "map.h"

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
    float mana;
    float hp;
    struct Player * suiv;
} Player_t;

extern int EnnemiesCount;

extern Player_t * ListeEnnemies[NB_ENNEMY];

extern Player_t Joueur;

extern int Inventory[4];

void initPlayer(Player_t * pJoueur, float x, float y, int id);

void initListeEnnemies(Player_t * ListeEnnemies[NB_ENNEMY], int * EnnemiesCount);

void removeEnnemy(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount);

void addEnnemytoList(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount);

Player_t * CreateEnnemy();

int * initChests();

void refreshChest(int chest_index);

void initInventory();

#endif