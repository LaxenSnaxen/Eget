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
        SDL_Renderer* renderer;
        SDL_CreateWindowAndRenderer(128*6, 64*6, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 6, 6);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, 128/2, 64/2);
        SDL_RenderPresent(renderer);

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

/*int simulation()
{
    int arr[127][63]
    for (int i = 0; i < 129);
    {
        NULL;
    }
}*/