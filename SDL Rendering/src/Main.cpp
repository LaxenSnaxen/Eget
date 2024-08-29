#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <iostream>


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO != 0))
        std::cout << "Error: " << SDL_GetError();
    else
    {
        SDL_Window* window;
        window = SDL_CreateWindow("Test Window", 400, 300, 800, 600, SDL_WINDOW_SHOWN);

        while (true)
        {
            SDL_Event event;
            SDL_PollEvent(&event);

            if (event.type == SDL_QUIT)
                break;
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}