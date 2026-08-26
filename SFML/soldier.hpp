#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Window/Window.hpp>
#include <gun.hpp>
using namespace sf;

// enum StatesOfSoldiers {idle, walking, running, stand_firing, walk_firing, run_firing, charging, in_melee, dead};
class base_soldier{        
    public:
        base_soldier(){ // constructor
        soldier_body.setSize(Vector2f(20,50));
        }
        bool is_soldier_alive = true;
        float hp = 100.0f;
        float damage = 10.0f;

        void gravity_pull(float delta_time){
            soldier_body.move({0,1000*delta_time});
        }

        void display_soldier(RenderWindow& win){
            win.draw(soldier_body);
        }
        
        void turn_soldier_right(){
            // soldier_body.setScale({1.0f,1.0f});
            base_gun_object.changing_gnn_side(1.0f);
        }
        void turn_soldier_left(){
            // soldier_body.setScale({1.0f,1.0f});
            base_gun_object.changing_gnn_side(-1.0f);
        }

        Color soldier_body_colour(){
            return soldier_body.getFillColor();
        }
        void reset_melee(){
            if((melee_timer.getElapsedTime().asSeconds() >  0.2f) && (soldier_body.getFillColor() == Color::Red)){
                soldier_body.setFillColor(Color::Green);
                }
        }
        void fire_bullet(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_pos){
            base_gun_object.gun_move_and_fire(window,bullet_vector ,target_pos ,soldier_body.getPosition());
        }
        void move_pos(Vector2f pos){
            soldier_body.move(pos);
        }
        void reset_pos(){
            soldier_body.setPosition({20,550});
        }
        Vector2f get_soldier_pos(){ // to get the real time position of the soldier_body like player
            return soldier_body.getPosition();
        }  
        FloatRect get_hitbox(){
            return soldier_body.getGlobalBounds();
        }
    private:
        Clock melee_timer;
    protected :
        RectangleShape soldier_body;
        base_gun base_gun_object; // Genius
};

class class_player : public base_soldier{
    public:
        class_player(){
            soldier_body.setPosition({30,550});
            soldier_body.setFillColor(Color::Green);
        }
        void plr_mov(float delta_time){
            float speed = 150.0f;
            if(Keyboard::isKeyPressed((Keyboard::Key::W))){ // IMP
                if(Keyboard::isKeyPressed(Keyboard::Key::RShift)) {
                    speed = 200.0f;
                }
                soldier_body.move({speed*delta_time,0.0f}); 
                turn_soldier_right();
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::S)){
                if(Keyboard::isKeyPressed(Keyboard::Key::RShift)){
                    speed = 200.0f;
                }
                soldier_body.move({-speed*delta_time,0.0f});
                turn_soldier_left();
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::Space)){
                soldier_body.move({0.0f,-20.0f});
            }
        }
        void fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec){
            base_gun_object.display_gun(window,soldier_body.getPosition()); // SUBJECT TO CHANGE
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                Vector2i mouse_pos = Mouse::getPosition(window) ; 
                Vector2f world_mouse_pos = window.mapPixelToCoords(mouse_pos);
                fire_bullet(window, bullet_vec,world_mouse_pos);
            }
            if(Mouse::isButtonPressed(Mouse::Button::Right) && soldier_body.getFillColor() == Color::Green){
                soldier_body.setFillColor(Color::Red);
                reset_melee();
                // melee_timer.restart(); //resets to 0 .
            }
            // if(Keyboard::isKeyPressed(Keyboard::Key::R)){
            //     reset_pos();
            // }
        }
};
class class_enemy: public base_soldier{
    public :
        class_enemy(Vector2f set_pos_on_creation ){
            soldier_body.setPosition(set_pos_on_creation);
            soldier_body.setFillColor(Color::Red);
        }
        bool emy_in_melee = false;
        float firing_timer = 0.0f;// for the delay in frigin of the soldiers, otherwise you die in an instant
        void dist_base_attack_mode(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_player,float dt_time){
            float gap_plyr_emy = abs(target_player.x - soldier_body.getPosition().x);
            if(soldier_body.getPosition().x > target_player.x) turn_soldier_left();
            else if(soldier_body.getPosition().x < target_player.x) turn_soldier_right();
            if(gap_plyr_emy >= 100 && gap_plyr_emy <= 600) {
                fire_bullet(window, bullet_vector, target_player);
            }/*stand and fire*/
            else if(gap_plyr_emy <= 20 && abs(target_player.y - soldier_body.getPosition().y) < 10) {
                // enemy_run_to_player(target_player,dt_time);
                emy_in_melee = true;
            } /*engae in melee*/
    }
        void display_troop_gun(RenderWindow& window){
            window.draw(soldier_body);
            base_gun_object.display_gun(window, soldier_body.getPosition());
    
        }
};