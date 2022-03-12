#include "render.h"

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_Texture *block_texture;
SDL_Surface *blocks[5];

SDL_Texture *sprite_texture;
SDL_Surface *character_sprite[10];

int Window_Height;
int Window_Width;




void CreateWindow(){
    SDL_DisplayMode ScreenDimension;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Couldn't create window.");
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &ScreenDimension);

    window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenDimension.w, ScreenDimension.h, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == NULL){
        printf("Couldn't create window");
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    if (renderer == NULL){
        printf("Couldn't create renderer.");
        exit(EXIT_FAILURE);
    }

    SDL_GetWindowSize(window, &Window_Width, &Window_Height);
}


void DrawPlayerOnMap(SDL_Renderer * renderer){
    SDL_Rect rect;
    rect.w = PLAYER_W * (Window_Width)/MAP_W;
    rect.h = PLAYER_H * (Window_Height/MAP_H);
    rect.x = Joueur.x;
    rect.y = Joueur.y;
    sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[0]);
    SDL_RenderCopyEx(renderer, sprite_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(1-Joueur.direction));
    SDL_DestroyTexture(sprite_texture);
}

void DrawPlayer(SDL_Renderer * renderer){
    SDL_Rect rect;
    rect.w = PLAYER_W * (Window_Width)/MAP_W;
    rect.h = PLAYER_H * (Window_Height/MAP_H);
    rect.x = Window_Height/2;
    rect.y = Window_Width/2;
    sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[0]);
    SDL_RenderCopyEx(renderer, sprite_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(1-Joueur.direction));
    SDL_DestroyTexture(sprite_texture);
}



void AffichageNormal(){
    //bg_texture = SDL_CreateTextureFromSurface(renderer, background);
    block_texture = SDL_CreateTextureFromSurface(renderer, blocks[0]);
//////////////// affichage background
    SDL_Rect rect;
    rect.h = Window_Height;
    rect.w = Window_Width;
    rect.x = 0;
    rect.y = 0;
    //SDL_RenderCopy(renderer, bg_texture, NULL, &rect);
//////////////// affichage map 
    float side_padding = (Joueur.x - (int)Joueur.x);
    float top_padding = 1 - (Joueur.y  -(int)Joueur.y);
    rect.w = (Window_Width/MAP_W);
    rect.h = (Window_Height/MAP_H);
    rect.x =  -side_padding * rect.w;
    rect.y = (top_padding- 1) * rect.h;
    int offset_y;
    int offset_x;
    for(int y = 0; y<MAP_H + 4; y++){
            for (int x = 0; x < MAP_W +5; x++)
            {
                offset_x = x + Joueur.x - 4;
                offset_y = y + Joueur.y - 4;
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
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(block_texture); 
    SDL_DestroyTexture(sprite_texture);
    //SDL_DestroyTexture(bg_texture);
}

void AffichageMap(SDL_Renderer * renderer){
    block_texture = SDL_CreateTextureFromSurface(renderer, blocks[0]);
    SDL_Rect rect;

    //background
    rect.w = (Window_Width);
    rect.h = Window_Height;
    rect.x = 0;
    rect.y = 0;

    SDL_SetRenderDrawColor(renderer,200,200,200,200);
    SDL_RenderFillRect(renderer, &rect);



    rect.w = (Window_Width)/MAP_W;
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

    DrawPlayerOnMap(renderer);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(block_texture);
}

void *BoucleGestInput(void *arg){
    while(GameOption){
      switch(GameOption){
          case ON_MAP : gestInputOnTerrain(renderer);break;
          case ON_TERRAIN : gestInputOnTerrain(renderer);break;
          //case 2 : gestMenu();break;
          default:printf("game option fault");break;
      }
    }
    return NULL;
}

int BouclePrincipale(){
    CreateWindow();

    blocks[0] = IMG_Load("Res/block.png");
    character_sprite[0] = IMG_Load("Res/block.png");

    pthread_t threadGest;
    int RetourDuThreadGest = pthread_create(&threadGest, NULL, BoucleGestInput, NULL);
    if (RetourDuThreadGest){
        return 1;
    }

    //GameOption = ON_MAP;

    while (running)
    {
        switch (GameOption)
        {
            case ON_TERRAIN:
                //printf("haha");
                //running = 0;
                AffichageNormal();
                break;
            
            case ON_MAP:
                AffichageMap(renderer);
                break;

            default:
                //printf("gameoption fault");
                exit(EXIT_FAILURE);
            }
    }
    return 0;
}