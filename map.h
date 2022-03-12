#ifndef _MAP_HEADER_
#define _MAP_HEADER_

#include "main.h"

#define MAP_H 40
#define MAP_W 120

#define NB_TO_SHOW_X 30
#define NB_TO_SHOW_Y 10

extern int map[MAP_H][MAP_W];

void initMap();
void printMap();

#endif