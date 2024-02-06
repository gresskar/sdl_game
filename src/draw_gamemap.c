#include "../inc/game.h"

void draw_gamemap(Renderer* renderer, State* state, Textures* textures, Colors* colors)
{
    // floors, highlights

    for(int i = 0 ; i < TILEMAP_LENGTH ; i++)
    {
        for(int j = 0 ; j < TILEMAP_LENGTH ; j++)
        {
            Vec2i tilemap_pos = vec2i(j,i);
            Vec2f gamemap_pos = tilemap_pos_to_gamemap_pos(tilemap_pos);
            Vec2f world_cart_pos = gamemap_pos_to_world_pos(gamemap_pos);
            Vec2f world_iso_pos = cart_pos_to_iso_pos(world_cart_pos);

            int floor = state->curr_room->floor_array[i][j];
            Texture* tile_floor_texture = 0;
            if(sin(state->time * 3) > 0)
            {
                tile_floor_texture = get_texture_1_from_floor_type(floor, textures);
            }
            else
            {
                tile_floor_texture = get_texture_2_from_floor_type(floor, textures);
            }

            // tile

            draw_texture_at_world_pos(
                renderer,
                tile_floor_texture,
                colors->none,
                1.0f,
                world_iso_pos,
                state->camera.world_pos,
                state->camera.zoom
                );

            // possible target 1

            if(state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_1)
            {
                if(is_tilemap_pos_in_possible_target_1_tilemap_pos_list(state, tilemap_pos))
                {
                    draw_texture_at_world_pos(
                        renderer,
                        textures->floor.highlight,
                        colors->orange,
                        1.0f,
                        world_iso_pos,
                        state->camera.world_pos,
                        state->camera.zoom
                        );
                }
            }

            // possible target 2

            if(state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_2)
            {
                if(is_tilemap_pos_in_possible_target_2_tilemap_pos_list(state, tilemap_pos))
                {
                    draw_texture_at_world_pos(
                        renderer,
                        textures->floor.highlight,
                        colors->pink,
                        1.0f,
                        world_iso_pos,
                        state->camera.world_pos,
                        state->camera.zoom
                        );
                }
            }

            // selected

            if(state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_1 || state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_2)
            {
                if(state->gamemap.curr_selected_tilemap_pos.x == j && state->gamemap.curr_selected_tilemap_pos.y == i)
                {
                    draw_texture_at_world_pos(
                        renderer,
                        textures->floor.highlight,
                        colors->yellow,
                        1.0f,
                        world_iso_pos,
                        state->camera.world_pos,
                        state->camera.zoom
                        );
                }
            }
        }
    }

    // enemy skill draw below

    if(state->gamestate != GAMESTATE__HERO_CHOOSING_TARGET_1 &&
    state->gamestate != GAMESTATE__HERO_CHOOSING_TARGET_2 &&
    state->gamestate != GAMESTATE__HERO_EXECUTING_ANIMATION &&
    state->gamestate != GAMESTATE__ENEMY_EXECUTING_ANIMATION &&
    state->gamestate != GAMESTATE__ENEMY_EXECUTING_ATTACK &&
    state->gamestate != GAMESTATE__HERO_EXECUTING_SKILL)
    {
        Object* hover_object = room_get_object_at(state->curr_room, state->mouse.tilemap_pos);
        Enemy* hover_enemy = get_enemy_of_object(state, hover_object);

        if(hover_object != 0 &&
        is_object_enemy(hover_object) &&
        !hover_object->is_dead &&
        hover_object->is_visible)
        {
            skill_draw_below(
                renderer,
                state,
                hover_enemy->skill,
                hover_object->tilemap_pos,
                hover_enemy->target_1_tilemap_pos,
                hover_enemy->target_2_tilemap_pos,
                colors->yellow,
                textures
                );

            skill_draw_effect(
                renderer,
                state,
                hover_enemy->skill,
                hover_object->tilemap_pos,
                hover_enemy->target_1_tilemap_pos,
                hover_enemy->target_2_tilemap_pos,
                textures,
                colors
                );
        }
        else
        {
            for(ListElem* curr_elem = state->curr_room->object_list->head; curr_elem != 0; curr_elem = curr_elem->next)
            {
                Object* curr_object = (Object*) curr_elem->data;
                Enemy* curr_enemy = get_enemy_of_object(state, curr_object);

                if(curr_enemy != 0)
                {
                    Action* curr_action = curr_enemy->action_sequence;

                    if(!curr_enemy->performed_attack)
                    {
                        if(!(state->gamestate == GAMESTATE__ENEMY_EXECUTING_ATTACK &&
                        state->action.enemy_action_sequence == curr_action) &&
                        !(state->gamestate == GAMESTATE__ENEMY_MOVING &&
                        state->action.enemy_action_sequence == curr_action))
                        {
                            skill_draw_below(
                                renderer,
                                state,
                                curr_enemy->skill,
                                curr_enemy->object->tilemap_pos,
                                curr_enemy->target_1_tilemap_pos,
                                curr_enemy->target_2_tilemap_pos,
                                colors->red,
                                textures
                                );
                        }
                    }
                }
            }
        }
    }

    if(state->gamestate == GAMESTATE__ENEMY_PAUSE_BEFORE_ATTACK)
    {
        Enemy* curr_enemy = state->gamemap.curr_enemy;

        if(curr_enemy != 0 &&
        !curr_enemy->object->is_dead &&
        curr_enemy->object->is_visible)
        {
            skill_draw_below(
                renderer,
                state,
                curr_enemy->skill,
                curr_enemy->object->tilemap_pos,
                curr_enemy->target_1_tilemap_pos,
                curr_enemy->target_2_tilemap_pos,
                colors->yellow,
                textures
                );
        }
    }

    // hero skill draw below

    if(state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_2)
    {
        skill_draw_below(
            renderer,
            state,
            state->gamemap.curr_skill,
            state->gamemap.object_hero->tilemap_pos,
            state->gamemap.target_1_tilemap_pos,
            state->gamemap.target_2_tilemap_pos,
            colors->green,
            textures
            );
    }

    // objects, sprites

    for(int i = 0 ; i < TILEMAP_LENGTH ; i++)
    {
        for(int j = 0 ; j < TILEMAP_LENGTH ; j++)
        {
            Vec2i tilemap_pos = vec2i(j,i);
            Vec2f gamemap_pos = tilemap_pos_to_gamemap_pos(tilemap_pos);
            Vec2f world_cart_pos = gamemap_pos_to_world_pos(gamemap_pos);
            Vec2f world_iso_pos = cart_pos_to_iso_pos(world_cart_pos);

            // objects

            for(ListElem* curr_elem = state->curr_room->object_list->head; curr_elem != 0; curr_elem = curr_elem->next)
            {
                Object* curr_object = (Object*)curr_elem->data;
                Enemy* curr_enemy = get_enemy_of_object(state, curr_object);

                if(!curr_object->is_dead &&
                curr_object->is_visible &&
                curr_object->tilemap_pos.x == j &&
                curr_object->tilemap_pos.y == i)
                {
                    Texture* texture = 0;
                    if(sin(state->time * 3) > 0)
                    {
                        texture = get_texture_1_from_object(curr_object, textures);
                    }
                    else
                    {
                        texture = get_texture_2_from_object(curr_object, textures);
                    }

                    draw_texture_at_world_pos(
                        renderer,
                        texture,
                        colors->none,
                        1.0f,
                        world_iso_pos,
                        state->camera.world_pos,
                        state->camera.zoom
                        );

                    if(curr_enemy != 0 &&
                    state->gamemap.show_all_order_numbers)
                    {
                        draw_texture_at_world_pos(
                            renderer,
                            get_texture_order_number(textures, curr_enemy->order_number),
                            colors->yellow,
                            1.0f,
                            world_iso_pos,
                            state->camera.world_pos,
                            state->camera.zoom
                            );
                    }
                }
            }

            // sprites

            for(ListElem* curr_elem = state->gamemap.sprite_list->head; curr_elem != 0; curr_elem = curr_elem->next)
            {
                Sprite* curr_sprite = (Sprite*)curr_elem->data;
                Vec2i curr_sprite_tilemap_pos = vec2i(
                    floor(curr_sprite->gamemap_pos.x + 0.4f),
                    floor(curr_sprite->gamemap_pos.y + 0.4f)
                    );

                if(curr_sprite_tilemap_pos.x == tilemap_pos.x && curr_sprite_tilemap_pos.y == tilemap_pos.y)
                {
                    Vec2f gamemap_pos = vec2f(curr_sprite->gamemap_pos.x,curr_sprite->gamemap_pos.y);
                    Vec2f world_cart_pos = gamemap_pos_to_world_pos(gamemap_pos);
                    Vec2f world_iso_pos = cart_pos_to_iso_pos(world_cart_pos);
                    world_iso_pos.y += curr_sprite->gamemap_pos.z * (TILE_LENGTH * 0.5f);

                    draw_texture_at_world_pos(
                        renderer,
                        curr_sprite->texture,
                        colors->none,
                        1.0f,
                        world_iso_pos,
                        state->camera.world_pos,
                        state->camera.zoom
                        );
                }
            }
        }
    }

    // enemy skill draw above

    if(state->gamestate != GAMESTATE__HERO_CHOOSING_TARGET_1 &&
    state->gamestate != GAMESTATE__HERO_CHOOSING_TARGET_2 &&
    state->gamestate != GAMESTATE__HERO_EXECUTING_ANIMATION &&
    state->gamestate != GAMESTATE__ENEMY_EXECUTING_ANIMATION &&
    state->gamestate != GAMESTATE__ENEMY_EXECUTING_ATTACK &&
    state->gamestate != GAMESTATE__HERO_EXECUTING_SKILL)
    {
        Object* hover_object = room_get_object_at(state->curr_room, state->mouse.tilemap_pos);
        Enemy* hover_enemy = get_enemy_of_object(state, hover_object);

        if(hover_enemy != 0 &&
        !hover_enemy->object->is_dead &&
        hover_enemy->object->is_visible)
        {
            skill_draw_above(
                renderer,
                state,
                hover_enemy->skill,
                hover_object->tilemap_pos,
                hover_enemy->target_1_tilemap_pos,
                hover_enemy->target_2_tilemap_pos,
                colors->yellow,
                textures
                );

            skill_draw_effect(
                renderer,
                state,
                hover_enemy->skill,
                hover_object->tilemap_pos,
                hover_enemy->target_1_tilemap_pos,
                hover_enemy->target_2_tilemap_pos,
                textures,
                colors
                );
        }
        else
        {
            for(ListElem* curr_elem = state->curr_room->object_list->head; curr_elem != 0; curr_elem = curr_elem->next)
            {
                Object* hover_object = (Object*)curr_elem->data;
                Enemy* hover_enemy = get_enemy_of_object(state, hover_object);

                if(hover_enemy != 0)
                {
                    Action* hover_action = hover_enemy->action_sequence;

                    if(!hover_enemy->performed_attack)
                    {
                        if(!(state->gamestate == GAMESTATE__ENEMY_EXECUTING_ATTACK &&
                        state->action.enemy_action_sequence == hover_action) &&
                        !(state->gamestate == GAMESTATE__ENEMY_MOVING &&
                        state->action.enemy_action_sequence == hover_action))
                        {
                            skill_draw_above(
                                renderer,
                                state,
                                hover_enemy->skill,
                                hover_enemy->object->tilemap_pos,
                                hover_enemy->target_1_tilemap_pos,
                                hover_enemy->target_2_tilemap_pos,
                                colors->red,
                                textures
                                );
                        }
                    }
                }
            }
        }
    }

    if(state->gamestate == GAMESTATE__ENEMY_PAUSE_BEFORE_ATTACK)
    {
        Enemy* curr_enemy = state->gamemap.curr_enemy;

        if(curr_enemy != 0 &&
        !curr_enemy->object->is_dead &&
        curr_enemy->object->is_visible)
        {
            skill_draw_above(
                renderer,
                state,
                curr_enemy->skill,
                curr_enemy->object->tilemap_pos,
                curr_enemy->target_1_tilemap_pos,
                curr_enemy->target_2_tilemap_pos,
                colors->yellow,
                textures
                );

            skill_draw_effect(
                renderer,
                state,
                curr_enemy->skill,
                curr_enemy->object->tilemap_pos,
                curr_enemy->target_1_tilemap_pos,
                curr_enemy->target_2_tilemap_pos,
                textures,
                colors
                );
        }
    }

    // hero skill draw above

    if(state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_2)
    {
        skill_draw_above(
            renderer,
            state,
            state->gamemap.curr_skill,
            state->gamemap.object_hero->tilemap_pos,
            state->gamemap.target_1_tilemap_pos,
            state->gamemap.target_2_tilemap_pos,
            colors->green,
            textures
            );
    }

    // yellow outline, order number

    if(state->gamestate == GAMESTATE__HERO_CHOOSING_SKILL)
    {
        Object* hover_object = room_get_object_at(state->curr_room, state->mouse.tilemap_pos);
        Enemy* hover_enemy = get_enemy_of_object(state, hover_object);

        if(hover_object != 0 &&
         !hover_object->is_dead &&
        hover_object->is_visible)
        {
            Vec2i selected_tilemap_pos = state->mouse.tilemap_pos;
            Vec2f selected_gamemap_pos = tilemap_pos_to_gamemap_pos(selected_tilemap_pos);
            Vec2f selected_world_cart_pos = gamemap_pos_to_world_pos(selected_gamemap_pos);
            Vec2f selected_world_iso_pos = cart_pos_to_iso_pos(selected_world_cart_pos);

            Texture* texture_outline = 0;
            if(sin(state->time * 3) > 0)
            {
                texture_outline = get_texture_1_outline_from_object(hover_object, textures);
            }
            else
            {
                texture_outline = get_texture_2_outline_from_object(hover_object, textures);
            }
            draw_texture_at_world_pos(
                renderer,
                texture_outline,
                colors->yellow,
                1.0f,
                selected_world_iso_pos,
                state->camera.world_pos,
                state->camera.zoom
                );

            if(hover_enemy != 0)
            {
                draw_texture_at_world_pos(
                    renderer,
                    get_texture_order_number(textures, hover_enemy->order_number),
                    colors->yellow,
                    1.0f,
                    selected_world_iso_pos,
                    state->camera.world_pos,
                    state->camera.zoom
                    );
            }
        }
    }

    // red outline

    if(state->gamestate == GAMESTATE__ENEMY_PAUSE_BEFORE_ATTACK ||
    state->gamestate == GAMESTATE__ENEMY_PAUSE_BEFORE_MOVE)
    {
        Enemy* enemy = state->gamemap.curr_enemy;

        if(enemy != 0 &&
         !enemy->object->is_dead &&
        enemy->object->is_visible)
        {
            Vec2i selected_tilemap_pos = enemy->object->tilemap_pos;
            Vec2f selected_gamemap_pos = tilemap_pos_to_gamemap_pos(selected_tilemap_pos);
            Vec2f selected_world_cart_pos = gamemap_pos_to_world_pos(selected_gamemap_pos);
            Vec2f selected_world_iso_pos = cart_pos_to_iso_pos(selected_world_cart_pos);

            Texture* texture_outline = 0;
            if(sin(state->time * 3) > 0)
            {
                texture_outline = get_texture_1_outline_from_object(enemy->object, textures);
            }
            else
            {
                texture_outline = get_texture_2_outline_from_object(enemy->object, textures);
            }
            draw_texture_at_world_pos(
                renderer,
                texture_outline,
                colors->red,
                1.0f,
                selected_world_iso_pos,
                state->camera.world_pos,
                state->camera.zoom
                );

            if(state->gamestate == GAMESTATE__ENEMY_PAUSE_BEFORE_ATTACK)
            {
                draw_texture_at_world_pos(
                    renderer,
                    get_texture_order_number(textures, enemy->order_number),
                    colors->yellow,
                    1.0f,
                    selected_world_iso_pos,
                    state->camera.world_pos,
                    state->camera.zoom
                    );
            }
        }
    }

    // enemy skill draw effect

    if(state->gamestate != GAMESTATE__HERO_CHOOSING_TARGET_1 &&
    state->gamestate != GAMESTATE__HERO_CHOOSING_TARGET_2 &&
    state->gamestate != GAMESTATE__HERO_EXECUTING_ANIMATION &&
    state->gamestate != GAMESTATE__ENEMY_EXECUTING_ANIMATION &&
    state->gamestate != GAMESTATE__HERO_EXECUTING_SKILL)
    {
        Object* hover_object = room_get_object_at(state->curr_room, state->mouse.tilemap_pos);
        Enemy* hover_enemy = get_enemy_of_object(state, hover_object);

        if(hover_enemy != 0 &&
        !hover_enemy->object->is_dead &&
        hover_enemy->object->is_visible)
        {
            skill_draw_effect(
                renderer,
                state,
                hover_enemy->skill,
                hover_object->tilemap_pos,
                hover_enemy->target_1_tilemap_pos,
                hover_enemy->target_2_tilemap_pos,
                textures,
                colors
                );
        }
    }

    // hero skill draw effect

    if(state->gamestate == GAMESTATE__HERO_CHOOSING_TARGET_2)
    {
        skill_draw_effect(
            renderer,
            state,
            state->gamemap.curr_skill,
            state->gamemap.object_hero->tilemap_pos,
            state->gamemap.target_1_tilemap_pos,
            state->gamemap.target_2_tilemap_pos,
            textures,
            colors
            );
    }
}
