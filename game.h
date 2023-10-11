#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "state.h"
#include "input.h"
#include "vec.h"
#include "dir.h"
#include "list.h"
#include "math_utils.h"
#include "floor.h"
#include "object.h"
#include "sprite.h"
#include "animation.h"
#include "action.h"
#include "skill.h"
#include "texture.h"
#include "sound.h"
#include "music.h"
#include "textures.h"
#include "sounds.h"
#include "musics.h"

void init_sdl (Window** window, Renderer** renderer);
void destroy_sdl (Window* window, Renderer* renderer);

void render (Renderer* renderer, State* state, Input* input, Textures* textures);

void draw_line (Renderer* renderer, vec2f start, vec2f end);
void draw_rectangle (Renderer* renderer, vec2f start, vec2f dims);

void draw_gamemap(Renderer* renderer, State* state, Textures* textures);

#endif