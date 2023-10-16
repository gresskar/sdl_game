#include "../inc/state.h"

void init_state (State* state, Textures* textures, Sounds* sounds, Musics* musics)
{
    state->is_game_running = 1;
    state->gamestate = GAMESTATE__NONE;

    // camera

    state->camera.world_pos = make_vec2f(0, 0);
    state->camera.zoom = 2.0f;

    // mouse

    state->mouse.screen_pos = make_vec2i(0, 0);
    state->mouse.world_pos = make_vec2f(0, 0);
    state->mouse.gamemap_pos = make_vec2f(0, 0);
    state->mouse.tilemap_pos = make_vec2i(0, 0);
    state->mouse.is_dragging = 0;
    state->mouse.drag_origin_world_pos = make_vec2f(0, 0);

    // gamemap

    for(int i = 0 ; i < TILEMAP_HEIGHT ; i++)
    {
        for(int j = 0 ; j < TILEMAP_WIDTH ; j++)
        {
            state->gamemap.tilemap[i][j] = malloc(sizeof(*state->gamemap.tilemap[i][j]));
            state->gamemap.tilemap[i][j]->floor = FLOOR_TYPE__METAL;
        }
    }

    state->gamemap.object_list = new_list((void (*)(void *))&destroy_object);
    state->gamemap.object_enemy_list = new_list((void (*)(void *))&destroy_object);
    state->gamemap.object_hero = new_object(OBJECT_TYPE__HERO);
    state->gamemap.object_hero->tilemap_pos = make_vec2i(11,5);
    add_object_to_gamemap_objects(state, state->gamemap.object_hero);

    state->gamemap.sprite_list = new_list((void (*)(void *))&destroy_sprite);

    state->gamemap.selected_tilemap_pos = make_vec2i(0, 0);

    state->gamemap.curr_skill = 0;
    state->gamemap.is_skill_two_target = 0;

    state->gamemap.possible_target_1_tilemap_pos_list = new_list((void(*)(void*))&destroy_vec2i);
    state->gamemap.possible_target_2_tilemap_pos_list = new_list((void(*)(void*))&destroy_vec2i);

    state->gamemap.enemy_action_sequence_list = new_list((void(*)(void*))&destroy_action);

    state->gamemap.target_1_tilemap_pos = make_vec2i(0, 0);
    state->gamemap.target_2_tilemap_pos = make_vec2i(0, 0);

    // action

    state->action.is_executing_actions = 0;
    state->action.main_action_sequence = new_action_sequence();
}

void change_gamestate(State* state, int new_gamestate)
{
    state->gamestate = new_gamestate;
    printf("\n");
    printf("gamestate: %s \n", get_gamestate_name(new_gamestate));
}

// gamemap

int is_tilemap_pos_in_tilemap(vec2i tilemap_pos)
{
    return (tilemap_pos.x >= 0 && tilemap_pos.x < TILEMAP_WIDTH && tilemap_pos.y >= 0 && tilemap_pos.y < TILEMAP_HEIGHT);
}

Object* get_object_on_tilemap_pos(State* state, vec2i tilemap_pos)
{
    if(!is_tilemap_pos_in_tilemap(tilemap_pos)) return 0;

    for(ListElem* curr_elem = state->gamemap.object_list->head; curr_elem; curr_elem = curr_elem->next)
    {
        Object* curr_object = (Object*)curr_elem->data;
        if(curr_object->tilemap_pos.x == tilemap_pos.x && curr_object->tilemap_pos.y == tilemap_pos.y)
        {
            return curr_object;
        }
    }

    return 0;
}

int get_floor_on_tilemap_pos(State* state, vec2i tilemap_pos)
{
    if(!is_tilemap_pos_in_tilemap(tilemap_pos)) return 0;

    Tile* tile = state->gamemap.tilemap[tilemap_pos.y][tilemap_pos.x];

    return (tile) ? (tile->floor) : (0);
}

void change_floor_in_tilemap_pos(State* state, int new_floor, vec2i tilemap_pos)
{
    if(!is_tilemap_pos_in_tilemap(tilemap_pos)) return;

    Tile* tile = state->gamemap.tilemap[tilemap_pos.y][tilemap_pos.x];

    tile->floor = new_floor;
}

void add_object_to_gamemap_objects(State* state, Object* new_object)
{
    add_new_list_element_to_list_end(state->gamemap.object_list, new_object);

    if(is_object_enemy(new_object->type))
    {
        add_new_list_element_to_list_end(state->gamemap.object_enemy_list, new_object);
    }
}

void remove_object_from_gamemap_objects(State* state, Object* object)
{
    if(is_object_enemy(object->type))
    {
        remove_list_element_of_data(state->gamemap.object_enemy_list, object, 0);
    }

    remove_list_element_of_data(state->gamemap.object_list, object, 1);
}

void remove_all_dead_objects_from_gamemap_objects(State* state)
{
    for(ListElem* curr_elem = state->gamemap.object_list->head; curr_elem; curr_elem = curr_elem->next)
    {
        Object* curr_object = (Object*)curr_elem->data;

        if(curr_object->is_dead)
        {
            remove_object_from_gamemap_objects(state, curr_object);
        }
    }
}

void add_action_sequence_to_gamemap_action_sequence(State* state, Action* new_action_sequence)
{
    add_new_list_element_to_list_end(state->gamemap.enemy_action_sequence_list, new_action_sequence);
}

void remove_action_sequence_from_gamemap_action_sequence(State* state, Action* action_sequence)
{
    remove_list_element_of_data(state->gamemap.enemy_action_sequence_list, action_sequence, 1);
}

void add_sprite_to_gamemap_sprites(State* state, Sprite* new_sprite)
{
    add_new_list_element_to_list_end(state->gamemap.sprite_list, new_sprite);
}

void remove_sprite_from_gamemap_sprites(State* state, Sprite* sprite)
{
    remove_list_element_of_data(state->gamemap.sprite_list, sprite, 1);
}

void add_pos_to_possible_target_1_tilemap_pos_list(State* state, vec2i* new_pos)
{
    add_new_list_element_to_list_end(state->gamemap.possible_target_1_tilemap_pos_list, new_pos);
}

void remove_all_pos_from_possible_target_1_tilemap_pos_list(State* state)
{
    remove_all_list_elements(state->gamemap.possible_target_1_tilemap_pos_list, 1);
}

int is_tilemap_pos_in_possible_target_1_tilemap_pos_list(State* state, vec2i pos)
{
    for(ListElem* curr_elem = state->gamemap.possible_target_1_tilemap_pos_list->head; curr_elem; curr_elem = curr_elem->next )
    {
        vec2i* curr_vec = (vec2i*)curr_elem->data;
        if(curr_vec->x == pos.x && curr_vec->y == pos.y) return 1;
    }

    return 0;
}

void add_pos_to_possible_target_2_tilemap_pos_list(State* state, vec2i* new_pos)
{
    add_new_list_element_to_list_end(state->gamemap.possible_target_2_tilemap_pos_list, new_pos);
}

void remove_all_pos_from_possible_target_2_tilemap_pos_list(State* state)
{
    remove_all_list_elements(state->gamemap.possible_target_2_tilemap_pos_list, 1);
}

int is_tilemap_pos_in_possible_target_2_tilemap_pos_list(State* state, vec2i pos)
{
    for(ListElem* curr_elem = state->gamemap.possible_target_2_tilemap_pos_list->head; curr_elem; curr_elem = curr_elem->next )
    {
        vec2i* curr_vec = (vec2i*)curr_elem->data;
        if(curr_vec->x == pos.x && curr_vec->y == pos.y) return 1;
    }

    return 0;
}

// action

void execute_actions(State* state, Textures* textures, Sounds* sounds, Musics* musics)
{
    state->action.is_executing_actions = 1;
    state->action.main_action_sequence->is_finished = 0;

    start_action(state, state->action.main_action_sequence, state->action.main_action_sequence, textures, sounds, musics);
}

void print_action(Action* action, int depth)
{
    char* action_type = get_action_name_from_type(action->type);
    for(int i = 0; i < depth; i++) printf("  ");
    printf("%s \n", action_type);

    if(action->type != ACTION_TYPE__SEQUENCE && action->type != ACTION_TYPE__SIMULTANEOUS)
    {
        // comment this line if you need to look closely at each single action
        return;
    }

    switch(action->type)
    {
        case ACTION_TYPE__NONE:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__SEQUENCE:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("[ \n");
            for(ListElem* curr_elem = action->sequence.action_list->head; curr_elem; curr_elem = curr_elem->next)
            {
                print_action(curr_elem->data, depth + 1);
            }
            for(int i = 0; i < depth; i++) printf("  ");
            printf("] \n");
        }
        break;
        case ACTION_TYPE__SIMULTANEOUS:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("{ \n");
            for(ListElem* curr_elem = action->simultaneous.action_list->head; curr_elem; curr_elem = curr_elem->next)
            {
                print_action(curr_elem->data, depth + 1);
            }
            for(int i = 0; i < depth; i++) printf("  ");
            printf("} \n");
        }
        break;
        case ACTION_TYPE__MOVE_GROUND:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("( \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->move_ground.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->move_ground.tilemap_pos.x, action->move_ground.tilemap_pos.y);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("dir4:           %i \n", action->move_ground.dir4);
            for(int i = 0; i < depth; i++) printf("  ");
            printf(") \n");
        }
        break;
        case ACTION_TYPE__MOVE_AIR:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->move_air.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->move_air.tilemap_pos.x, action->move_air.tilemap_pos.y);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("dir4:           %i \n", action->move_air.dir4);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__CRASH:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->crash.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->crash.tilemap_pos.x, action->crash.tilemap_pos.y);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("dir4:           %i \n", action->crash.dir4);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__FALL:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->fall.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->fall.tilemap_pos.x, action->fall.tilemap_pos.y);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__DEATH:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->death.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->death.tilemap_pos.x, action->death.tilemap_pos.y);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__BLOW_UP:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->blow_up.tilemap_pos.x, action->blow_up.tilemap_pos.y);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__THROW:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->throw.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->throw.tilemap_pos.x, action->throw.tilemap_pos.y);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("dir4:           %i \n", action->throw.dir4);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("distance:       %i \n", action->throw.distance);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        case ACTION_TYPE__DROP:
        {
            for(int i = 0; i < depth; i++) printf("  ");
            printf("< \n");
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("object:         %p \n", action->drop.object);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("tilemap_pos:    %i, %i \n", action->drop.tilemap_pos.x, action->drop.tilemap_pos.y);
            for(int i = 0; i < depth + 1; i++) printf("  ");
            printf("dir4:           %i \n", action->drop.dir4);
            for(int i = 0; i < depth; i++) printf("  ");
            printf("> \n");
        }
        break;
        default:
        break;
    }
}

char* get_gamestate_name(int gamestate)
{
    char* name = "";

    switch(gamestate)
    {
        case GAMESTATE__NONE:                   name = "none";                      break;
        case GAMESTATE__HERO_CHOOSING_SKILL:    name = "hero choosing skill";       break;
        case GAMESTATE__HERO_CHOOSING_TARGET_1: name = "hero choosing target 1";    break;
        case GAMESTATE__HERO_CHOOSING_TARGET_2: name = "hero choosing target 2";    break;
        case GAMESTATE__HERO_EXECUTING_SKILL:   name = "hero skill executing";      break;
        default: break;
    }

    return name;
}
