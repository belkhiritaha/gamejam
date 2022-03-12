#ifndef _GAMEPLAY_HEADER_
#define _GAMEPLAY_HEADER_

#include "map.h"
#include "gest_event.h"
#include <math.h>

#define MAX_RUN_SPEED 0.005
#define MAX_Y_SPEED 0.001
#define JUMP_SPEED 0.0045
#define GROUND_MVT 0.00007
#define GROUND_FRICTION (9/10)
#define AIR_FRICTION (9.999/10)
#define GRAVITY 0.0000065

void gestPhysique();

#endif