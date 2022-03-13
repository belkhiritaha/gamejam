#include "gameplay.h"

int DrawJumpEffect = 0;
int Score = 0;
int Kills = 0;

int ScoreGlobal = 0;

void refreshMana(){
    int map_timer_curr = SDL_GetTicks();
    int time_spent = (map_timer_curr - map_timer1)/1000;
    if (GameOption == ON_MAP){
        if (time_spent){
           Joueur.mana -= time_spent * 100;
        }
    }
    else {
        time_spent = (map_timer_curr - map_timer2)/1000;
        if (Joueur.mana < MANA_MAX && time_spent){
            Joueur.mana += time_spent;
        } 
    }
    if (Joueur.mana < 20){
        GameOption = ON_TERRAIN;
        mana_save1 = 0;
        mana_save2 = 0;
    }
}

int checkCollisionY(Player_t *pEntity){
    int case_x = floorf(pEntity->x + pEntity->xSpeed - 0.5);//dont touch this
    int case_y = floorf(pEntity->y + pEntity->ySpeed );
    //printf("positions : %f %f\n",pEntity->x, pEntity->y);
    //printf("cases : %f %f %d\n", case_x, case_y, map[(int)case_y][(int)case_x]);
    //if (case_y >= 0 && case_y < NB_BLOCKS_Y && case_x >= 0 && case_x < NB_BLOCKS_X){
        if (map[case_y][case_x]){
            //printf("collide\n");
            pEntity->ySpeed = 0;
            pEntity->isGrounded = 1;
            return 1;
        }
        else {
            pEntity->isGrounded = 0;
        }
    //}
    return 0;
}

int checkCollisionX(Player_t *pEntity){
    int case_right = ceilf(pEntity->x + 2/16);
    int case_left = floorf(pEntity->x);
    int case_bot = floorf(pEntity->y - 2.6) + 2;
    int case_top = case_bot - 1;
    //int case_below = floorf(pEntity->y  + 2/16.0 - 1) + 1 +1;
    //printf("left = %d , pos = %f, %f , right = %d, bot= %d top= %d\n", case_left, pEntity->x,pEntity->y, case_right, case_bot, case_top);
    //printf("DESTINATION: %f\n", pEntity->x + xSpeed);
    if (map[case_bot][case_right] || map[case_top][case_right]){// || (pEntity->isFalling && pEntity->y - (int)pEntity->y > 0.7 && map[case_below][case_right])){
        pEntity->xSpeed = 0;
        return 2;
    }
    if (map[case_bot][case_left] || map[case_top][case_left]){// || (pEntity->isFalling && pEntity->y - (int)pEntity->y > 0.7 && map[case_below][case_left])){
        pEntity->xSpeed = 0;
        return 1;
    }
    return 0;
}

int PlayerMoveX(Player_t * pEntity){
    //printf("pos : %f %f\n", pEntity->x, pEntity->y);
    //printf("xSpeed = %f, ySpeed = %f\n", pEntity->xSpeed, pEntity->ySpeed);
    //printf("%d\n",checkCollisionX(pEntity));
    switch (checkCollisionX(pEntity))
    {
        case 0: //no sides collided
            if (fabs(pEntity->xSpeed) < MAX_RUN_SPEED){
                pEntity->xSpeed += GROUND_MVT * (Keys[1] - Keys[3]);
            }
            (pEntity->xSpeed > 0) ? (pEntity->xSpeed -= GROUND_MVT/1.32) : (pEntity->xSpeed += GROUND_MVT/1.32);

            pEntity->x += pEntity->xSpeed;
            break;
        
        case 2: //right side collided
            pEntity->xSpeed -= GROUND_MVT * Keys[3];
            pEntity->x += pEntity->xSpeed;
            break;

        case 1: //left side collided
           pEntity->xSpeed += GROUND_MVT * Keys[1];
            pEntity->x += pEntity->xSpeed;
            break;

        default:
            break;
    }

    return 1;
}

int EntityMoveX(Player_t *pEntity){
    int MoveLeft = 0;
    int MoveRight = 0;
    (pEntity->x - Joueur.x > 0) ? (pEntity->direction = LEFT):(pEntity->direction = RIGHT);
    if (fabs(pEntity->x - Joueur.x) < 5 + rand()%5){
        if (fabs(pEntity->x - Joueur.x) > 2){
            if (pEntity->x - Joueur.x < 0){
                MoveRight = 1;
                MoveLeft = 0;
            }
            else {
                MoveLeft = 1;
                MoveRight = 0;
            }
            DrawHitEffect = 0;
        }
        else {
            DrawHitEffect = -(pEntity->x - Joueur.x)/fabs(pEntity->x - Joueur.x);
            Joueur.hp -= 0.1;
            MoveRight = 0;
            MoveLeft = 0;
        }
    }

    switch (checkCollisionX(pEntity))
    {
        case 0: //no sides collided
            if (fabs(pEntity->xSpeed) < ENNEMY_MAX_RUN_SPEED * (1 + rand()%5)){
                pEntity->xSpeed += ENNEMY_GROUND_MVT * (MoveRight - MoveLeft);
            }
            (pEntity->xSpeed > 0) ? (pEntity->xSpeed -= ENNEMY_GROUND_MVT/1.32) : (pEntity->xSpeed += ENNEMY_GROUND_MVT/1.32);

            pEntity->x += pEntity->xSpeed;
            break;
        
        case 2: //right side collided
            pEntity->xSpeed -= ENNEMY_GROUND_MVT * MoveLeft;
            pEntity->x += pEntity->xSpeed;
            break;

        case 1: //left side collided
           pEntity->xSpeed += ENNEMY_GROUND_MVT * MoveRight;
            pEntity->x += pEntity->xSpeed;
            break;

        default:
            break;
    }

    return 1;
}

int EntityMoveY(Player_t *pEntity){
    int Jump = 0;
    (checkCollisionX(pEntity)) ? (Jump = 1) : (Jump = 0);
    if (checkCollisionY(pEntity)){
        pEntity->ySpeed -= JUMP_SPEED * Jump;
    }
    else{
        pEntity->ySpeed += GRAVITY;
    }
    pEntity->y += pEntity->ySpeed;
    return 1;
}

int PlayerMoveY(Player_t * pEntity){
    //printf("ySpeed = %f\n", pEntity->ySpeed);
    if (checkCollisionY(pEntity)){
        pEntity->ySpeed -= JUMP_SPEED * (Keys[0]);
        if (Keys[0]){
            DrawJumpEffect = 1;
        }
    }
    else{
        DrawJumpEffect = 0;
        pEntity->ySpeed += GRAVITY;
    }
   pEntity->y += pEntity->ySpeed;
    return 1;
}

int checkChest(){
    for (int i=0; i < NB_CHEST; i++){
        //printf("%d %d\n",(int)(Joueur.x * (Window_Width)/MAP_W) - 30, chests[i]);
        if ((int)(Joueur.x * (Window_Width)/MAP_W) == chests[i]){
            return i;
        }
    }
    return 69;
}

void UpdateChests(){
    int chestIndex = checkChest();
    if (chestIndex != 69){
        refreshChest(chestIndex);
        ScoreGlobal = ScoreGlobal + 5;
        int powerUp = rand()%3;
        if (Inventory[powerUp] == 0){
            Inventory[powerUp] = 1;
        }
        Score = Score + 1;
    }
}


void gestPhysique(){
    //printf("%p\n", Ennemy);
    for (int i = 0; i < EnnemiesCount ; i++){
        Player_t * Ennemy = ListeEnnemies[i];
        EntityMoveX(Ennemy);
        EntityMoveY(Ennemy);
        if (isJoueurAttacking){
            if (fabs(Ennemy->x - Joueur.x) < 3){
                Ennemy->hp -= 10;
            }
        }
        if (Ennemy->hp <= 0){
            Kills = Kills + 1;
            ScoreGlobal = ScoreGlobal + 10;
            ListeEnnemies[i] = CreateEnnemy();
            initPlayer(ListeEnnemies[i], rand() % 120, 20, 1);
            DrawHitEffect = 0;
        }
    }
    PlayerMoveX(&Joueur);
    PlayerMoveY(&Joueur);
    UpdateChests();
}

