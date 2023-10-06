#ifndef TEXTURES_H
#define TEXTURES_H

#include "common.h"
#include "texture.h"

typedef struct
{
    Texture* metal;
    Texture* metal_spikes;
    Texture* metal_lava_crack;
    Texture* lava;
    Texture* ice;
    Texture* ice_water_crack;
    Texture* water;

} Textures_Floor;

void load_textures_floor (Renderer* renderer, Textures_Floor* floor);
void destroy_textures_floor (Textures_Floor* floor);

typedef struct
{
    Texture* red;
    Texture* orange;
    Texture* yellow;
    Texture* green;
    Texture* teal;
    Texture* blue;
    Texture* purple;
    Texture* pink;
    Texture* grey;

} Textures_Highlight;

void load_textures_highlight (Renderer* renderer, Textures_Highlight* highlight);
void destroy_textures_highlight (Textures_Highlight* highlight);

typedef struct
{
    Texture* frame_1;
    Texture* frame_2;
    Texture* frame_3;
    Texture* frame_4;
    Texture* frame_5;
    Texture* frame_6;

} Textures_Danger;

void load_textures_danger (Renderer* renderer, Textures_Danger* danger);
void destroy_textures_danger (Textures_Danger* danger);

typedef struct
{
    Texture* up;
    Texture* right;
    Texture* down;
    Texture* left;

} Textures_Move;

void load_textures_move (Renderer* renderer, Textures_Move* move);
void destroy_textures_move (Textures_Move* move);

typedef struct
{
    Texture* up;
    Texture* right;
    Texture* down;
    Texture* left;

} Textures_Push;

void load_textures_push (Renderer* renderer, Textures_Push* push);
void destroy_textures_push (Textures_Push* push);

typedef struct
{
    Texture* up;
    Texture* right;
    Texture* down;
    Texture* left;

} Textures_Crash;

void load_textures_crash (Renderer* renderer, Textures_Crash* crash);
void destroy_textures_crash (Textures_Crash* crash);

typedef struct
{
    Texture* explosion;

} Textures_BlowUp;

void load_textures_blow_up (Renderer* renderer, Textures_BlowUp* blow_up);
void destroy_textures_blow_up (Textures_BlowUp* blow_up);

typedef struct
{
    Texture* thump;

} Textures_Drop;

void load_textures_drop (Renderer* renderer, Textures_Drop* drop);
void destroy_textures_drop (Textures_Drop* drop);

typedef struct
{
    Texture* pillar;
    Texture* barrel;
    Texture* spring;
    Texture* hero;
    Texture* goat;
    Texture* spider;

} Textures_Object;

void load_textures_object (Renderer* renderer, Textures_Object* object);
void destroy_textures_object (Textures_Object* object);

typedef struct
{
    Textures_Floor floor;

    Textures_Highlight highlight;
    Textures_Danger danger;

    Textures_Move move;
    Textures_Push push;
    Textures_Crash crash;
    Textures_BlowUp blow_up;
    Textures_Drop drop;

    Textures_Object object;
    
} Textures;

void load_textures (Renderer* renderer, Textures* textures);
void destroy_textures (Textures* textures);

#endif