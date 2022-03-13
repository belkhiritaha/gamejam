#include "render.h"

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_Texture *block_texture;
SDL_Surface *blocks[5];

SDL_Texture *sprite_texture;
SDL_Surface *character_sprite[50];
SDL_Surface *ennemy_sprite[20];

SDL_Texture *bg_texture;
SDL_Surface *background;

SDL_Texture *blur_texture;
SDL_Surface *blur;

SDL_Surface *HitEffectSurface;
SDL_Surface *ArrowSurface;

SDL_Surface *BarsSurface;

SDL_Surface *ChestSurface;
SDL_Surface *SwordSurface;
SDL_Surface *SkullSurface;

SDL_Surface *Card[3];
SDL_Texture *CardTexture;

SDL_Surface * Trophy;

SDL_Surface * GameName;
SDL_Surface * GameLost;

int Window_Height;
int Window_Width;

int DrawHitEffect = 0;

TTF_Font *RobotoFont;

SDL_Color Color = {255, 255, 255};



void CreateWindow(){
    SDL_DisplayMode ScreenDimension;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Couldn't create window.");
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &ScreenDimension);

    window = SDL_CreateWindow("Explorateur 3000", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenDimension.w, ScreenDimension.h, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == NULL){
        printf("Couldn't create window");
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    if (renderer == NULL){
        printf("Couldn't create renderer.");
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1)
    {
        exit(EXIT_FAILURE);
    }


    RobotoFont = TTF_OpenFont("Roboto-Black.ttf", 50);

    SDL_GetWindowSize(window, &Window_Width, &Window_Height);
}

void DrawCards(){
    SDL_Rect rect;
    rect.w = Window_Width/10;
    rect.h = Window_Height/10;
    rect.x = Window_Width - rect.w - 50;
    rect.y = 200; 

    for (int i=0; i<3; i++){
        if (Inventory[i] == 1){
            CardTexture = SDL_CreateTextureFromSurface(renderer, Card[i]);
            SDL_RenderCopy(renderer, CardTexture, NULL, &rect);
        }
        rect.y += rect.h + 20;
    }

    SDL_DestroyTexture(CardTexture);
}


void DrawScore(){
    char ScoreString[10];
    sprintf(ScoreString,"%d",Score);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, ScoreString, Color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = 50;
    Message_rect.h = 50;
    Message_rect.x = Window_Width - Message_rect.w - 50; 
    Message_rect.y = 50;  
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    Message_rect.x -= 80;
    blur_texture = SDL_CreateTextureFromSurface(renderer, ChestSurface);
    SDL_RenderCopy(renderer, blur_texture, NULL, &Message_rect);
    SDL_DestroyTexture(blur_texture);
}

void DrawScoreGlobal(){
    char ScoreString[10];
    sprintf(ScoreString,"%d",ScoreGlobal);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, ScoreString, Color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = 50;
    Message_rect.h = 50;
    Message_rect.x = 100; 
    Message_rect.y = Window_Height - Message_rect.h - 50;  
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    Message_rect.x -= 80;
    blur_texture = SDL_CreateTextureFromSurface(renderer, Trophy);
    SDL_RenderCopy(renderer, blur_texture, NULL, &Message_rect);
    SDL_DestroyTexture(blur_texture);
}

void DrawAutoAttack(){
    char AutoString[10];
    sprintf(AutoString,"%d",Inventory[3]);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, AutoString, Color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = 50;
    Message_rect.h = 50;
    Message_rect.x = 50; 
    Message_rect.y = 50;  
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    Message_rect.x += 80;
    blur_texture = SDL_CreateTextureFromSurface(renderer, SwordSurface);
    SDL_RenderCopy(renderer, blur_texture, NULL, &Message_rect);
    SDL_DestroyTexture(blur_texture);
}

void DrawKills(){
    char KillString[10];
    sprintf(KillString,"%d",Kills);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(RobotoFont, KillString, Color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = 50;
    Message_rect.h = 50;
    Message_rect.x = 50; 
    Message_rect.y = 150;  
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    Message_rect.x += 80;
    blur_texture = SDL_CreateTextureFromSurface(renderer, SkullSurface);
    SDL_RenderCopy(renderer, blur_texture, NULL, &Message_rect);
    SDL_DestroyTexture(blur_texture);
}


void DrawChests(){
    SDL_Rect rect;
    rect.w = 25;
    rect.h = 25;
    rect.y = Window_Height/2 - rect.h - 10;
    blur_texture = SDL_CreateTextureFromSurface(renderer, ChestSurface);
    for (int i = 0; i < NB_CHEST; i++){
        rect.x = chests[i] - rect.w;
        SDL_RenderCopy(renderer, blur_texture, NULL, &rect);
    }
    SDL_DestroyTexture(blur_texture);
}


void DrawPlayerOnMap(Player_t * pEntity, SDL_Renderer * renderer){
    SDL_Rect rect;
    int tick = SDL_GetTicks()/250;
    rect.w = PLAYER_W * (Window_Width)/MAP_W;
    rect.h = PLAYER_H * (Window_Height/MAP_H);
    rect.x = pEntity->x * (Window_Width)/MAP_W - 30;
    rect.y = pEntity->y * (Window_Height/MAP_H) - 35;
    if (pEntity->id == 1){
        if (fabs(pEntity->xSpeed) > MAX_RUN_SPEED/10){
            sprite_texture = SDL_CreateTextureFromSurface(renderer, ennemy_sprite[10 + tick % 7]);
        }
        else {
            sprite_texture = SDL_CreateTextureFromSurface(renderer, ennemy_sprite[tick % 7]);
        }
    }
    else {
        if (Joueur.isGrounded){
            if (isJoueurAttacking){
                sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[30 + tick % 12]);
            }
            else {
                if (fabs(Joueur.xSpeed) > MAX_RUN_SPEED/10){
                    sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[10 + tick % 7]);
                }
                else {
                    sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[tick % 5]);
                }
            }
        }
        else {
            if (Joueur.ySpeed > 0){//falling
                sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[20 + tick % 3]);
            }
            else {
                sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[23 + tick % 3]);
            }
        }

    }
    SDL_RenderCopyEx(renderer, sprite_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(1-pEntity->direction));
    SDL_DestroyTexture(sprite_texture);
}


void DrawPlayer(SDL_Renderer * renderer){
    SDL_Rect rect;
    int tick = SDL_GetTicks()/250;
    rect.w = (PLAYER_W) * (Window_Width)/NB_TO_SHOW_X;
    rect.h = PLAYER_H * (Window_Height/NB_TO_SHOW_Y);
    rect.x = Window_Width/2 - rect.w/2;
    rect.y = Window_Height/2 - rect.h/2 + 5;
    if (Joueur.isGrounded){
        if (isJoueurAttacking){
            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[30 + tick % 12]);
        }
        else {
            if (fabs(Joueur.xSpeed) > MAX_RUN_SPEED/10){
                sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[10 + tick % 7]);
            }
            else {
                sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[tick % 5]);
            }
        }
    }
    else {
        if (Joueur.ySpeed > 0){//falling
            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[20 + tick % 3]);
        }
        else {
            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[23 + tick % 3]);
        }
    }


    SDL_RenderCopyEx(renderer, sprite_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(1-Joueur.direction));

    if (DrawHitEffect){
        blur_texture = SDL_CreateTextureFromSurface(renderer, HitEffectSurface);
        rect.h = Window_Height;
        rect.w = Window_Width;
        rect.x = 0;
        rect.y = 0;
        SDL_RenderCopyEx(renderer, blur_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(DrawHitEffect));

        blur_texture = SDL_CreateTextureFromSurface(renderer, ArrowSurface);
        SDL_RenderCopyEx(renderer, blur_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(DrawHitEffect+1)/2);
    }

    SDL_DestroyTexture(sprite_texture);
    SDL_DestroyTexture(blur_texture);
}


void DrawBars(){
    SDL_Rect rect;
    rect.w = (Joueur.hp) * Window_Width/(2.75 * HP_MAX);
    rect.h = Window_Height/20;

    rect.x = Window_Width /4 + 100;
    rect.y = Window_Height/10 - rect.h;

    SDL_SetRenderDrawColor(renderer,250,0,0,250);
    SDL_RenderFillRect(renderer, &rect);        

    rect.w = (Joueur.mana) * Window_Width/(2.75 * MANA_MAX);
    rect.y += rect.h;

    SDL_SetRenderDrawColor(renderer,0,0,250,250);
    SDL_RenderFillRect(renderer, &rect);

    rect.w =Window_Width/2;
    rect.h = Window_Height;

    rect.x = Window_Width /4;
    rect.y = -300;

    blur_texture = SDL_CreateTextureFromSurface(renderer, BarsSurface);
    SDL_RenderCopy(renderer, blur_texture, NULL, &rect);

    SDL_DestroyTexture(blur_texture);
}


void AffichageNormal(){
    bg_texture = SDL_CreateTextureFromSurface(renderer, background);
    block_texture = SDL_CreateTextureFromSurface(renderer, blocks[0]);

//////////////// affichage background
    SDL_Rect parallax;
    parallax.h = Window_Height;
    parallax.w = Window_Width/4;
    parallax.x = Joueur.x;
    parallax.y = 0;
    SDL_Rect rect;
    rect.h = Window_Height;
    rect.w = Window_Width;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderCopy(renderer, bg_texture, &parallax, &rect);


//////////////// affichage map 
    float side_padding = (Joueur.x - (int)Joueur.x);
    float top_padding = 1 - (Joueur.y  -(int)Joueur.y);
    rect.w = (Window_Width/NB_TO_SHOW_X);
    rect.h = (Window_Height/NB_TO_SHOW_Y);
    rect.x =  -side_padding * rect.w;
    rect.y = (top_padding- 1) * rect.h;
    int offset_y;
    int offset_x;
    for(int y = 0; y<NB_TO_SHOW_Y+2; y++){
            for (int x = 0; x < NB_TO_SHOW_X + 1; x++)
            {
                offset_x = x + Joueur.x - 9;
                offset_y = y + Joueur.y - 3;
                //printf("offset_x = %d, offset_y = %d\n", offset_x, offset_y);
                //printf("%d %d\n", rect.x, rect.y);
                
                if (offset_y >= 0 && offset_y < MAP_H && offset_x >= 0 && offset_x < MAP_W){
                    if(map[offset_y][offset_x] == 1){
                        SDL_RenderCopy(renderer, block_texture, NULL, &rect);
                    }
                }
                rect.x = rect.x + rect.w;
            }
        rect.x = -side_padding * rect.w;
        rect.y = rect.y + rect.h;
        //rect.y = 0;// top_padding * rect.h;
    }
//////////////// affichage joueur
    DrawPlayer(renderer);
////////////////
    //////// blur
    blur_texture = SDL_CreateTextureFromSurface(renderer, blur);
    rect.h = Window_Height;
    rect.w = Window_Width;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderCopy(renderer, blur_texture, NULL, &rect);

    DrawBars();

    DrawScore();
    DrawScoreGlobal();
    DrawAutoAttack();
    DrawKills();
    DrawCards();

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(block_texture); 
    SDL_DestroyTexture(sprite_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(blur_texture);
}

void AffichageMap(){
    bg_texture = SDL_CreateTextureFromSurface(renderer, background);
    block_texture = SDL_CreateTextureFromSurface(renderer, blocks[0]);
//////////////// affichage background
    SDL_Rect rect;
    rect.h = Window_Height;
    rect.w = Window_Width;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderCopy(renderer, bg_texture, NULL, &rect);


    rect.w = 1 + (Window_Width)/MAP_W;
    rect.h = Window_Height/MAP_H;
    rect.x = 0;
    rect.y = 0;

    
    for (int j = 0; j < MAP_H; j++){
        for (int i = 0; i < MAP_W; i++){
            if (map[j][i] == 1){
                SDL_RenderCopy(renderer, block_texture, NULL, &rect);
            }
            rect.x = rect.x + rect.w;
        }
        rect.x = 0;
        rect.y = rect.y + rect.h;
    }

    DrawPlayerOnMap(&Joueur, renderer);
    
    for (int i = 0; i < EnnemiesCount; i++){
        Player_t * Ennemy = ListeEnnemies[i];
        DrawPlayerOnMap(Ennemy, renderer);
    }

    DrawChests();

    if (GameOption == ON_MAP){
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(block_texture);
    SDL_DestroyTexture(bg_texture);
}

void AffichageMenu(){
    AffichageMap();
    SDL_Rect rect;
    rect.w = Window_Width;
    rect.h = Window_Height/2;
    rect.x = 0; 
    rect.y = Window_Height/4;  
    blur_texture = SDL_CreateTextureFromSurface(renderer, GameName);
    SDL_RenderCopy(renderer, blur_texture , NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(blur_texture);
}

void AffichageEnd(){
    isJoueurAttacking = 1;
    AffichageMap();
    isJoueurAttacking = 0;
    SDL_Rect rect;
    rect.w = Window_Width;
    rect.h = Window_Height/2;
    rect.x = 0; 
    rect.y = Window_Height/4;  
    blur_texture = SDL_CreateTextureFromSurface(renderer, GameLost);
    SDL_RenderCopy(renderer, blur_texture , NULL, &rect);
    DrawScoreGlobal();
    DrawKills();
    DrawScore();
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(blur_texture);
}

void *BoucleGestInput(void *arg){
    while(GameOption){
      switch(GameOption){
          case ON_MAP : gestInputOnTerrain(renderer);break;
          case ON_TERRAIN : gestInputOnTerrain(renderer);break;
          case MENU : gestMenu();break;
          case END_SCREEN : gestMenu();break;
          default:printf("game option fault");break;
      }
    }
    return NULL;
}

int BouclePrincipale(){
    CreateWindow();

    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;

    blocks[0] = IMG_Load("Res/block.png");
    character_sprite[0] = IMG_Load("Res/idle/Warrior_Idle_1.png");
    character_sprite[1] = IMG_Load("Res/idle/Warrior_Idle_2.png");
    character_sprite[2] = IMG_Load("Res/idle/Warrior_Idle_3.png");
    character_sprite[3] = IMG_Load("Res/idle/Warrior_Idle_4.png");
    character_sprite[4] = IMG_Load("Res/idle/Warrior_Idle_5.png");
    character_sprite[5] = IMG_Load("Res/idle/Warrior_Idle_6.png");
    
    character_sprite[10] = IMG_Load("Res/Run/Warrior_Run_1.png");
    character_sprite[11] = IMG_Load("Res/Run/Warrior_Run_2.png");
    character_sprite[12] = IMG_Load("Res/Run/Warrior_Run_3.png");
    character_sprite[13] = IMG_Load("Res/Run/Warrior_Run_4.png");
    character_sprite[14] = IMG_Load("Res/Run/Warrior_Run_5.png");
    character_sprite[15] = IMG_Load("Res/Run/Warrior_Run_6.png");
    character_sprite[16] = IMG_Load("Res/Run/Warrior_Run_7.png");
    character_sprite[17] = IMG_Load("Res/Run/Warrior_Run_8.png");

    character_sprite[20] = IMG_Load("Res/Fall/Warrior_Fall_1.png");
    character_sprite[21] = IMG_Load("Res/Fall/Warrior_Fall_2.png");
    character_sprite[22] = IMG_Load("Res/Fall/Warrior_Fall_3.png");

    character_sprite[23] = IMG_Load("Res/Jump/Warrior_Jump_1.png");
    character_sprite[24] = IMG_Load("Res/Jump/Warrior_Jump_2.png");
    character_sprite[25] = IMG_Load("Res/Jump/Warrior_Jump_3.png");

    character_sprite[30] = IMG_Load("Res/Attack/Warrior_Attack_1.png");
    character_sprite[31] = IMG_Load("Res/Attack/Warrior_Attack_2.png");
    character_sprite[32] = IMG_Load("Res/Attack/Warrior_Attack_3.png");
    character_sprite[33] = IMG_Load("Res/Attack/Warrior_Attack_4.png");
    character_sprite[34] = IMG_Load("Res/Attack/Warrior_Attack_5.png");
    character_sprite[35] = IMG_Load("Res/Attack/Warrior_Attack_6.png");
    character_sprite[36] = IMG_Load("Res/Attack/Warrior_Attack_7.png");
    character_sprite[37] = IMG_Load("Res/Attack/Warrior_Attack_8.png");
    character_sprite[38] = IMG_Load("Res/Attack/Warrior_Attack_9.png");
    character_sprite[39] = IMG_Load("Res/Attack/Warrior_Attack_10.png");
    character_sprite[40] = IMG_Load("Res/Attack/Warrior_Attack_11.png");
    character_sprite[41] = IMG_Load("Res/Attack/Warrior_Attack_12.png");

    ennemy_sprite[0] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_1.png");
    ennemy_sprite[1] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_2.png");
    ennemy_sprite[2] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_3.png");
    ennemy_sprite[3] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_4.png");
    ennemy_sprite[4] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_5.png");
    ennemy_sprite[5] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_6.png");
    ennemy_sprite[6] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_7.png");
    ennemy_sprite[7] = IMG_Load("Res/monster_idle/Bringer-of-Death_Idle_8.png");

    ennemy_sprite[10] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_1.png");
    ennemy_sprite[11] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_2.png");
    ennemy_sprite[12] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_3.png");
    ennemy_sprite[13] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_4.png");
    ennemy_sprite[14] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_5.png");
    ennemy_sprite[15] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_6.png");
    ennemy_sprite[16] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_7.png");
    ennemy_sprite[17] = IMG_Load("Res/monster_walk/Bringer-of-Death_Walk_8.png");

    background = IMG_Load("Res/background.png");
    blur = IMG_Load("Res/blur.png");
    HitEffectSurface = IMG_Load("Res/HitEffect.png");
    ArrowSurface = IMG_Load("Res/arrow.png");
    BarsSurface = IMG_Load("Res/bars.png");

    ChestSurface = IMG_Load("Res/chest.png");
    SwordSurface = IMG_Load("Res/sword.png");
    SkullSurface = IMG_Load("Res/skull.png");

    Card[0] = IMG_Load("Res/refill_attacks.png");
    Card[1] = IMG_Load("Res/refill_mana.png");
    Card[2] = IMG_Load("Res/score_boost.png");

    Trophy = IMG_Load("Res/trophy.png");
    GameName = IMG_Load("Res/gameName.png");
    GameLost = IMG_Load("Res/gameLost.png");

    pthread_t threadGest;
    int RetourDuThreadGest = pthread_create(&threadGest, NULL, BoucleGestInput, NULL);
    if (RetourDuThreadGest){
        return 1;
    }

    //GameOption = ON_MAP;


    while (running)
    {
        a = SDL_GetTicks();
        delta = a - b;
        if (delta > 1000/60.0){
            refreshMana();
            switch (GameOption)
            {
                case ON_TERRAIN:
                    //printf("haha");
                    //running = 0;
                    AffichageNormal();
                    break;
                
                case ON_MAP:
                    AffichageMap();
                    break;

                case MENU:
                    AffichageMenu();
                    break;

                case END_SCREEN:
                    AffichageEnd();
                    break;

                default:
                    //printf("gameoption fault");
                    exit(EXIT_FAILURE);
            }
        }

    }
    return 0;
}