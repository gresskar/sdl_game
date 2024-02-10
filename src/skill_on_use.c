#include "../inc/state.h"

void skill_on_use(
    State* state,
    int skill,
    Vec2i source_tilemap_pos,
    Vec2i target_1_tilemap_pos,
    Vec2i target_2_tilemap_pos,
    Textures* textures,
    Colors* colors
)
{
    Object* source_object = room_get_object_at(state->curr_room, source_tilemap_pos);
    Object* target_1_object = room_get_object_at(state->curr_room, target_1_tilemap_pos);
    Object* target_2_object = room_get_object_at(state->curr_room, target_2_tilemap_pos);

    switch (skill)
    {
        case SKILL__PICK_ITEM_CLOSE:
        case SKILL__PICK_ITEM_FAR:
        {
            int item_type = 0;
            int item_count = 0;

            if(target_2_object != 0)
            {
                item_type = get_object_item_type(target_2_object);
                item_count = get_object_item_count(target_2_object);
            }
            else
            {
                int floor = room_get_floor_at(state->curr_room, target_2_tilemap_pos);
                item_type = get_floor_item_type(floor);
                item_count = get_floor_item_count(floor);
            }

            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                state->hero_item_number[item_type] += item_count;
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY)
            {
                switch(item_type)
                {
                    case ITEM__CELL: source_object->type = OBJECT_TYPE__MINIBOT_ALLY_CELL; break;
                    case ITEM__DYNAMITE: source_object->type = OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE; break;
                    case ITEM__GEMSTONE: source_object->type = OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE; break;
                    default:break;
                }
            }
        }
        break;
        case SKILL__PUT_ITEM_CELL_CLOSE:
        case SKILL__PUT_ITEM_CELL_FAR:
        {
            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                if(state->hero_item_number[ITEM__CELL] >= 1)
                {
                    state->hero_item_number[ITEM__CELL]--;
                }
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY_CELL ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE)
            {
                source_object->type = OBJECT_TYPE__MINIBOT_ALLY;
            }
        }
        break;
        case SKILL__PUT_ITEM_DYNAMITE_CLOSE:
        case SKILL__PUT_ITEM_DYNAMITE_FAR:
        {
            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                if(state->hero_item_number[ITEM__DYNAMITE] >= 1)
                {
                    state->hero_item_number[ITEM__DYNAMITE]--;
                }
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY_CELL ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE)
            {
                source_object->type = OBJECT_TYPE__MINIBOT_ALLY;
            }
        }
        break;
        case SKILL__PUT_ITEM_GEMSTONE_CLOSE:
        case SKILL__PUT_ITEM_GEMSTONE_FAR:
        {
            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                if(state->hero_item_number[ITEM__GEMSTONE] >= 1)
                {
                    state->hero_item_number[ITEM__GEMSTONE]--;
                }
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY_CELL ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE)
            {
                source_object->type = OBJECT_TYPE__MINIBOT_ALLY;
            }
        }
        break;
        case SKILL__THROW_ITEM_CELL:
        {
            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                if(state->hero_item_number[ITEM__CELL] >= 1)
                {
                    state->hero_item_number[ITEM__CELL]--;
                }
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY_CELL ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE)
            {
                source_object->type = OBJECT_TYPE__MINIBOT_ALLY;
            }
        }
        break;
        case SKILL__THROW_ITEM_DYNAMITE:
        {
            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                if(state->hero_item_number[ITEM__DYNAMITE] >= 1)
                {
                    state->hero_item_number[ITEM__DYNAMITE]--;
                }
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY_CELL ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE)
            {
                source_object->type = OBJECT_TYPE__MINIBOT_ALLY;
            }
        }
        break;
        case SKILL__THROW_ITEM_GEMSTONE:
        {
            if(source_object->type == OBJECT_TYPE__HERO ||
            source_object->type == OBJECT_TYPE__HERO_FLOATING ||
            source_object->type == OBJECT_TYPE__HERO_FLYING)
            {
                if(state->hero_item_number[ITEM__GEMSTONE] >= 1)
                {
                    state->hero_item_number[ITEM__GEMSTONE]--;
                }
            }
            else if(source_object->type == OBJECT_TYPE__MINIBOT_ALLY_CELL ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_DYNAMITE ||
            source_object->type == OBJECT_TYPE__MINIBOT_ALLY_GEMSTONE)
            {
                source_object->type = OBJECT_TYPE__MINIBOT_ALLY;
            }
        }
        break;
        case SKILL__USE:
        {
            if(target_2_object != 0)
            {
                if(is_object_station(target_2_object))
                {
                    if(state->curr_ally->object->type == OBJECT_TYPE__HERO ||
                    state->curr_ally->object->type == OBJECT_TYPE__HERO_FLOATING ||
                    state->curr_ally->object->type == OBJECT_TYPE__HERO_FLYING)
                    {
                        int augmentation = get_station_augmentation(target_2_object);
                        hero_add_augmentation(state, augmentation);
                    }
                }
                else if(is_object_exit(target_2_object))
                {
                    Passage* passage = get_passage(
                        state,
                        state->curr_room->name,
                        target_2_tilemap_pos
                        );

                    if(passage != 0)
                    {
                        Room* room = get_room(state, passage->to_room_name);

                        if(room != 0)
                        {
                            // travel
                            room_remove_object(
                                state->curr_room,
                                state->curr_ally->object,
                                0);
                            set_curr_room(state, room);
                            room_add_object_at(
                                room,
                                state->curr_ally->object,
                                passage->to_tilemap_pos);

                            // all enemies
                            update_enemy_list(state);
                            update_all_enemy_order(state);
                            for(ListElem* curr_elem = state->enemy_list->head;
                            curr_elem != 0; curr_elem = curr_elem->next)
                            {
                                Enemy* curr_enemy = (Enemy*) curr_elem->data;
                                update_enemy_attack_dir4(state, curr_enemy);
                                update_enemy_attack_targets(state, curr_enemy);
                                update_enemy_draw(state, curr_enemy, textures, colors);
                            }

                            // all allies
                            update_ally_list(state);
                            for(ListElem* curr_elem = state->ally_list->head;
                            curr_elem != 0; curr_elem = curr_elem->next)
                            {
                                Ally* curr_ally = (Ally*) curr_elem->data;
                                update_ally_skill_list(state, curr_ally);
                            }

                            // curr ally
                            int was_prev_ally_chosen = 0;
                            for(ListElem* curr_elem = state->ally_list->head;
                            !was_prev_ally_chosen && curr_elem != 0;
                            curr_elem = curr_elem->next)
                            {
                                Ally* curr_ally = (Ally*) curr_elem->data;
                                if(curr_ally != 0)
                                {
                                    if(curr_ally->object != 0 &&
                                    curr_ally->object == state->curr_ally_object)
                                    {
                                        state->curr_ally_list_elem = curr_elem;
                                        state->curr_ally = curr_ally;
                                        state->curr_ally_object = curr_ally->object;
                                        was_prev_ally_chosen = 1;
                                    }
                                }
                            }
                            if(!was_prev_ally_chosen)
                            {
                                state->curr_ally_list_elem = state->ally_list->head;
                                state->curr_ally = state->curr_ally_list_elem->data;
                                state->curr_ally_object = state->curr_ally->object;
                            }
                        }
                    }
                }
            }
            else
            {
                int floor = room_get_floor_at(state->curr_room, target_2_tilemap_pos);

                if(floor != FLOOR_TYPE__NONE)
                {
                    if(is_floor_exit(floor))
                    {
                        Passage* passage = get_passage(
                            state,
                            state->curr_room->name,
                            target_2_tilemap_pos
                            );

                        if(passage != 0)
                        {
                            Room* room = get_room(state, passage->to_room_name);

                            if(room != 0)
                            {
                                // travel
                                room_remove_object(
                                    state->curr_room,
                                    state->curr_ally->object,
                                    0);
                                set_curr_room(state, room);
                                room_add_object_at(
                                    room,
                                    state->curr_ally->object,
                                    passage->to_tilemap_pos);

                                // all enemies
                                update_enemy_list(state);
                                update_all_enemy_order(state);
                                for(ListElem* curr_elem = state->enemy_list->head;
                                curr_elem != 0; curr_elem = curr_elem->next)
                                {
                                    Enemy* curr_enemy = (Enemy*) curr_elem->data;
                                    update_enemy_attack_dir4(state, curr_enemy);
                                    update_enemy_attack_targets(state, curr_enemy);
                                    update_enemy_draw(state, curr_enemy, textures, colors);
                                }

                                // all allies
                                update_ally_list(state);
                                for(ListElem* curr_elem = state->ally_list->head;
                                curr_elem != 0; curr_elem = curr_elem->next)
                                {
                                    Ally* curr_ally = (Ally*) curr_elem->data;
                                    update_ally_skill_list(state, curr_ally);
                                }

                                // curr ally
                                int was_prev_ally_chosen = 0;
                                for(ListElem* curr_elem = state->ally_list->head;
                                !was_prev_ally_chosen && curr_elem != 0;
                                curr_elem = curr_elem->next)
                                {
                                    Ally* curr_ally = (Ally*) curr_elem->data;
                                    if(curr_ally != 0)
                                    {
                                        if(curr_ally->object != 0 &&
                                        curr_ally->object == state->curr_ally_object)
                                        {
                                            state->curr_ally_list_elem = curr_elem;
                                            state->curr_ally = curr_ally;
                                            state->curr_ally_object = curr_ally->object;
                                            was_prev_ally_chosen = 1;
                                        }
                                    }
                                }
                                if(!was_prev_ally_chosen)
                                {
                                    state->curr_ally_list_elem = state->ally_list->head;
                                    state->curr_ally = state->curr_ally_list_elem->data;
                                    state->curr_ally_object = state->curr_ally->object;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
        default:
        break;
    }
}
