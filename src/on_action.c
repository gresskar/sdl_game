#include "../inc/state.h"

void floor_on_move_start(State* state, Action* sequence, Action* action, int floor)
{
    switch(floor)
    {
        case FLOOR_TYPE__ROCK_CRACK_WATER:
        {
            if(!is_object_flying(action->move.object))
            {
                room_change_floor_at(state->curr_room, FLOOR_TYPE__WATER, action->move.object->tilemap_pos);
            }
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_LAVA:
        {
            if(!is_object_flying(action->move.object))
            {
                room_change_floor_at(state->curr_room, FLOOR_TYPE__LAVA, action->move.object->tilemap_pos);
            }
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_PIT:
        {
            if(!is_object_flying(action->move.object))
            {
                room_change_floor_at(state->curr_room, FLOOR_TYPE__PIT, action->move.object->tilemap_pos);
            }
        }
        break;
        case FLOOR_TYPE__ICE_CRACK_WATER:
        {
            if(!is_object_flying(action->move.object))
            {
                room_change_floor_at(state->curr_room, FLOOR_TYPE__WATER, action->move.object->tilemap_pos);
            }
        }
        break;
        default:
        break;
    }
}

void floor_on_move_end(State* state, Action* sequence, Action* action, int floor)
{
    switch(floor)
    {
        case FLOOR_TYPE__METAL_TARGET_UNCHECKED:
        {
            if(!is_object_flying(action->move.object))
            {
                add_action_after_curr_action_action_sequence(
                    sequence,
                    new_action_change_floor(
                        FLOOR_TYPE__METAL_TARGET_CHECKED,
                        vec2i_move_in_dir4_by(action->tilemap_pos, action->move.dir4, 1)
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__STONE_SPIKES_ON:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_after_curr_action_action_sequence(sequence, new_action_death(action->move.object, vec2i_move_in_dir4_by(action->tilemap_pos, action->move.dir4, 1)));
            }
        }
        break;
        case FLOOR_TYPE__STONE_TRAP:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_after_curr_action_action_sequence(sequence, new_action_death(action->move.object, vec2i_move_in_dir4_by(action->tilemap_pos, action->move.dir4, 1)));
                add_action_after_curr_action_action_sequence(sequence, new_action_change_floor(FLOOR_TYPE__STONE, vec2i_move_in_dir4_by(action->tilemap_pos, action->move.dir4, 1)));
            }
        }
        break;
        case FLOOR_TYPE__ICE:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_to_end_action_sequence(sequence, new_action_move( vec2i_move_in_dir4_by(action->tilemap_pos, action->move.dir4, 1), action->move.dir4));
            }
        }
        break;
        case FLOOR_TYPE__ICE_CRACK_WATER:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_to_end_action_sequence(sequence, new_action_move( vec2i_move_in_dir4_by(action->tilemap_pos, action->move.dir4, 1), action->move.dir4));
            }
        }
        break;
        case FLOOR_TYPE__WATER:
        case FLOOR_TYPE__LAVA:
        {
            if(!is_object_floating(action->move.object) &&
            !is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_fall(
                        action->move.object,
                        vec2i_move_in_dir4_by(
                            action->tilemap_pos,
                            action->move.dir4,
                            1
                            )
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__PIT:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_fall(
                        action->move.object,
                        vec2i_move_in_dir4_by(
                            action->tilemap_pos,
                            action->move.dir4,
                            1
                            )
                        )
                    );
            }
        }
        break;
        default:
        break;
    }
}

void floor_on_drop(State* state, Action* sequence, Action* action, int floor)
{
    switch(floor)
    {
        case FLOOR_TYPE__METAL_TARGET_UNCHECKED:
        {
            if(!is_object_flying(action->move.object))
            {
                add_action_after_curr_action_action_sequence(
                    sequence,
                    new_action_change_floor(
                        FLOOR_TYPE__METAL_TARGET_CHECKED,
                        action->tilemap_pos
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__STONE_SPIKES_ON:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_after_curr_action_action_sequence(
                    sequence,
                    new_action_death(
                        action->move.object,
                        action->tilemap_pos
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__STONE_TRAP:
        {
            if(!is_object_flying(action->move.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                add_action_after_curr_action_action_sequence(
                    sequence,
                    new_action_death(
                        action->move.object,
                        action->tilemap_pos
                        )
                    );
                add_action_after_curr_action_action_sequence(
                    sequence,
                    new_action_change_floor(
                        FLOOR_TYPE__STONE,
                        action->tilemap_pos
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_WATER:
        {
            if(!is_object_floating(action->drop.object) &&
            !is_object_flying(action->drop.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                room_change_floor_at(
                    state->curr_room,
                    FLOOR_TYPE__WATER,
                    action->tilemap_pos
                    );
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_fall(
                        action->drop.object,
                        action->tilemap_pos
                        )
                    );
            }
            else if(is_object_floating(action->drop.object))
            {
                room_change_floor_at(
                    state->curr_room,
                    FLOOR_TYPE__WATER,
                    action->tilemap_pos
                    );
            }
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_LAVA:
        {
            if(!is_object_floating(action->drop.object) &&
            !is_object_flying(action->drop.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                room_change_floor_at(
                    state->curr_room,
                    FLOOR_TYPE__LAVA,
                    action->tilemap_pos
                    );
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_fall(
                        action->drop.object,
                        action->tilemap_pos
                        )
                    );
            }
            else if(is_object_floating(action->drop.object))
            {
                room_change_floor_at(
                    state->curr_room,
                    FLOOR_TYPE__LAVA,
                    action->tilemap_pos
                    );
            }
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_PIT:
        {
            if(!is_object_flying(action->drop.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                room_change_floor_at(
                    state->curr_room,
                    FLOOR_TYPE__PIT,
                    action->tilemap_pos
                    );
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_fall(
                        action->drop.object,
                        action->tilemap_pos
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__ICE:
        {
            if(!is_object_flying(action->drop.object))
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_move(
                        action->tilemap_pos,
                        action->drop.dir4
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__ICE_CRACK_WATER:
        {
            if(!is_object_floating(action->drop.object) &&
            !is_object_flying(action->drop.object))
            {
                remove_all_actions_after_curr_action_action_sequence(sequence);
                room_change_floor_at(
                    state->curr_room,
                    FLOOR_TYPE__WATER,
                    action->tilemap_pos
                    );
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_fall(
                        action->drop.object,
                        action->tilemap_pos
                        )
                    );
            }
            else if(is_object_floating(action->drop.object) &&
            !is_object_flying(action->drop.object))
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_move(
                        action->tilemap_pos,
                        action->drop.dir4
                        )
                    );
            }
        }
        break;
        case FLOOR_TYPE__WATER:
        case FLOOR_TYPE__LAVA:
        case FLOOR_TYPE__PIT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_fall(
                    action->drop.object,
                    action->tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void floor_on_stomp(State* state, Action* sequence, int floor, Vec2i tilemap_pos)
{
    switch(floor)
    {
        case FLOOR_TYPE__STONE_STAIRS_BELOW_BLOCKED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__STONE_STAIRS_BELOW,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__WATER_LILY_POD:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__WATER,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__STONE_TRAP:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__STONE,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__ICE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__ICE_CRACK_WATER,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__ICE_CRACK_WATER:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__WATER,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_WATER:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__WATER,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_LAVA:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__LAVA,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__ROCK_CRACK_PIT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__PIT,
                    tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void floor_on_manipulation(State* state, Action* sequence, int floor, Vec2i tilemap_pos)
{
    switch(floor)
    {
        case FLOOR_TYPE__METAL_PISTON:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_add_object(
                    new_object(OBJECT_TYPE__PISTON),
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_PISTON_CELL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_add_object(
                    new_object(OBJECT_TYPE__PISTON_CELL),
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_PISTON_DYNAMITE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_add_object(
                    new_object(OBJECT_TYPE__PISTON_DYNAMITE),
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_add_object(
                    new_object(OBJECT_TYPE__PISTON_BARREL),
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__STONE_SPIKES_OFF:
        {
            add_action_to_end_action_sequence(sequence, new_action_change_floor(FLOOR_TYPE__STONE_SPIKES_ON, tilemap_pos));
        }
        break;
        case FLOOR_TYPE__STONE_SPIKES_ON:
        {
            add_action_to_end_action_sequence(sequence, new_action_change_floor(FLOOR_TYPE__STONE_SPIKES_OFF, tilemap_pos));
        }
        break;
        case FLOOR_TYPE__METAL_HATCH_CLOSED:
        {
            add_action_to_end_action_sequence(sequence, new_action_change_floor(FLOOR_TYPE__METAL_HATCH_OPEN, tilemap_pos));
        }
        break;
        case FLOOR_TYPE__METAL_HATCH_OPEN:
        {
            add_action_to_end_action_sequence(sequence, new_action_change_floor(FLOOR_TYPE__METAL_HATCH_CLOSED, tilemap_pos));
        }
        break;
        case FLOOR_TYPE__METAL_STAIRS_ABOVE_OFF:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_add_object(
                    new_object(OBJECT_TYPE__STAIRS_ABOVE_METAL_ON),
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_STAIRS_BELOW_OFF:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_STAIRS_BELOW_ON,
                    tilemap_pos
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_STAIRS_BELOW_ON:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_STAIRS_BELOW_OFF,
                    tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

Animation* floor_on_manipulation_get_animation(State* state, int floor, Vec2i tilemap_pos, Textures* textures)
{
    Animation* animation = new_animation_none();

    switch(floor)
    {
        case FLOOR_TYPE__METAL_PISTON:
        {
            //
        }
        break;
        case FLOOR_TYPE__STONE_SPIKES_OFF:
        {
            animation = new_animation_sequence_of_2(
                new_animation_show_sprite_in_gamemap(
                    textures->animation.stone_spikes_1,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    ),
                new_animation_show_sprite_in_gamemap(
                    textures->animation.stone_spikes_2,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    )
                );
        }
        break;
        case FLOOR_TYPE__STONE_SPIKES_ON:
        {
            animation = new_animation_sequence_of_2(
                new_animation_show_sprite_in_gamemap(
                    textures->animation.stone_spikes_2,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    ),
                new_animation_show_sprite_in_gamemap(
                    textures->animation.stone_spikes_1,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_HATCH_CLOSED:
        {
            animation = new_animation_sequence_of_2(
                new_animation_show_sprite_in_gamemap(
                    textures->animation.metal_hatch_2,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    ),
                new_animation_show_sprite_in_gamemap(
                    textures->animation.metal_hatch_1,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_HATCH_OPEN:
        {
            animation = new_animation_sequence_of_2(
                new_animation_show_sprite_in_gamemap(
                    textures->animation.metal_hatch_1,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    ),
                new_animation_show_sprite_in_gamemap(
                    textures->animation.metal_hatch_2,
                    tilemap_pos_to_gamemap_pos(tilemap_pos),
                    ACTION_LENGTH_IN_SECONDS * 0.5
                    )
                );
        }
        break;
        case FLOOR_TYPE__METAL_STAIRS_ABOVE_OFF:
        {
            //
        }
        break;
        default:
        break;
    }

    return animation;
}

void floor_on_pick_item(State* state, Action* sequence, int floor, Vec2i tilemap_pos)
{
    switch(floor)
    {
        case FLOOR_TYPE__STONE_STAIRS_ABOVE_POWERED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__STONE_STAIRS_ABOVE_UNPOWERED,
                    tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void floor_on_put_item(State* state, Action* sequence, int floor, Vec2i tilemap_pos, int item_type)
{
    switch(floor)
    {
        case FLOOR_TYPE__STONE_STAIRS_ABOVE_UNPOWERED:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_floor(
                        FLOOR_TYPE__STONE_STAIRS_ABOVE_POWERED,
                        tilemap_pos
                        )
                    );

                add_action_to_end_action_sequence(
                    sequence,
                    new_action_add_object(
                        new_object(OBJECT_TYPE__STAIRS_ABOVE_STONE_POWERED),
                        tilemap_pos
                        )
                    );
            }
        }
        break;
        default:
        break;
    }
}

void object_on_crashing(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__PILLAR:
        {
            //
        }
        break;
        case OBJECT_TYPE__BALL_SPIKES:
        {
            if(action->crash.object_crushed->type != OBJECT_TYPE__BARREL &&
            action->crash.object_crushed->type != OBJECT_TYPE__PISTON_BARREL)
            {
                add_action_to_end_action_sequence(sequence, new_action_death(action->crash.object_crushed, action->crash.object_crushed->tilemap_pos));
            }
        }
        break;
        case OBJECT_TYPE__BARREL:
        {
            add_action_to_end_action_sequence(sequence, new_action_death(object, object->tilemap_pos));
        }
        break;
        case OBJECT_TYPE__PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_NO_PISTON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void object_on_crashed(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__BALL_SPIKES:
        {
            if(action->crash.object_crushed->type != OBJECT_TYPE__BARREL &&
            action->crash.object_crushed->type != OBJECT_TYPE__BARREL)
            {
                add_action_to_end_action_sequence(sequence, new_action_death(action->crash.object_crushing, action->crash.object_crushed->tilemap_pos));
            }
        }
        break;
        case OBJECT_TYPE__BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_NO_PISTON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__BALL:
        {
            add_action_to_end_action_sequence(sequence, new_action_move(object->tilemap_pos, action->crash.dir4));
        }
        break;
        default:
        break;
    }
}

void object_on_death(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__PILLAR:
        {
            //
        }
        break;
        case OBJECT_TYPE__BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_blow_up(
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_blow_up(
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_NO_PISTON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void object_on_drop(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__DISPLAY:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(OBJECT_TYPE__DISPLAY_DAMAGED_ITEM, object->tilemap_pos)
                );
        }
        break;
        case OBJECT_TYPE__BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_NO_PISTON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__BALL:
        {
            if(action->drop.dir4 != DIR4__NONE)
            {
                add_action_to_end_action_sequence(sequence, new_action_move( action->tilemap_pos, action->drop.dir4));
            }
        }
        break;
        case OBJECT_TYPE__BALL_SPIKES:
        {
            if(action->drop.dir4 != DIR4__NONE)
            {
                add_action_to_end_action_sequence(sequence, new_action_move( action->tilemap_pos, action->drop.dir4));
            }
        }
        break;
        case OBJECT_TYPE__TURRET_LASER_DEPLOYED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__TURRET_LASER_UNDEPLOYED,
                    action->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__TURRET_BOMB_DEPLOYED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__TURRET_BOMB_UNDEPLOYED,
                    action->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__TURRET_PROJECTILE_DEPLOYED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__TURRET_PROJECTILE_UNDEPLOYED,
                    action->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__TURRET_LASER_UNDEPLOYED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__TURRET_LASER_DEPLOYED,
                    action->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__TURRET_BOMB_UNDEPLOYED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__TURRET_BOMB_DEPLOYED,
                    action->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__TURRET_PROJECTILE_UNDEPLOYED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__TURRET_PROJECTILE_DEPLOYED,
                    action->tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void object_on_melt(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__EXIT_STONE_BLOCKED_UP:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_STONE_UP,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_BLOCKED_RIGHT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_STONE_RIGHT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_BLOCKED_DOWN:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_STONE_DOWN,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__SAFE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(OBJECT_TYPE__SAFE_DAMAGED_ITEM, object->tilemap_pos)
                );
        }
        break;
        case OBJECT_TYPE__VENDING_CELL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__VENDING_CELL_DAMAGED_ITEM,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__VENDING_CELL_ITEM:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__VENDING_CELL_DAMAGED_ITEM,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__VENDING_DYNAMITE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__VENDING_DYNAMITE_DAMAGED_ITEM,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__VENDING_DYNAMITE_ITEM:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__VENDING_DYNAMITE_DAMAGED_ITEM,
                    object->tilemap_pos
                    )
                );
        }
        break;
        default:
        {
            if(is_object_meltable(object))
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_death(object, object->tilemap_pos)
                    );
            }
        }
        break;
    }
}

void object_on_break(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__EXIT_STONE_BLOCKED_LEFT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_STONE_LEFT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_ROCK_BLOCKED_UP:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_ROCK_UP,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_ROCK_BLOCKED_RIGHT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_ROCK_RIGHT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_ROCK_BLOCKED_DOWN:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_ROCK_DOWN,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__ROCK:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(OBJECT_TYPE__ROCK_DAMAGED_ITEM, object->tilemap_pos)
                );
        }
        break;
        default:
        {
            if(is_object_breakable(object))
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_death(object, object->tilemap_pos)
                    );
            }
        }
        break;
    }
}

void object_on_shake(State* state, Action* sequence, Action* action, Object* object)
{
    switch(object->type)
    {
        case OBJECT_TYPE__EXIT_ROCK_BLOCKED_LEFT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_ROCK_LEFT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_BLOCKED_UP:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_UP,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_BLOCKED_RIGHT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_RIGHT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_BLOCKED_DOWN:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_DOWN,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_BLOCKED_LEFT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_LEFT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__DISPLAY:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(OBJECT_TYPE__DISPLAY_DAMAGED_ITEM, object->tilemap_pos)
                );
        }
        break;
        case OBJECT_TYPE__BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_NO_PISTON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__STALACTITE:
        {
            int floor = room_get_floor_at(state->curr_room, action->tilemap_pos);

            switch(floor)
            {
                case FLOOR_TYPE__WATER:
                {
                    add_action_to_end_action_sequence(
                        sequence,
                        new_action_change_floor(
                            FLOOR_TYPE__WATER_STALACTITE_FALLEN,
                            object->tilemap_pos
                            )
                        );

                    add_action_to_end_action_sequence(
                        sequence,
                        new_action_remove_object(
                            object,
                            object->tilemap_pos
                            )
                        );
                }
                break;
                case FLOOR_TYPE__LAVA:
                {
                    add_action_to_end_action_sequence(
                        sequence,
                        new_action_change_floor(
                            FLOOR_TYPE__LAVA_STALACTITE_FALLEN,
                            object->tilemap_pos
                            )
                        );

                    add_action_to_end_action_sequence(
                        sequence,
                        new_action_remove_object(
                            object,
                            object->tilemap_pos
                            )
                        );
                }
                break;
                default:
                {
                    add_action_to_end_action_sequence(
                        sequence,
                        new_action_change_object(
                            OBJECT_TYPE__STALACTITE_FALLEN_ITEM,
                            object->tilemap_pos
                            )
                        );
                }
                break;
            }
        }
        break;
        default:
        break;
    }
}

void object_on_stomp(State* state, Action* sequence, Object* object, Vec2i tilemap_pos)
{
    switch(object->type)
    {
        case OBJECT_TYPE__MINIBOT_ALLY:
        case OBJECT_TYPE__MINIBOT_ALLY_CELL:
        case OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE:
        case OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE:
        case OBJECT_TYPE__MINIBOT_ENEMY:
        case OBJECT_TYPE__MINIBOT_ENEMY_CELL:
        case OBJECT_TYPE__MINIBOT_ENEMY_DYNAMITE:
        case OBJECT_TYPE__MINIBOT_ENEMY_GEMSTONE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_death(
                    object,
                    object->tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

void object_on_manipulate(State* state, Action* sequence, Object* object, Vec2i tilemap_pos)
{
    switch(object->type)
    {
        case OBJECT_TYPE__LEVER_METAL_OFF:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__LEVER_METAL_ON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__LEVER_METAL_ON:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__LEVER_METAL_OFF,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_ON_UP:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_OFF_UP,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_ON_RIGHT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_OFF_RIGHT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_ON_DOWN:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_OFF_DOWN,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_ON_LEFT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_OFF_LEFT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_OFF_UP:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_ON_UP,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_OFF_RIGHT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_ON_RIGHT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_OFF_DOWN:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_ON_DOWN,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_METAL_OFF_LEFT:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__EXIT_METAL_ON_LEFT,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_remove_object(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_PISTON,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_CELL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_remove_object(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_PISTON_CELL,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_DYNAMITE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_remove_object(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_PISTON_DYNAMITE,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__PISTON_BARREL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_remove_object(
                    object,
                    object->tilemap_pos
                    )
                );

            add_action_to_end_action_sequence(
                sequence,
                new_action_change_floor(
                    FLOOR_TYPE__METAL_PISTON_BARREL,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__BALL:
        {
            add_action_to_end_action_sequence(sequence,new_action_change_object(OBJECT_TYPE__BALL_SPIKES, object->tilemap_pos));
        }
        break;
        case OBJECT_TYPE__BALL_SPIKES:
        {
            add_action_to_end_action_sequence(sequence,new_action_change_object(OBJECT_TYPE__BALL, object->tilemap_pos));
        }
        break;
        case OBJECT_TYPE__BARREL:
        {
            add_action_to_end_action_sequence(sequence, new_action_death(object, object->tilemap_pos));
        }
        break;
        case OBJECT_TYPE__STAIRS_ABOVE_METAL_ON:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_remove_object(
                    object,
                    tilemap_pos
                    )
                );
        }
        break;
        default:
        break;
    }
}

Animation* object_on_manipulate_get_animation(State* state, Object* object, Vec2i tilemap_pos, Textures* textures)
{
    Animation* animation = new_animation_none();

    switch(object->type)
    {
        case OBJECT_TYPE__PISTON:
        {
            //
        }
        break;
        default:
        break;
    }

    return animation;
}

void object_on_pick_item(State* state, Action* sequence, Object* object, Vec2i tilemap_pos)
{
    switch(object->type)
    {
        case OBJECT_TYPE__LEVER_STONE_POWERED:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__LEVER_STONE_UNPOWERED,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__MINIBOT_ALLY_CELL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__MINIBOT_ALLY,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__MINIBOT_ALLY,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__MINIBOT_ALLY,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__MINIBOT_ENEMY_CELL:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__MINIBOT_ENEMY,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__MINIBOT_ENEMY_DYNAMITE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__MINIBOT_ENEMY,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__MINIBOT_ENEMY_GEMSTONE:
        {
            add_action_to_end_action_sequence(
                sequence,
                new_action_change_object(
                    OBJECT_TYPE__MINIBOT_ENEMY,
                    object->tilemap_pos
                    )
                );
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_POWERED_UP:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_UNPOWERED_UP,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_POWERED_RIGHT:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_UNPOWERED_RIGHT,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_POWERED_DOWN:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_UNPOWERED_DOWN,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_POWERED_LEFT:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_UNPOWERED_LEFT,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__CRATE_CELL_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__CRATE_CELL_ITEM,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__CRATE_DYNAMITE_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__CRATE_DYNAMITE,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__CRATE_GEMSTONE_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__CRATE_GEMSTONE,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__STALACTITE_FALLEN_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__STALACTITE_FALLEN,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__ROCK_DAMAGED_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__ROCK_DAMAGED,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__SAFE_DAMAGED_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__SAFE_DAMAGED,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__DISPLAY_DAMAGED_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__DISPLAY_DAMAGED,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__VENDING_CELL_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__VENDING_CELL,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__VENDING_CELL_DAMAGED_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__VENDING_CELL_DAMAGED,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__VENDING_DYNAMITE_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__VENDING_DYNAMITE,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__VENDING_DYNAMITE_DAMAGED_ITEM:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__VENDING_DYNAMITE_DAMAGED,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__STAIRS_ABOVE_STONE_POWERED:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_floor(
                        FLOOR_TYPE__STONE_STAIRS_ABOVE_UNPOWERED,
                        tilemap_pos
                        )
                    );

                add_action_to_end_action_sequence(
                    sequence,
                    new_action_remove_object(
                        object,
                        tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__PISTON_CELL:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__PISTON,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        case OBJECT_TYPE__PISTON_DYNAMITE:
        {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__PISTON,
                        object->tilemap_pos
                        )
                    );
        }
        break;
        default:
        break;
    }
}

void object_on_put_item(State* state, Action* sequence, Object* object, Vec2i tilemap_pos, int item_type)
{
    switch(object->type)
    {
        case OBJECT_TYPE__LEVER_STONE_UNPOWERED:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__LEVER_STONE_POWERED,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__MINIBOT_ALLY:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__MINIBOT_ALLY_CELL,
                        object->tilemap_pos
                        )
                    );
            }
            if(item_type == ITEM__DYNAMITE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE,
                        object->tilemap_pos
                        )
                    );
            }
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__MINIBOT_ENEMY:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__MINIBOT_ENEMY_CELL,
                        object->tilemap_pos
                        )
                    );
            }
            if(item_type == ITEM__DYNAMITE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__MINIBOT_ENEMY_DYNAMITE,
                        object->tilemap_pos
                        )
                    );
            }
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__MINIBOT_ENEMY_GEMSTONE,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_UNPOWERED_UP:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_POWERED_UP,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_UNPOWERED_RIGHT:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_POWERED_RIGHT,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_UNPOWERED_DOWN:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_POWERED_DOWN,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_STONE_UNPOWERED_LEFT:
        {
            if(item_type == ITEM__CELL)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_STONE_POWERED_LEFT,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_GOLD_LOCKED_UP:
        {
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_GOLD_UNLOCKED_UP,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_GOLD_LOCKED_RIGHT:
        {
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_GOLD_UNLOCKED_RIGHT,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_GOLD_LOCKED_DOWN:
        {
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_GOLD_UNLOCKED_DOWN,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__EXIT_GOLD_LOCKED_LEFT:
        {
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__EXIT_GOLD_LOCKED_LEFT,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__VENDING_CELL:
        {
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__VENDING_CELL_ITEM,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        case OBJECT_TYPE__VENDING_DYNAMITE:
        {
            if(item_type == ITEM__GEMSTONE)
            {
                add_action_to_end_action_sequence(
                    sequence,
                    new_action_change_object(
                        OBJECT_TYPE__VENDING_DYNAMITE_ITEM,
                        object->tilemap_pos
                        )
                    );
            }
        }
        break;
        default:
        break;
    }
}
