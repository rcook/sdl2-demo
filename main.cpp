#include <SDL2/SDL.h>
#include <memory>

using Renderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;
using Window = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;

int main(int argc, char *argv[]) {
    Window window(SDL_CreateWindow(
        "Hello World",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN),
        SDL_DestroyWindow);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }

    Renderer renderer(SDL_CreateRenderer(
        window.get(),
        -1,
        SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
   if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }

    // Clear background colour to red
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    // Set render colour to blue
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);

    SDL_Rect r{ 50, 50, 50, 50 };
    SDL_RenderFillRect(renderer.get(), &r);
    SDL_RenderPresent(renderer.get());

    SDL_Delay(1000);
    SDL_Quit();

    return EXIT_SUCCESS;
}
