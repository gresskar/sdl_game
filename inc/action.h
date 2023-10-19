#ifndef ACTION_H
#define ACTION_H

#include "../inc/common.h"
#include "../inc/vec.h"
#include "../inc/dir.h"
#include "../inc/list.h"
#include "../inc/animation.h"
#include "../inc/floor.h"
#include "../inc/object.h"

enum ACTION_TYPE
{
    ACTION_TYPE__NONE,

    ACTION_TYPE__SEQUENCE,
    ACTION_TYPE__SIMULTANEOUS,

    ACTION_TYPE__MOVE,
    ACTION_TYPE__CRASH,

    ACTION_TYPE__FALL,
    ACTION_TYPE__DEATH,
    ACTION_TYPE__BLOW_UP,

    ACTION_TYPE__THROW,
    ACTION_TYPE__DROP,

    ACTION_TYPE__COUNT
};

typedef struct _Action Action;

typedef struct
{
} Action_None;

typedef struct
{
    List* action_list;
    ListElem* curr_action_list_elem;

} Action_Sequence;

typedef struct
{
    List* action_list;

} Action_Simultaneous;

typedef struct
{
    int dir4;

    Object* object;

} Action_Move;

typedef struct
{
    int dir4;

    Object* object_crushing;
    Object* object_crushed;

} Action_Crash;

typedef struct
{
    Object* object;

} Action_Fall;

typedef struct
{
    Object* object;

} Action_Death;

typedef struct
{

} Action_BlowUP;

typedef struct
{
    int dir4;
    int distance;

    Object* object_thrown;
    Object* object_on_target;

} Action_Throw;

typedef struct
{
    int dir4;
    Object* object;

} Action_Drop;

struct _Action
{
    Animation* animation;
    vec2i tilemap_pos;
    int is_finished;
    int is_finished_at_start;
    int type;

    union
    {
        Action_None action_none;

        Action_Sequence sequence;
        Action_Simultaneous simultaneous;

        Action_Move move;
        Action_Crash crash;

        Action_Fall fall;
        Action_Death death;
        Action_BlowUP blow_up;

        Action_Throw throw;
        Action_Drop drop;
    };

};

Action* new_action_none();

Action* new_action_sequence();
Action* new_action_sequence_of_1(Action* action_1);
Action* new_action_sequence_of_2(Action* action_1, Action* action_2);
Action* new_action_sequence_of_3(Action* action_1, Action* action_2, Action* action_3);
void add_action_to_end_action_sequence(Action* sequence, Action* new_action);
void add_action_after_curr_action_action_sequence(Action* sequence, Action* new_action);
void remove_all_actions_after_curr_action_action_sequence(Action* sequence);

Action* new_action_simultaneous();
Action* new_action_simultaneous_of_1(Action* action_1);
Action* new_action_simultaneous_of_2(Action* action_1, Action* action_2);
Action* new_action_simultaneous_of_3(Action* action_1, Action* action_2, Action* action_3);
void add_action_sequence_to_action_simultaneous(Action* simultaneous, Action* new_sequence);

Action* new_action_move( vec2i tilemap_pos, int dir4);
Action* new_action_crash( vec2i tilemap_pos, int dir4);

Action* new_action_fall(Object* object, vec2i tilemap_pos);
Action* new_action_death(Object* object, vec2i tilemap_pos);
Action* new_action_blow_up(vec2i tilemap_pos);

Action* new_action_throw(vec2i tilemap_pos, int dir4, int distance);
Action* new_action_drop(Object* object, vec2i tilemap_pos, int dir4);

void destroy_action(Action* action);

char* get_action_name_from_type(int action_type);

#endif
