#ifndef _GAMEPLAY_HEADER_
#define _GAMEPLAY_HEADER_

#include "map.h"
#include "gest_event.h"
#include <math.h>

#define MAX_RUN_SPEED 0.007
#define ENNEMY_MAX_RUN_SPEED 0.005
#define MAX_Y_SPEED 0.001
#define JUMP_SPEED 0.0048
#define GROUND_MVT 0.00003
#define ENNEMY_GROUND_MVT 0.00003
#define GRAVITY 0.000008

void gestPhysique();

#endif