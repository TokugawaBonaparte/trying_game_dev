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

        void gravity_pull(float delta_time);

        void display_soldier(RenderWindow& win);
        
        void turn_soldier_right();
        void turn_soldier_left();

        Color soldier_body_colour();

        void reset_melee();

        void fire_bullet(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_pos);

        void move_pos(Vector2f pos);

        Vector2f get_soldier_pos();
        FloatRect get_hitbox();
    private:
        Clock melee_timer;
    protected :
        RectangleShape soldier_body;
        base_gun base_gun_object; // Genius
};

class class_player : public base_soldier{
    public:
        class_player();

        void reset_pos();

        void plr_mov(float delta_time);

        void fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec);
};

class class_enemy: public base_soldier{
    public :
        class_enemy(Vector2f set_pos_on_creation);

        bool emy_in_melee = false;

        float firing_timer = 0.0f;// for the delay in frigin of the soldiers, otherwise you die in an instant

        void dist_base_attack_mode(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_player,float dt_time);

        void display_troop_gun(RenderWindow& window);
};