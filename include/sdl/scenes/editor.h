#ifndef EDITOR_H
#define EDITOR_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "conf.h"
#include "input.h"
#include "scene.h"

/* **************************************************************** */

void editor_init(Conf conf, Scene scene, Assets assets, SDL_Renderer *ren);
void editor_process(Conf conf, Scene *scenes, Input input, Assets assets, SDL_Renderer *ren, SDL_Rect win_rect);

/* **************************************************************** */

#endif /* EDITOR_H */