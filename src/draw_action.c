#include "../inc/game.h"

void draw_action(Renderer* renderer, State* state, Action* action, Vec3i color, Textures* textures, Colors* colors)
{
    Vec2i tilemap_pos = action->tilemap_pos;
    Vec2f gamemap_pos = tilemap_pos_to_gamemap_pos(tilemap_pos);
    Vec2f world_cart_pos = gamemap_pos_to_world_pos(gamemap_pos);
    Vec2f world_iso_pos = cart_pos_to_iso_pos(world_cart_pos);

    switch(action->type)
    {
        case ACTION__NONE:
        {
            //
        }
        break;
        case ACTION__SEQUENCE:
        {
            for(ListElem* curr_elem = action->sequence.action_list->head; curr_elem; curr_elem = curr_elem->next)
            {
                Action* curr_action = (Action*) curr_elem->data;
                draw_action(renderer, state, curr_action, color, textures, colors);
            }
        }
        break;
        case ACTION__SIMULTANEOUS:
        {
            for(ListElem* curr_elem = action->simultaneous.action_list->head; curr_elem; curr_elem = curr_elem->next)
            {
                Action* curr_action = (Action*) curr_elem->data;
                draw_action(renderer, state, curr_action, color, textures, colors);
            }
        }
        break;
        case ACTION__MOVE:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__CRASH:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__FALL:
        {
            draw_texture_at_world_pos(
                renderer,
                textures->skill.fall,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__DEATH:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__BLOW_UP:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__THROW:
        {
            Vec2i target_tilemap_pos = vec2i_move_in_dir4_by(action->tilemap_pos, action->throww.dir4, action->throww.distance);
            Vec2f target_gamemap_pos = tilemap_pos_to_gamemap_pos(target_tilemap_pos);
            Vec2f target_world_cart_pos = gamemap_pos_to_world_pos(target_gamemap_pos);
            Vec2f target_world_iso_pos = cart_pos_to_iso_pos(target_world_cart_pos);

            draw_texture_at_world_pos(
                renderer,
                get_texture_throw(textures, action->throww.dir4),
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );

            draw_texture_at_world_pos(
                renderer,
                textures->skill.drop,
                color,
                1.0f,
                target_world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__LIFT:
        {
            draw_texture_at_world_pos(
                renderer,
                get_texture_lift(textures, action->lift.dir4),
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__DROP:
        {
            draw_texture_at_world_pos(
                renderer,
                textures->skill.drop,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__CHANGE_FLOOR:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__CHANGE_OBJECT:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__ADD_OBJECT:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        case ACTION__REMOVE_OBJECT:
        {
            draw_texture_at_world_pos(
                renderer,
                0,
                color,
                1.0f,
                world_iso_pos,
                state->camera_world_pos,
                state->camera_zoom
            );
        }
        break;
        default:
        break;
    }
}
