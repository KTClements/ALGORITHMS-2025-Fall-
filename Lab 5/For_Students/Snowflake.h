#ifndef _SDL2_Header
#define _SDL2_Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#ifndef _Point_Header
#define _Point_Header
#include "Point.h"
#endif

#ifndef _Color_Def
#define _Color_Def
SDL_Color Red = {255, 0, 0};
SDL_Color Black = {0, 0, 0};
SDL_Color White = {0xff, 0xff, 0xff};
#endif

#ifndef _Snowflak_Support
#define _Snowflak_Support

enum align
{
    alignLeft,
    alignCenter,
    alignRight
};

// variables
bool quit = false;
int lvl;
bool draw;
double PI = 3.14159;
double s;
Point currPt, pt;
double angle;

SDL_Renderer *renderer;
SDL_Window *window;

void draw_text(SDL_Renderer *renderer, int x, int y, char message[], SDL_Color color, int alignment)
{
    SDL_Rect text_rect;
    SDL_Surface *messageSurface;
    int message_width;
    int message_height;
    SDL_Texture *textTexture;

    TTF_Font *Sans = TTF_OpenFont("FreeSans.ttf", 12); //this opens a font style and sets a size
    TTF_SizeText(Sans, message, &message_width, &message_height);
    messageSurface = TTF_RenderText_Blended(Sans, message, color);
    TTF_CloseFont(Sans);
    switch (alignment)
    {
    case alignLeft:
        text_rect.x = x; //controls the rect's x coordinate
        break;
    case alignCenter:
        text_rect.x = x - (message_width / 2); //controls the rect's x coordinate
        break;
    case alignRight:
        text_rect.x = x - message_width; //controls the rect's x coordinate
        break;
    }
    text_rect.y = y;              // controls the rect's y coordinte
    text_rect.w = message_width;  // controls the width of the rect
    text_rect.h = message_height; // controls the height of the rect
    textTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
    SDL_DestroyTexture(textTexture);
}

int init()
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("CSCI415 Snowflake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    return 0;
}

#endif