#include "../inc/state.h"

void skill_add_pos_to_possible_target_1_tilemap_pos_list(State* state, int skill, vec2i source_tilemap_pos)
{
    Object* source_object = get_object_on_tilemap_pos(state, source_tilemap_pos);

    switch(skill)
    {
        case SKILL__CHARGE:
        {
            //
        }
        break;
        case SKILL__JUMP:
        {
            //
        }
        break;
        case SKILL__CHARGE_AND_PUSH:
        {
            int up_cont = 1;
            int right_cont = 1;
            int down_cont = 1;
            int left_cont = 1;

            vec2i up_tilemap_pos = source_tilemap_pos;
            vec2i right_tilemap_pos = source_tilemap_pos;
            vec2i down_tilemap_pos = source_tilemap_pos;
            vec2i left_tilemap_pos = source_tilemap_pos;

            Object* up_object = 0;
            Object* right_object = 0;
            Object* down_object = 0;
            Object* left_object = 0;

            for(int i = 1; i < 10; i++)
            {
                up_tilemap_pos = make_vec2i_move_in_dir4_by(up_tilemap_pos, DIR4__UP, 1);
                right_tilemap_pos = make_vec2i_move_in_dir4_by(right_tilemap_pos, DIR4__RIGHT, 1);
                down_tilemap_pos = make_vec2i_move_in_dir4_by(down_tilemap_pos, DIR4__DOWN, 1);
                left_tilemap_pos = make_vec2i_move_in_dir4_by(left_tilemap_pos, DIR4__LEFT, 1);

                up_object = get_object_on_tilemap_pos(state, up_tilemap_pos);
                right_object = get_object_on_tilemap_pos(state, right_tilemap_pos);
                down_object = get_object_on_tilemap_pos(state, down_tilemap_pos);
                left_object = get_object_on_tilemap_pos(state, left_tilemap_pos);

                if(up_cont && is_tilemap_pos_in_tilemap(up_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, up_tilemap_pos);
                }
                if(right_cont && is_tilemap_pos_in_tilemap(right_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, right_tilemap_pos);
                }
                if(down_cont && is_tilemap_pos_in_tilemap(down_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, down_tilemap_pos);
                }
                if(left_cont && is_tilemap_pos_in_tilemap(left_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, left_tilemap_pos);
                }

                if(up_object != 0) up_cont = 0;
                if(right_object != 0) right_cont = 0;
                if(down_object != 0) down_cont = 0;
                if(left_object != 0) left_cont = 0;
            }
        }
        break;
        case SKILL__CHARGE_AND_THROW:
        {
            int up_cont = 1;
            int right_cont = 1;
            int down_cont = 1;
            int left_cont = 1;

            vec2i up_tilemap_pos = source_tilemap_pos;
            vec2i right_tilemap_pos = source_tilemap_pos;
            vec2i down_tilemap_pos = source_tilemap_pos;
            vec2i left_tilemap_pos = source_tilemap_pos;

            Object* up_object = 0;
            Object* right_object = 0;
            Object* down_object = 0;
            Object* left_object = 0;

            for(int i = 1; i < 10; i++)
            {
                up_tilemap_pos = make_vec2i_move_in_dir4_by(up_tilemap_pos, DIR4__UP, 1);
                right_tilemap_pos = make_vec2i_move_in_dir4_by(right_tilemap_pos, DIR4__RIGHT, 1);
                down_tilemap_pos = make_vec2i_move_in_dir4_by(down_tilemap_pos, DIR4__DOWN, 1);
                left_tilemap_pos = make_vec2i_move_in_dir4_by(left_tilemap_pos, DIR4__LEFT, 1);

                up_object = get_object_on_tilemap_pos(state, up_tilemap_pos);
                right_object = get_object_on_tilemap_pos(state, right_tilemap_pos);
                down_object = get_object_on_tilemap_pos(state, down_tilemap_pos);
                left_object = get_object_on_tilemap_pos(state, left_tilemap_pos);

                if(up_cont && is_tilemap_pos_in_tilemap(up_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, up_tilemap_pos);
                }
                if(right_cont && is_tilemap_pos_in_tilemap(right_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, right_tilemap_pos);
                }
                if(down_cont && is_tilemap_pos_in_tilemap(down_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, down_tilemap_pos);
                }
                if(left_cont && is_tilemap_pos_in_tilemap(left_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, left_tilemap_pos);
                }

                if(up_object != 0) up_cont = 0;
                if(right_object != 0) right_cont = 0;
                if(down_object != 0) down_cont = 0;
                if(left_object != 0) left_cont = 0;
            }
        }
        break;
        case SKILL__PUSH:
        {
            vec2i up_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__UP, 1);
            if(get_object_on_tilemap_pos(state, up_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, up_tilemap_pos);
            }

            vec2i right_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__RIGHT, 1);
            if(get_object_on_tilemap_pos(state, right_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, right_tilemap_pos);
            }

            vec2i down_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__DOWN, 1);
            if(get_object_on_tilemap_pos(state, down_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, down_tilemap_pos);
            }

            vec2i left_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__LEFT, 1);
            if(get_object_on_tilemap_pos(state, left_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, left_tilemap_pos);
            }
        }
        break;
        case SKILL__PULL:
        {
            int up_cont = 1;
            int right_cont = 1;
            int down_cont = 1;
            int left_cont = 1;

            vec2i up_tilemap_pos = source_tilemap_pos;
            vec2i right_tilemap_pos = source_tilemap_pos;
            vec2i down_tilemap_pos = source_tilemap_pos;
            vec2i left_tilemap_pos = source_tilemap_pos;

            Object* up_object = 0;
            Object* right_object = 0;
            Object* down_object = 0;
            Object* left_object = 0;

            for(int i = 1; i < 10; i++)
            {
                up_tilemap_pos = make_vec2i_move_in_dir4_by(up_tilemap_pos, DIR4__UP, 1);
                right_tilemap_pos = make_vec2i_move_in_dir4_by(right_tilemap_pos, DIR4__RIGHT, 1);
                down_tilemap_pos = make_vec2i_move_in_dir4_by(down_tilemap_pos, DIR4__DOWN, 1);
                left_tilemap_pos = make_vec2i_move_in_dir4_by(left_tilemap_pos, DIR4__LEFT, 1);

                up_object = get_object_on_tilemap_pos(state, up_tilemap_pos);
                right_object = get_object_on_tilemap_pos(state, right_tilemap_pos);
                down_object = get_object_on_tilemap_pos(state, down_tilemap_pos);
                left_object = get_object_on_tilemap_pos(state, left_tilemap_pos);

                if(up_cont && is_tilemap_pos_in_tilemap(up_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, up_tilemap_pos);
                }
                if(right_cont && is_tilemap_pos_in_tilemap(right_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, right_tilemap_pos);
                }
                if(down_cont && is_tilemap_pos_in_tilemap(down_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, down_tilemap_pos);
                }
                if(left_cont && is_tilemap_pos_in_tilemap(left_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, left_tilemap_pos);
                }

                if(up_object != 0) up_cont = 0;
                if(right_object != 0) right_cont = 0;
                if(down_object != 0) down_cont = 0;
                if(left_object != 0) left_cont = 0;
            }
        }
        break;
        case SKILL__PULL_AND_THROW:
        {
            int up_cont = 1;
            int right_cont = 1;
            int down_cont = 1;
            int left_cont = 1;

            vec2i up_tilemap_pos = source_tilemap_pos;
            vec2i right_tilemap_pos = source_tilemap_pos;
            vec2i down_tilemap_pos = source_tilemap_pos;
            vec2i left_tilemap_pos = source_tilemap_pos;

            Object* up_object = 0;
            Object* right_object = 0;
            Object* down_object = 0;
            Object* left_object = 0;

            for(int i = 1; i < 10; i++)
            {
                up_tilemap_pos = make_vec2i_move_in_dir4_by(up_tilemap_pos, DIR4__UP, 1);
                right_tilemap_pos = make_vec2i_move_in_dir4_by(right_tilemap_pos, DIR4__RIGHT, 1);
                down_tilemap_pos = make_vec2i_move_in_dir4_by(down_tilemap_pos, DIR4__DOWN, 1);
                left_tilemap_pos = make_vec2i_move_in_dir4_by(left_tilemap_pos, DIR4__LEFT, 1);

                up_object = get_object_on_tilemap_pos(state, up_tilemap_pos);
                right_object = get_object_on_tilemap_pos(state, right_tilemap_pos);
                down_object = get_object_on_tilemap_pos(state, down_tilemap_pos);
                left_object = get_object_on_tilemap_pos(state, left_tilemap_pos);

                if(up_cont && is_tilemap_pos_in_tilemap(up_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, up_tilemap_pos);
                }
                if(right_cont && is_tilemap_pos_in_tilemap(right_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, right_tilemap_pos);
                }
                if(down_cont && is_tilemap_pos_in_tilemap(down_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, down_tilemap_pos);
                }
                if(left_cont && is_tilemap_pos_in_tilemap(left_tilemap_pos))
                {
                    add_pos_to_possible_target_1_tilemap_pos_list(state, left_tilemap_pos);
                }

                if(up_object != 0) up_cont = 0;
                if(right_object != 0) right_cont = 0;
                if(down_object != 0) down_cont = 0;
                if(left_object != 0) left_cont = 0;
            }
        }
        break;
        case SKILL__THROW:
        {
            vec2i up_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__UP, 1);
            if(get_object_on_tilemap_pos(state, up_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, up_tilemap_pos);
            }

            vec2i right_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__RIGHT, 1);
            if(get_object_on_tilemap_pos(state, right_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, right_tilemap_pos);
            }

            vec2i down_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__DOWN, 1);
            if(get_object_on_tilemap_pos(state, down_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, down_tilemap_pos);
            }

            vec2i left_tilemap_pos = make_vec2i_move_in_dir4_by(source_tilemap_pos, DIR4__LEFT, 1);
            if(get_object_on_tilemap_pos(state, left_tilemap_pos) != 0)
            {
                add_pos_to_possible_target_1_tilemap_pos_list(state, left_tilemap_pos);
            }
        }
        break;
        default:
        break;
    }
}