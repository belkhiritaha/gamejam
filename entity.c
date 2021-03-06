#include "entity.h"

Player_t Joueur;
Player_t Mob_tete;

int Inventory[4];

void initInventory(){
    Inventory[REFILL_AUTO] = 1;
    Inventory[REFILL_MANA] = 1;
    Inventory[JUMP_BOOST] = 1;
    Inventory[3] = 20;
}


void initPlayer(Player_t * pJoueur, float x, float y, int id){
    pJoueur->x = x;
    pJoueur->y = y;
    pJoueur->isGrounded = 0;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
    pJoueur->suiv = NULL;
    pJoueur->id = id;
    pJoueur->mana = MANA_MAX;
    pJoueur->hp = HP_MAX;
}

Player_t * ListeEnnemies[NB_ENNEMY];

int EnnemiesCount = 0;

void initListeEnnemies(Player_t * ListeEnnemies[NB_ENNEMY], int * EnnemiesCount){
    while (*EnnemiesCount < NB_ENNEMY){
        ListeEnnemies[*EnnemiesCount] = CreateEnnemy();
        initPlayer(ListeEnnemies[*EnnemiesCount], rand() % 120, 20, 1);
        *EnnemiesCount+= 1;
    }
}

void removeEnnemy(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount){
    for (int i = 0; i < *EnnemiesCount; i++){
        if (ListeEnnemies[i] == pEnnemy){
            for (int j = i; j < *EnnemiesCount- 1; j++){
                ListeEnnemies[j] = ListeEnnemies[j+1];
            }
            *EnnemiesCount-= 1;
        }
    }
}

void addEnnemytoList(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount){
    ListeEnnemies[*EnnemiesCount] = pEnnemy;
    *EnnemiesCount+= 1;
}


Player_t * CreateEnnemy(){
    Player_t * Ennemy = calloc(1,sizeof(Player_t));
    return Ennemy;
}

int * initChests(){
    int * ListeChests = calloc(NB_CHEST, sizeof(int));
    for (int i = 0; i < NB_CHEST; i++){
        ListeChests[i] = (rand()% 1920) ;
    }
    return ListeChests;
}

void refreshChest(int chest_index){
    chests[chest_index] = (rand()%1920);
}
