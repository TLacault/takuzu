#include "takuzu.h"

// Loader
void sso_init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[], Env *env) { return; }

// Renderer
void sso_render(SDL_Window *win, SDL_Renderer *ren, Env *env) {
    if (env->active_scene != SETTINGS_SOUNDS)
        return;
}

// Input Processor
bool sso_process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
    if (env->active_scene != SETTINGS_SOUNDS)
        return;

    return false;
}

// Destructor
void sso_clean(SDL_Window *win, SDL_Renderer *ren, Env *env) { return; }

/* ************************************************************************************** */

// Event Handler
