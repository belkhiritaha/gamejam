#include "main.h"

int running;
int GameOption;

int main(){
    running = 1;
    GameOption = ON_TERRAIN;
    initPlayer(&Joueur, 20, 10, 0);
    initListeEnnemies(ListeEnnemies, &EnnemiesCount);
    initMap();
    //printMap();
    BouclePrincipale();
}