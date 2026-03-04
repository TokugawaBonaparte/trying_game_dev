#ifndef base_soldier_hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Window/Window.hpp>
#include <gun.hpp>
using namespace sf;

enum StatesOfSoldiers {idle, walking, running, stand_firing, walk_firing, run_firing, charging, in_melee, dead};
enum weapon {Carcano, VillarP , Dagger ,FIAT_1914, Mannlicher, Grenade};
class base_soldier{        
    public:
        base_soldier(){ // constructor
            soldier_body.setSize(Vector2f(20,50));
            soldier_body.setFillColor(Color::Green);
            soldier_body.setOrigin({10,25});
        }

        float frane_time = 0.2;
        float frame = 0;

        StatesOfSoldiers current_soldier_state = idle;
        bool is_soldier_alive = true;
        bool in_melee = false;

        float hp = 100.0f;
        float damage = 10.0f;

        void take_damage(float damage){ // bcs cannot put conditions without functions, so need a sepeerate function
             hp -= damage;
            if (hp <= 0.0f) {
                is_soldier_alive = false;
                current_soldier_state = dead;
            }
        }
        void turn_soldier_right(){
            soldier_body.setScale({1.0f,1.0f});
            base_gun_object.changing_gnn_side(1.0f);
        }
        void turn_soldier_left(){
            soldier_body.setScale({-1.0f,-1.0f});
            base_gun_object.changing_gnn_side(-1.0f);
        }

        Color soldier_body_colour(){
            return soldier_body.getFillColor();
        }
        
        void fire_bullet(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_pos){
            base_gun_object.gun_move_and_fire(window,bullet_vector ,target_pos ,soldier_body.getPosition(), 1.0f);
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
    protected :
        RectangleShape soldier_body;
        base_gun base_gun_object; // Genius
};

class class_player : public base_soldier{
    private:
        Clock melee_timer;
    public:
        class_player(){
            soldier_body.setPosition({30,550});
        }
        weapon IT_current_weapon = Carcano;
        void melee(){
            soldier_body.setFillColor(Color::Red);
            melee_timer.restart(); //resets to 0 .
        }
        void reset_melee(){
            if((melee_timer.getElapsedTime().asSeconds() >  0.2f) && (soldier_body.getFillColor() == Color::Red)){
                soldier_body.setFillColor(Color::Green);
                }
        }

        void display_move_fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec){

        // float min_border_x = 0.0;
        // float max_border_x = 800;
        // float min_border_y = 0;
        // float max_border_y = 600;
        // Vector2f pos = soldier_body.getPosition();
        // if(soldier_body.getPosition().x < min_border_x) pos.x = min_border_x; 
        // if(soldier_body.getPosition().x > max_border_x) pos.x = max_border_x; 
        // if(soldier_body.getPosition().y < min_border_y) pos.y = min_border_y; 
        // if(soldier_body.getPosition().y > max_border_y) pos.y = max_border_y; 
        // soldier_body.setPosition(pos);

        float speed = 100.0f;
        window.draw(soldier_body);
        base_gun_object.display_gun(window,soldier_body.getPosition()); // SUBJECT TO CHANGE

        // base_gun_object.display_gun(window, soldier_body.getPosition());
        // idea - put a mode system - > right click once to enter into melee mode, where the character puts his gun on 
        // shoulder and takes out his dagger. right click again to put the dagger back and get the gun from the back. 
        // if ! melee mode --> display gun , else --> display dagger

        // ---------------------------------------------weapon switch mechanic ---------------------------------------------//
            // if(Keyboard::isKeyPressed::false_type)
            if(Keyboard::isKeyPressed((Keyboard::Key::S))){ // IMP
                speed = 100.0f;
                current_soldier_state = walking;
                if(Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift)){
                    speed = 150.0f;
                    current_soldier_state = running;
                }
                soldier_body.move({0.0f,speed*delta_time}); 
                turn_soldier_right();
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::W)){
                speed = 100.0f;
                current_soldier_state = walking;
                if(Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                    speed = 150.0f;
                    current_soldier_state = running;
                }
                soldier_body.move({0.0f, -speed*delta_time});
                turn_soldier_left();
            }
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                current_soldier_state = stand_firing;
                Vector2i mouse_pos = Mouse::getPosition(window) ; 
                Vector2f world_mouse_pos = window.mapPixelToCoords(mouse_pos);
                fire_bullet(window, bullet_vec,world_mouse_pos);
            }
            if(Keyboard::isKeyPressed((Keyboard::Key::D))){ // IMP
                current_soldier_state = walking;
                speed = 100.0f;
                if(Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
                    speed = 150.0f;
                    current_soldier_state = running;
                }
                soldier_body.move({speed*delta_time,0.0f}); 
                turn_soldier_right();
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::A)){
                current_soldier_state = walking;
                speed = 100.0f;
                if(Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift)){
                    speed = 150.0f;
                    current_soldier_state = running;
                }
                soldier_body.move({-speed*delta_time,0.0f});
                turn_soldier_left();
            }
        // ---------------------------------------------//movement logic // ---------------------------------------------//
            // if(Keyboard::isKeyPressed(Keyboard::Key::R)){
            //     reset_pos();
            // }
            reset_melee();

        // ---------------------------------------------//weapon switch mechanic ---------------------------------------------//
            if(Keyboard::isKeyPressed(Keyboard::Key::Num1)) IT_current_weapon = Carcano;
            if(Keyboard::isKeyPressed(Keyboard::Key::Num2)) IT_current_weapon = VillarP;
            if(Keyboard::isKeyPressed(Keyboard::Key::Num3)) IT_current_weapon = Grenade;
            if(Keyboard::isKeyPressed(Keyboard::Key::Space)){
                 IT_current_weapon = Dagger;
                 in_melee = true; //melee mode on//
            }
            if((Keyboard::isKeyPressed(Keyboard::Key::Space)) && in_melee){
                 IT_current_weapon = Carcano;
                 in_melee = false; // melee mode off//
            }            
        // ---------------------------------------------//weapon switch mechanic ---------------------------------------------//
        }
};
class class_enemy: public base_soldier{
    public :
        Clock firing_clock; // for the delay in frigin of the soldiers, otherwise you die in an instant
        class_enemy(Vector2f set_pos_on_creation ){
            soldier_body.setPosition(set_pos_on_creation);
            soldier_body.setFillColor(Color::Blue);
        }
        
        weapon AU_current_weapon = Mannlicher ;

        void dist_base_attack_mode(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_player,float dt_time){
            // if(soldier_body.getPosition().y == 550){
            //     soldier_body.move({0,0}); // STAY IN YOUR TRENCHES 
            // }
            // else{ stupid mistake, to be remembered for a laugh.
            float gap_plyr_emy = abs(target_player.x - soldier_body.getPosition().x);
            if(soldier_body.getPosition().x > target_player.x) turn_soldier_left();
            if(soldier_body.getPosition().x < target_player.x) turn_soldier_right();
            if(gap_plyr_emy >=600) soldier_body.move({0.0f,0.0f}); // stand still 
            else if( gap_plyr_emy >= 200) {
                // enemy_run_to_player(target_player,dt_time);
                fire_bullet(window, bullet_vector, target_player);
            }/*walk and fire*/
            else if(gap_plyr_emy >= 100 ) {
                // soldier_body.move({0,0});
                fire_bullet(window, bullet_vector, target_player);
            }/*stand and fire*/
            else if(gap_plyr_emy >=50) {
                // enemy_run_to_player(target_player,dt_time);
            }//fix bayonets and chargE
            else if(gap_plyr_emy <= 20 && abs(target_player.y - soldier_body.getPosition().y) < 10) {
                // enemy_run_to_player(target_player,dt_time);
                in_melee = true;
            } /*engae in melee*/
    }

        // void enemy_run_to_player(Vector2f target_player, float d_time){
        //     float enemyX = soldier_body.getPosition().x;
        //     float target_playerX = target_player.x;
        //     if(abs(enemyX - target_playerX) >= 21){
        //         if(target_playerX < enemyX) soldier_body.move({-110*d_time,0}) ;
        //         else soldier_body.move({+110*d_time,0});
        //     }
        //     else soldier_body.move({0,0});
        // } JUST REALISED THIS FUNCTION WAS FOR NOTHING.

        void display_troop(RenderWindow& window){
            window.draw(soldier_body);
            base_gun_object.display_gun(window, soldier_body.getPosition());
        // base_gun_object.display_gun(window, soldier_body.getPosition());
        // idea - put a mode system - > right click once to enter into melee mode, where the character puts his gun on 
        // shoulder and takes out his dagger. right click again to put the dagger back and get the gun from the back. 
        // if ! melee mode --> display gun , else --> display bayonet
        }
};
// class ally_enemy : base_soldier{
//     public:
//         bool is_ally = true;
//         if (is_ally) {
//         bool in_melee = false;
//         void dist_base_attack_mode(Vector2f target_player,float dt_time){
//             float gap_plyr_emy = abs(target_player.x - enemy_body.getPosition().x);
//             if( gap_plyr_emy >= 200) enemy_run_to_player(target_player,dt_time);/*walk and fire*/
//             else if(gap_plyr_emy >= 100 ) enemy_body.move({0,0});/*stand and fire*/
//             else if(gap_plyr_emy >=50) {
//                 enemy_run_to_player(target_player,dt_time);
//                 in_melee = false;
//             }//fix bayonets and chargE
//             else {
//                 enemy_run_to_player(target_player,dt_time);
//                 in_melee = true;
//             } /*engae in melee*/
//         }

//         void enemy_run_to_player(Vector2f target_player, float d_time){
//             float enemyX = enemy_body.getPosition().x;
//             float target_playerX = target_player.x;
//             if(abs(enemyX - target_playerX) >= 21){
//                 if(target_playerX < enemyX) enemy_body.move({-100*d_time,0}) ;
//                 else enemy_body.move({+100*d_time,0});
//             }
//             else enemy_body.move({0,0});
//         }
//     }
//     else{
//         void dist_base_attack_mode(Vector2f target_player,float dt_time){
//             float gap_plyr_emy = abs(target_player.x - enemy_body.getPosition().x);
//             if( gap_plyr_emy >= 200) enemy_run_to_player(target_player,dt_time);/*walk and fire*/
//             else if(gap_plyr_emy >= 100 ) enemy_body.move({0,0});/*stand and fire*/
//             else if(gap_plyr_emy >=50) {
//                 enemy_run_to_player(target_player,dt_time);
//                 in_melee = false;
//             }//fix bayonets and chargE
//             else {
//                 enemy_run_to_player(target_player,dt_time);
//                 in_melee = true;
//             } /*engae in melee*/
//         }

//         void enemy_run_to_player(Vector2f target_player, float d_time){
//             float enemyX = enemy_body.getPosition().x;
//             float target_playerX = target_player.x;
//             if(abs(enemyX - target_playerX) >= 21){
//                 if(target_playerX < enemyX) enemy_body.move({-100*d_time,0}) ;
//                 else enemy_body.move({+100*d_time,0});
//             }
//             else enemy_body.move({0,0});
//         }
//     }
// };
#endif