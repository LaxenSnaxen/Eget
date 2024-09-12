#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL.h>
#include <iostream>
#include <thread>
#include <cmath>
#include <time.h>

int printArray2D (int**arr)
{

    for(int a = 0; a < 64; a++)
    {
        for(int b = 0; b < 64; b++)
        {
            std::cout << arr[a][b] << " ";
        }
        std::cout << std::endl;
    }  
    return 0;
}

template<typename T>

int removeOldPointCreatNew(T renderer, int x, int y, int nx, int ny, int** grid)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderDrawColor(renderer, 235, 195, 50, 255);
    SDL_RenderDrawPoint(renderer, nx, ny);
    SDL_RenderPresent(renderer);
    grid [x] [y] = 0;
    grid [nx] [ny] = 1;
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderDrawPoint(renderer, 64/2, 64/2);
        SDL_RenderPresent(renderer);

        SDL_RenderClear(renderer);
        
        // Alla celler ska vara noll, men jag tror att det inte defineras ordentligt, jag vet inte heller hur jag ska set till att allt ska defineras som nollor utan att byta det sätt jag definerar arrayen på, vilket skulle fucka med vissa funktioner.
        int** grid = new int*[64];
        for (int x = 0; x < 64; x++)
            grid[x] = new int[64];


        while (true)
        {   
            SDL_PumpEvents();
            int x,y = 0;
            int mouseState = SDL_GetMouseState(&x, &y);
            //std::cout << mouseState << std::endl;
            
            if (mouseState == 1) 
            {
                SDL_SetRenderDrawColor(renderer, 235, 195, 50, 255);
                SDL_Delay(100);
                x =  round(x/10);
                y =  round(y/10);
                std::cout << x << ":" << y << std::endl;
                SDL_Delay(10);
                std::cout << "Before: " << grid[x][y] << std::endl;
                grid[x][y] = 1;
                std::cout << "After: " << grid[x][y] << std::endl;
                SDL_RenderDrawPoint(renderer, x, y);
                SDL_RenderPresent(renderer);
                //printArray2D(grid);
            }

            SDL_Event event;
            if (SDL_PollEvent(&event));
            {
                if (event.type == SDL_QUIT)
                    break;
                if (event.type == SDL_MOUSEMOTION)
                {
                    int x,y = 0;
                    SDL_GetMouseState( &x, &y);
                    x =  round(x/10);
                    y =  round(y/10);
                    std::cout << x <<" : " << y << std::endl;
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
                    else if (grid[x+1][y+1] == 0 & (grid[x-1][y+1] == 0))
                        {
                            std::srand(time(NULL));
                            int random_value = std::rand() % 2;
                            if (random_value != 1)
                            {
                            int nx = x + 1;
                            int ny = y + 1;
                            removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                            }
                            else
                            {
                            int nx = x - 1;
                            int ny = y + 1;
                            removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                            }

                        }
                    else if (grid[x-1][y+1] == 0 & grid[x+1][y+1] == 1)
                        {
                        int nx = x - 1;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                        }
                    else if (grid[x+1][y+1] == 0 & grid[x-1][y+1] == 1)
                        {
                        int nx = x + 1;
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
