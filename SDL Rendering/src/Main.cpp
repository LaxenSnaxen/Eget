#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL.h>
#include <iostream>

int mouse()
{
    HANDLE hIn;
    HANDLE hOut;
    COORD KeyWhere;
    COORD MouseWhere;
    COORD EndWhere;
    bool Continue = TRUE;
    int KeyEvents = 0;
    int MouseEvents = 0;
    INPUT_RECORD InRec;
    DWORD NumRead;

    hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "Key Events   : " << std::endl;
    std::cout << "Mouse Events : " << std::flush;

    KeyWhere.X = 15;
    KeyWhere.Y = 0;
    MouseWhere.X = 15;
    MouseWhere.Y = 1;
    EndWhere.X = 0;
    EndWhere.Y = 3;

    while (Continue)
    {
        ReadConsoleInput(hIn,&InRec,1, &NumRead);

        switch (InRec.EventType)
        {
        case KEY_EVENT:
            ++KeyEvents;
            SetConsoleCursorPosition(hOut,KeyWhere);
            std::cout << KeyEvents << flush;
            if (InRec.Event.KeyEvent.uChar.AsciiChar == 'x')
            {
                SetConsoleCursorPosition(hOut,EndWhere);
                std::cout << "Exiting..." << std::endl;
                Continue = FALSE;
            }
            break;

        case MOUSE_EVENT:
            ++MouseEvents;
            SetConsoleCursorPosition(hOut, MouseWhere);
            std::cout << MouseEvents << flush;
            break;
        }
    }
}

int gravity()
{
    int grid[70][70];
    for (int x = 0; x < 70; x++)
    {
        for (int y = 0; y < 70; y++)
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
        SDL_Window* window
        SDL_Renderer* renderer
        SDL_CreateWindowAndRenderer(70*10, 70*10, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 10, 10);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, 70/2, 70/2);
        SDL_RenderPresent(renderer);

        gravity(    );

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