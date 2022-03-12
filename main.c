#include "main.h"

int running;
int GameOption;

int main(){
    running = 1;
    GameOption = ON_TERRAIN;
    initMap();
    printMap();
    initPlayer(&Joueur);
    BouclePrincipale();
}