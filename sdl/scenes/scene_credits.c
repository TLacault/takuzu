#include "takuzu.h"

// Loader
void c_init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[], Env *env) { return; }

// Renderer
void c_render(SDL_Window *win, SDL_Renderer *ren, Env *env) {
    if (env->active_scene != CREDITS)
        return;
}

// Input Processor
bool c_process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
    if (env->active_scene != CREDITS)
        return;

    return false;
}

// Destructor
void c_clean(SDL_Window *win, SDL_Renderer *ren, Env *env) { return; }

/* ************************************************************************************** */

// Event Handler
