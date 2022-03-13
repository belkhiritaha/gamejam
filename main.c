#include "main.h"

int running;
int GameOption;
int * chests;

int main(){
    running = 1;
    GameOption = MENU;
    initPlayer(&Joueur, 20, 10, 0);
    initListeEnnemies(ListeEnnemies, &EnnemiesCount);
    initMap();
    chests = initChests();
    initInventory();
    //printMap();
    BouclePrincipale();
}