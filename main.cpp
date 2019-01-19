#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    SDL_Window* window = SDL_CreateWindow(
        "Hello World",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    // Clear background colour to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set render colour to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_Rect r{ 50, 50, 50, 50 };
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
