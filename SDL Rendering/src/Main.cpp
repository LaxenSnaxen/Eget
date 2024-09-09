#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL.h>
#include <iostream>
#include <thread>
#include <cmath>

template<typename T>

int removeOldPointCreatNew(T renderer, int x, int y, int nx, int ny, int** grid)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, nx, ny);
    SDL_RenderPresent(renderer);
    grid [x] [y] = 0;
    grid [nx] [ny] = 1;
    SDL_Delay(10);
    return 0;
}

int main(int argc, char* argv[])
{   
    if (SDL_Init(SDL_INIT_VIDEO != 0))
        std::cout << "Error: " << SDL_GetError();
    else
    {

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_CreateWindowAndRenderer(64*10, 64*10, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 10, 10);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDrawPoint(renderer, 64/2, 64/2);
        SDL_RenderPresent(renderer);
        
        int** grid = new int*[64];
        for (int x = 0; x < 64; x++)
            grid[x] = new int[64];


        while (true)
        {   
            bool lmbDown = false;
            
            SDL_Event event;
            if (SDL_PollEvent(&event));
            {
                if (event.type == SDL_QUIT)
                    break;
                /*if (event.type == SDL_MOUSEMOTION)
                {
                    int x,y;
                    SDL_GetMouseState( &x, &y);
                    std::cout << x <<" : " << y << std::endl;
                }*/
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(SDL_BUTTON_LEFT == event.button.button)
                        {std::cout << "LMB DOWN" << std::endl;
                        lmbDown = true;
                        int x,y;
                        SDL_GetMouseState(&x,&y);
                        x =  round(x/10);
                        y =  round(y/10);
                        std::cout << x << ":" << y << std::endl;
                        grid[x][y] = 1;
                        std::cout << grid[x][y] << std::endl;
                        SDL_RenderDrawPoint(renderer, x, y);
                        SDL_RenderPresent(renderer);
                        if (event.type == SDL_MOUSEMOTION)
                        {}}
                    if(SDL_BUTTON_RIGHT == event.button.button)
                        {std::cout << "RMB DOWN" << std::endl; }
                    if(SDL_BUTTON_MIDDLE == event.button.button)
                        {std::cout << "MMB DOWN" << std::endl; }
                }
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if(SDL_BUTTON_LEFT == event.button.button)
                        {std::cout << "LMB UP" << std::endl; 
                        lmbDown = false;}
                    if(SDL_BUTTON_RIGHT == event.button.button)
                        {std::cout << "RMB UP" << std::endl; }
                    if(SDL_BUTTON_MIDDLE == event.button.button)
                        {std::cout << "MMB UP" << std::endl; }
                }
            }

            for (int x = 0; x < 64; x++)
            {
            for (int y = 0; y < 64; y++)
                {
                if (grid[x][y] == 1 && y != 63)
                    {
                    if (grid[x][y+1] == 0)
                        {
                        int nx = x;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                        }
                    else if (grid[x+1][y+1] == 0)
                        {
                        int nx = x + 1;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                        }
                    else if (grid[x+1][y+1] == 0)
                        {
                        int nx = x - 1;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                        }
                    }
                }
            }
        }

    SDL_Delay(100000);
    

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    }
}
