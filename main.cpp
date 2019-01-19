#include <SDL2/SDL.h>
#include <algorithm>
#include <memory>

using Renderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;
using Window = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;

template<typename T>
inline void check_sdl_resource(const T& resource) {
    if (!resource) {
        throw std::runtime_error(SDL_GetError());
    }
}

inline void check_sdl_status(int status) {
    if (status != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

inline void check_sdl_bool(SDL_bool status) {
    if (status != SDL_TRUE) {
        throw std::runtime_error("Operation returned unexpected false");
    }
}

static void drawLineSimple(SDL_Renderer& renderer, int x1, int y1, int x2, int y2);

int main(int argc, char *argv[]) {
    const int width = 640;
    const int height = 480;

    // Enable antialiasing
    check_sdl_bool(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"));

    Window window(SDL_CreateWindow(
        "Hello World",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN),
        SDL_DestroyWindow);
    check_sdl_resource(window);

    Renderer renderer(SDL_CreateRenderer(
        window.get(),
        -1,
        SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
    check_sdl_resource(renderer);

    // Clear background colour to red
    check_sdl_status(SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255));
    check_sdl_status(SDL_RenderClear(renderer.get()));

    // Set render colour to blue
    check_sdl_status(SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255));

    SDL_Rect r{ 50, 50, 50, 50 };
    check_sdl_status(SDL_RenderFillRect(renderer.get(), &r));

    // Draw line
    check_sdl_status(SDL_RenderDrawLine(renderer.get(), 0, 0, width - 1, height - 1));

    // Draw line (Bresenham's algorithm)
    drawLineSimple(*renderer, 0, height - 1, width - 1, 0);

    SDL_RenderPresent(renderer.get());

    SDL_Delay(2000);
    SDL_Quit();

    return EXIT_SUCCESS;
}

// Draw line with no antialiasing etc.
void drawLineSimple(SDL_Renderer& renderer, int x1, int y1, int x2, int y2) {
    const int dx = x2 - x1;
    const int dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        const int xMin = std::min(x1, x2);
        const int xMax = std::max(x1, x2);
        for (int x = xMin; x <= xMax; ++x) {
            const int y = y1 + static_cast<int>(dy * (x - x1) / dx);
            check_sdl_status(SDL_RenderDrawPoint(&renderer, x, y));
        }
    }
    else {
        const int yMin = std::min(y1, y2);
        const int yMax = std::max(y1, y2);
        for (int y = yMin; y <= yMax; ++y) {
            const int x = x1 + static_cast<int>(dx * (y - y1) / dy);
            check_sdl_status(SDL_RenderDrawPoint(&renderer, x, y));
        }
    }
}
