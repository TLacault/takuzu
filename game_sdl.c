#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "engine.h"
#include "env.h"
#include "sdl_game.h"
#include "takuzu.h"

/* **************************************************************** */

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        ERROR("Error: SDL_Init VIDEO (%s)", SDL_GetError());

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG) != IMG_INIT_PNG)
        ERROR("Error: IMG_Init PNG (%s)", SDL_GetError());

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
        ERROR("Error: TTF_Init (%s)", SDL_GetError());

    // Play sounds in a separate thread
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        ERROR("Error: Mix_OpenAudio (%s)", SDL_GetError());

    /* create window and renderer */
    SDL_Window* win = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                       SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!win)
        ERROR("Error: SDL_CreateWindow (%s)", SDL_GetError());
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren)
        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (!ren)
        ERROR("Error: SDL_CreateRenderer (%s)", SDL_GetError());

    /* initialize the environment */
    Env* env = init(win, ren, argc, argv);
    SDL_Event e;

    bool quit = false;
    while (!quit) {
        env_update(env);
        /* manage events */
        while (SDL_PollEvent(&e)) {
            /* process your events */
            quit = process(env->win, env->ren, env, &e);
            if (quit)
                break;
        }

        // Window Reset
        SDL_RenderClear(env->ren);
        render(env->win, env->ren, env);
        SDL_RenderPresent(env->ren);
    }

    /* clean the environment */
    clean(env->win, env->ren, env);

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
