#include "gest_event.h"

int Keys[NB_KEYS];

void * gestInputOnTerrain(SDL_Renderer * renderer){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_MOUSEBUTTONUP:
                    printf("Click\n");
                    break;

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

                    case SDLK_m:
                        if (GameOption == ON_MAP){
                            GameOption = ON_TERRAIN;
                        }
                        else{
                            GameOption = ON_MAP;
                        }
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
                    
                    case SDLK_x:
                        printf("end game");
                        running = 0;
                        //GameOption = ;
                        break;
                    
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