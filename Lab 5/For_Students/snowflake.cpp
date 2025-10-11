#define _GNU_SOURCE /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <pthread.h>
#include <math.h>
#include "Snowflake.h"

using namespace std;

pthread_mutex_t received_message_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t vector_lock = PTHREAD_MUTEX_INITIALIZER;

int event_thread(void *arg)
{
    // !!!!!!! Do Not Touch !!!!!!!!!
    SDL_Event event;

    while (!quit)
    {
        while (!quit && SDL_WaitEvent(&event))
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                quit = true;

                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:

                    break;
                }
            }
        }
        exit(0);
    }
    return 0;
}

// Rotate right x degree
void right(double x)
{
    angle -= x;
}

// Rotate left x degree
void rotate_left(double x)
{
    angle += x;
}

void drawFourLines(double side, int level)
{
    if (level == 0)
    {
        pt.X = (int)(cos(angle * PI / 180) * side) + currPt.X;
        pt.Y = (int)(sin(angle * PI / 180) * side) + currPt.Y;
        SDL_RenderDrawLine(renderer, int(currPt.X), int(currPt.Y), int(pt.X), int(pt.Y));
        currPt.X = pt.X;
        currPt.Y = pt.Y;
    }
    else
    {
        double new_side = side / 3.0;
    
        drawFourLines(new_side, level - 1);
        rotate_left(90);
        drawFourLines(new_side, level - 1);
        right(90);
        drawFourLines(new_side, level - 1);
        right(90);
        drawFourLines(new_side, level - 1);
        rotate_left(90);
        drawFourLines(new_side, level - 1);
    }
}

void SnowFlakes(double side, int level)
{
    currPt.X = 200;
    currPt.Y = 200;
    angle = 0.0;
    
    for (int i = 0; i < 4; i++)
    {
        drawFourLines(side, level);
        right(90);
    }
}

int main(int argc, char **argv)
{
    SDL_Event event;

    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " <level> <side_length>" << endl;
        return 1;
    }
    else
    {
        // !!!!!!! Do Not Touch !!!!!!!!!
        lvl = atoi(argv[1]);
        s = atoi(argv[2]);
        init();
        // Initiaize event thread
        SDL_Thread *thread;
        thread = SDL_CreateThread(event_thread, "UI_Thread", NULL);
        // clear window

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SnowFlakes(s, lvl);
        SDL_RenderPresent(renderer);
        while (!quit)
        {
            SDL_Delay(33);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}