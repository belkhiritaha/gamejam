#include "map.h"

int map[MAP_H][MAP_W];

void initMap(){
    int i;
    int j;
    for (i=0; i<MAP_H; ++i){
        for (j=0; j<MAP_W; ++j){
            map[i][j] = 0;
        }
    }
    for (i=MAP_H/2; i < MAP_H; ++i){
        for (j= 0; j < MAP_W; ++j){
            map[i][j] = 1;
        }
    }
    map[11][15] = 1;
}

void printMap(){
    int i;
    int j;
    int case_x = 0;
    int case_y = 0;
    printf("%d %d\n", case_x, case_y);
    for (i=0; i<MAP_H; ++i){
        for (j=0; j<MAP_W; ++j){
            if ( i == case_y && j == case_x){
                printf("2");
            }
            else{
                printf("%d", map[i][j]);
            }
        }
        printf("\n");
    }
}