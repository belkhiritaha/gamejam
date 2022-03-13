#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_

#include <SDL2/SDL.h>
#include "map.h"
#include "render.h"
#include "entity.h"

#define ON_TERRAIN 1
#define ON_MAP 2
#define MENU 3
#define END_SCREEN 4

extern int running;
extern int GameOption;
extern int * chests;


#endif