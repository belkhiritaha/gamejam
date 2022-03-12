#ifndef _MAP_HEADER_
#define _MAP_HEADER_

#include "main.h"

#define MAP_H 50
#define MAP_W 200

#define NB_TO_SHOW_X 20
#define NB_TO_SHOW_Y 4

extern int map[MAP_H][MAP_W];

void initMap();
void printMap();

#endif