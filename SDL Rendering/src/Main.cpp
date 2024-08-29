#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL.h>
#include <iostream>
#include <thread>

int gravity()
{
    int grid[640-1][640-1];
    for (int x = 0; x < 640; x++)
    {
        for (int y = 0; y < 640; y++)
        {
            grid[x][y] = 0;
            std::cout << "x: " << x << " , " << "y: "<<  y << std::endl;
        }
    }
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
        SDL_RenderDrawPoint(renderer, 64/2, 64/2);
        SDL_RenderPresent(renderer);

        while (true)
        {
            SDL_Event event;
            if (SDL_PollEvent(&event));
            {
                if (event.type == SDL_QUIT)
                    break;
                if (event.type == SDL_MOUSEMOTION)
                {
                    int x,y;
                    SDL_GetMouseState( &x, &y);
                    std::cout << x <<" : " << y << std::endl;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(SDL_BUTTON_LEFT == event.button.button)
                        {std::cout << "LMB DOWN" << std::endl; }
                    if(SDL_BUTTON_RIGHT == event.button.button)
                        {std::cout << "RMB DOWN" << std::endl; }
                    if(SDL_BUTTON_MIDDLE == event.button.button)
                        {std::cout << "MMB DOWN" << std::endl; }
                }
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if(SDL_BUTTON_LEFT == event.button.button)
                        {std::cout << "LMB UP" << std::endl; }
                    if(SDL_BUTTON_RIGHT == event.button.button)
                        {std::cout << "RMB UP" << std::endl; }
                    if(SDL_BUTTON_MIDDLE == event.button.button)
                        {std::cout << "MMB UP" << std::endl; }
                }
            } 
    int grid[640-1][640-1];
    for (int x = 0; x < 640; x++)
    {
        for (int y = 0; y < 640; y++)
        {
            grid[x][y] = 0;
            //std::cout << "x: " << x << " , " << "y: "<<  y << std::endl;
        }
    }
    std::cout << "List completed" << std::endl;
    return 0;
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}