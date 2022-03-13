#ifndef _GESTEVENT_HEADER_
#define _GESTEVENT_HEADER_

#include <SDL2/SDL.h>
#include "main.h"
#include "entity.h"
#include "gameplay.h"

#define NB_KEYS 10

extern int Keys[NB_KEYS];

extern int map_timer1;
extern int map_timer2;
extern int mana_save1;
extern int mana_save2;
void * gestInputOnTerrain(SDL_Renderer * renderer);

#endif