#ifndef SKILL_H
#define SKILL_H

#include "../inc/common.h"
#include "../inc/vec.h"

enum SKILL
{
    SKILL__NONE,

    SKILL__ATTACK_DIR,
    SKILL__NO_ATTACK,

    SKILL__USE,
    SKILL__MANIPULATION,
    SKILL__TELEPORTATION,

    SKILL__MOVE,
    SKILL__MOVE_FLOATING,
    SKILL__MOVE_FLYING,

    SKILL__PICK_ITEM_CLOSE,
    SKILL__PICK_ITEM_FAR,

    SKILL__PUT_ITEM_CELL_CLOSE,
    SKILL__PUT_ITEM_CELL_FAR,
    SKILL__PUT_ITEM_DYNAMITE_CLOSE,
    SKILL__PUT_ITEM_DYNAMITE_FAR,
    SKILL__PUT_ITEM_GEMSTONE_CLOSE,
    SKILL__PUT_ITEM_GEMSTONE_FAR,

    SKILL__THROW_ITEM_CELL,
    SKILL__THROW_ITEM_DYNAMITE,
    SKILL__THROW_ITEM_GEMSTONE,

    SKILL__SHOOT_PROJECTILE_FLY,
    SKILL__SHOOT_PROJECTILE_SQUIRREL,

    SKILL__PUSH,
    SKILL__THROW,
    SKILL__PULL_HOOK,
    SKILL__PULL_SPIDERWEB,
    SKILL__PULL_TENTACLE,
    SKILL__PULL_TONGUE,
    SKILL__DRAG_HOOK,
    SKILL__DRAG_SPIDERWEB,
    SKILL__DRAG_TENTACLE,
    SKILL__JUMP,
    SKILL__CHARGE,
    SKILL__STOMP,

    SKILL__DRAG_AND_THROW_HOOK,
    SKILL__DRAG_AND_THROW_TONGUE,
    SKILL__CHARGE_AND_PUSH,
    SKILL__CHARGE_AND_THROW,
    SKILL__CHARGE_AND_JUMP,
    SKILL__JUMP_AND_CARRY,
    SKILL__JUMP_AND_STOMP,

    SKILL__LAUNCH_MINIBOT,
    SKILL__MINIBOT_MERGE,

    SKILL__TURRET_LASER,
    SKILL__TURRET_BOMB,
    SKILL__TURRET_PROJECTILE,

    SKILL__KILL_AROUND,

    SKILL__ENVIRONMENT_FALLING_STALACTITE,
    SKILL__ENVIRONMENT_EMERGE_WATER,
    SKILL__ENVIRONMENT_EMERGE_PIT,
    SKILL__ENVIRONMENT_EMERGE_BURROW,
    SKILL__ENVIRONMENT_EMERGE_PIPE,
    SKILL__ENVIRONMENT_COLLAPSE_BURROW,
    SKILL__ENVIRONMENT_CONV_BELT,

    SKILL__COUNT
};

int is_skill_two_target(int skill);
int get_skill_action_points(int skill);
char* get_skill_name(int skill);

#endif
