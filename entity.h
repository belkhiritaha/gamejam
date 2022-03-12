#ifndef _ENTITY_HEADER_
#define _ENTITY_HEARDER_

#define RIGHT 0
#define LEFT 1
#define PLAYER_W 1
#define PLAYER_H 2

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
} Player_t;

extern Player_t Joueur;

void initPlayer();

#endif