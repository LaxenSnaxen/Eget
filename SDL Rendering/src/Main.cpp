#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL.h>
#include <iostream>
#include <thread>
#include <cmath>
#include <time.h>



int lastUpdateTime = 0;

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


template<typename T>
void updateGrid(T renderer, int** grid, int** lastUpdateTimeGrid, int currentTime)
{
    // Loopar över hela griden
    for (int x = 0; x < 64; x++)
    {
        for (int y = 63; y >= 0; y--)  // Starta längst ner för att undvika problem med att kolla nästa rad
        {
            if (grid[x][y] == 1 && y != 63)  // Om sandkornet inte är längst ner
            {
                // Kolla om tillräckligt mycket tid har passerat för just detta korn
                if (currentTime - lastUpdateTimeGrid[x][y] >= 200)  // 200 ms mellan uppdateringar
                {
                    lastUpdateTimeGrid[x][y] = currentTime;  // Uppdatera tiden för detta korn

                    // Fysiklogik för sandens fall
                    if (grid[x][y + 1] == 0)  // Om det är tomt under, flytta ner
                    {
                        int nx = x;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                    }
                    else if (grid[x + 1][y + 1] == 0 && grid[x - 1][y + 1] == 0)  // Om det finns plats på båda sidor
                    {
                        std::srand(time(NULL));  // Slumpa riktning
                        int random_value = std::rand() % 2;
                        int nx = (random_value != 1) ? x + 1 : x - 1;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                    }
                    else if (grid[x - 1][y + 1] == 0 && grid[x + 1][y + 1] == 1)
                    {
                        int nx = x - 1;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                    }
                    else if (grid[x + 1][y + 1] == 0 && grid[x - 1][y + 1] == 1)
                    {
                        int nx = x + 1;
                        int ny = y + 1;
                        removeOldPointCreatNew(renderer, x, y, nx, ny, grid);
                    }
                }
            }
        }
    }
}


template<typename T>

void placeSand(T renderer, int** grid, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 235, 195, 50, 255);
    std::cout << "Before: " << grid[x][y] << std::endl;
    grid[x][y] = 1;
    std::cout << "After: " << grid[x][y] << std::endl;
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << "Error: " << SDL_GetError();
    else
    {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_CreateWindowAndRenderer(64 * 10, 64 * 10, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 10, 10);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        // Skapa griden och en grid för senaste uppdateringstid för varje sandkorn
        int** grid = new int*[64];
        int** lastUpdateTimeGrid = new int*[64];

        for (int x = 0; x < 64; x++)
        {
            grid[x] = new int[64];
            lastUpdateTimeGrid[x] = new int[64];
            for (int y = 0; y < 64; y++)
            {
                grid[x][y] = 0;
                lastUpdateTimeGrid[x][y] = 0;
            }
        }

        int lastUpdateTime = SDL_GetTicks();
        const int updateInterval = 50;  // Bestäm hur långsamt sanden ska falla (millisekunder)

        while (true)
        {
            SDL_PumpEvents();
            int x, y = 0;
            int mouseState = SDL_GetMouseState(&x, &y);

            if (mouseState == 1)
            {
                x = round(x / 10);
                y = round(y / 10);
                placeSand(renderer, grid, x, y);
            }

            SDL_Event event;
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    break;
            }

            int currentTime = SDL_GetTicks();  // Hämta nuvarande tid

            if (currentTime - lastUpdateTime >= updateInterval)  // Kolla om det är dags att uppdatera sanden
            {
                lastUpdateTime = currentTime;  // Uppdatera senaste tiden
                updateGrid(renderer, grid, lastUpdateTimeGrid, currentTime);  // Uppdatera hela griden
            }
        }

        // Rensa resurser
        for (int i = 0; i < 64; i++)
        {
            delete[] grid[i];
            delete[] lastUpdateTimeGrid[i];
        }
        delete[] grid;
        delete[] lastUpdateTimeGrid;

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
}
