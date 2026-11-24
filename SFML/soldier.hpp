#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Window/Window.hpp>
#include "gun.hpp"
using namespace sf;
// enum StatesOfSoldiers {idle, walking, running, stand_firing, walk_firing, run_firing, charging, in_melee, dead};
class base_soldier{
    public:
        base_soldier(); // constructor
        bool is_soldier_alive = true;
        float hp = 100.0f;
        float damage = 10.0f;
        bool on_ground = true;
        float v_X = 0;
        float v_Y = 0;

        void display_soldier(RenderWindow& win);
        // void deal_dmg_to_xyz_entity(int argc, char **argv); //basically calling this whenever dmg has to be delt. it can accept any object, be it player or enemy vector and then put 2 if cond inside to check whcih it is and deal dmgaccordingly
        void turn_soldier_right();
        void turn_soldier_left();

        Color soldier_body_colour();

        void fire_bullet(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_pos);

        void move_pos(Vector2f pos);

        Vector2f get_soldier_pos();
        FloatRect get_hitbox();

        Clock melee_attack_timer;
        Clock melee_attack_colour_timer;
    protected :
        RectangleShape soldier_body;
        base_gun base_gun_object; // Genius
};



class class_enemy : public base_soldier
{
    public :
        class_enemy(Vector2f set_pos_on_creation);

        bool emy_in_melee = false;

        float firing_timer = 0.0f;// for the delay in frigin of the soldiers, otherwise you die in an instant

        void dist_base_attack_mode(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_player,float dt_time);

        void display_troop_gun(RenderWindow& window);

        float  enemy_melee(float& plyr_hp);
        /*The melee function earlier had class_player object as an argument in order to change the 
        health of the player by getting the hp info from the object.
        but class_player also needed class_enemy in its melee function
        this lead to a circular dependency
        an easy fix was to return the deductions in hp and then make that equal to the
        player hp in the main file
        ik, it's not the most clever or maybe the most efficient ways, but it's my way, not c+v*/
};


class class_player: public base_soldier
{
    public:
        class_player();
        bool melee_mode = 0;
        void reset_pos();
        
        void reset_melee_colour();

        void plr_mov(float& delta_time);

        void fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec);
        
        void melee(std::vector<class_enemy>& emy_vec);
        
        Clock melee_mode_timer;
};