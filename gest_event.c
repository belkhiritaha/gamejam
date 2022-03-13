#include "gest_event.h"

int Keys[NB_KEYS];

int map_timer1;
int map_timer2;
int mana_save1;
int mana_save2;

int isJoueurAttacking = 0;

void * gestInputOnTerrain(SDL_Renderer * renderer){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (Inventory[3] > 0){
                        Inventory[3] = Inventory[3] - 1;
                        isJoueurAttacking = 1;
                    }
                    continue;
                
                case SDL_MOUSEBUTTONUP:
                    isJoueurAttacking = 0;
                    continue;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_z:
                        Keys[0] = 1;
                        continue;
                    
                    case SDLK_q:
                        Keys[3] = 1;
                        Joueur.direction = 0;
                        continue;
                    
                    case SDLK_d:
                        Keys[1] = 1;
                        Joueur.direction = 1;
                        continue;

                    case SDLK_s:
                        Keys[2] = 1;
                        continue;
                    
                    default:
                        continue;
                    }
                
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_z:
                        Keys[0] = 0;
                        continue;
                    
                    case SDLK_q:
                        Keys[3] = 0;
                        continue;
                    
                    case SDLK_d:
                        Keys[1] = 0;
                        continue;

                    case SDLK_s:
                        Keys[2] = 0;
                        continue;


                    case SDLK_1:
                        if (Inventory[0] == 1){
                            Inventory[0] = 0;
                            Inventory[3] = 20;
                        }
                        continue;

                    case SDLK_2:
                        if (Inventory[1] == 1){
                            Inventory[1] = 0;
                            Joueur.mana = MANA_MAX;
                        }
                        continue;

                    case SDLK_3:
                        if (Inventory[2] == 1){
                            Inventory[2] = 0;
                            ScoreGlobal+= 20;
                        }
                        continue;
                    
                    case SDLK_x:
                        printf("end game");
                        printf("%f\n", Joueur.x);
                        running = 0;
                        //GameOption = ;
                        break;

                    case SDLK_SPACE:
                        if (GameOption == ON_MAP){
                            //GameOption = ON_TERRAIN;
                            map_timer1 = 0;
                            map_timer2 = SDL_GetTicks();
                            mana_save1 = Joueur.mana;
                            mana_save2 = Joueur.mana;
                        }
                        else{
                            if (Joueur.mana > MANA_MAX - 1000){
                                mana_save2 = Joueur.mana;
                                GameOption = ON_MAP;
                                map_timer1 = SDL_GetTicks();
                                map_timer2 = 0;
                            }
                            else {
                                printf("hello");
                                Joueur.mana = 0;
                                mana_save1 = 0;
                                mana_save2 = 0;
                            }
                        }
                        continue;
                    
                    default:
                        continue;
                    }
                
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                        Window_Height = event.window.data2;
                        Window_Width = event.window.data1;
                    }
                    break;

                case SDL_QUIT:
                    printf("end game");
                    running = 0;
                    break;

                default:
                    break;
                }
            }
    gestPhysique();
    SDL_Delay(1);
    return NULL;
}

void gestMenu(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {   
                case SDL_MOUSEBUTTONUP:
                    GameOption = ON_TERRAIN;
                    continue;

                default:
                    break;


                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                        Window_Height = event.window.data2;
                        Window_Width = event.window.data1;
                    }
                    break;

                case SDL_QUIT:
                    printf("end game");
                    running = 0;
                    break;
                
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_x:
                        printf("end game");
                        running = 0;
                        continue;
                    
                    default:
                        continue;
                    }
            }
    }
    SDL_Delay(1);
}