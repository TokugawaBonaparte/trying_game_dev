#ifndef base_soldier_hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Window/Window.hpp>
#include <base_gun.hpp>

using namespace sf;

class base_soldier{        
    public:
        base_soldier(){ // constructor
        soldier_body.setSize(Vector2f(20,50));
        soldier_body.setFillColor(Color::Green);
        }
        bool is_soldier_alive = true;
        float hp = 100.0f;
        float damage = 10.0f;
        void take_damage(float damage){ // bcs cannot put conditions without functions, so need a sepeerate function
             hp -= damage;
            if (hp <= 0.0f) is_soldier_alive = false;
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
        void melee(){
            soldier_body.setFillColor(Color::Red);
            melee_timer.restart(); //resets to 0 .
        }
        void reset_pos(){
            soldier_body.setPosition({20,550});
        }
        void move_soldier(float x, float y){
            soldier_body.move(Vector2f(x, y));
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
            soldier_body.setOrigin({30,10});
        }
        void display_move_fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec){
                window.draw(soldier_body);
                base_gun_object.display_gun(window,soldier_body.getPosition()); // SUBJECT TO CHANGE
        // base_gun_object.display_gun(window, soldier_body.getPosition());
        // idea - put a mode system - > right click once to enter into melee mode, where the character puts his gun on 
        // shoulder and takes out his dagger. right click again to put the dagger back and get the gun from the back. 
        // if melee mode --> display gun , else --> display dagger
                // movement of player
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                Vector2i mouse_pos = Mouse::getPosition(window) ; 
                Vector2f world_mouse_pos = window.mapPixelToCoords(mouse_pos);
                fire_bullet(window, bullet_vec,world_mouse_pos);
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::LShift)){ //sprinting
                if(Keyboard::isKeyPressed(Keyboard::Key::D)){
                    soldier_body.move({100.0f*delta_time,0.0f});
                }
                else if(Keyboard::isKeyPressed(Keyboard::Key::A)){
                    soldier_body.move({-100.0f*delta_time,0.0f});
                }
            }
            if(Keyboard::isKeyPressed((Keyboard::Key::D))){ // IMP
                soldier_body.move({+100.0f*delta_time,0.0f}); 
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::A)){
                soldier_body.move({-100.0f*delta_time,0.0f});
            }
            if(Keyboard::isKeyPressed(Keyboard::Key::R)){
                reset_pos();
            }
            reset_melee();
        }
};
class class_enemy: public base_soldier{
    public :
        class_enemy(Vector2f set_pos_on_creation ){
            soldier_body.setPosition(set_pos_on_creation);
            soldier_body.setFillColor(Color::Blue);
            soldier_body.setOrigin({30,10});
        }
        bool emy_in_melee = false;
        void dist_base_attack_mode(Vector2f target_player,float dt_time){
            float gap_plyr_emy = abs(target_player.x - soldier_body.getPosition().x);
            if(gap_plyr_emy >=500) soldier_body.move({0.0f,0.0f}); // stand still 
            if( gap_plyr_emy >= 200) enemy_run_to_player(target_player,dt_time);/*walk and fire*/
            else if(gap_plyr_emy >= 100 ) soldier_body.move({0,0});/*stand and fire*/
            else if(gap_plyr_emy >=50) {
                enemy_run_to_player(target_player,dt_time);
                emy_in_melee = false;
            }//fix bayonets and chargE
            else {
                enemy_run_to_player(target_player,dt_time);
                emy_in_melee = true;
            } /*engae in melee*/
        }
        void enemy_run_to_player(Vector2f target_player, float d_time){
            float enemyX = soldier_body.getPosition().x;
            float target_playerX = target_player.x;
            if(abs(enemyX - target_playerX) >= 21){
                if(target_playerX < enemyX) soldier_body.move({-110*d_time,0}) ;
                else soldier_body.move({+110*d_time,0});
            }
            else soldier_body.move({0,0});
        } 

        void display_troop(RenderWindow& window){
        window.draw(soldier_body);
        base_gun_object.display_gun(window, soldier_body.getPosition());
        // base_gun_object.display_gun(window, soldier_body.getPosition());
        // idea - put a mode system - > right click once to enter into melee mode, where the character puts his gun on 
        // shoulder and takes out his dagger. right click again to put the dagger back and get the gun from the back. 
        // if melee mode --> display gun , else --> display bayonet
        }
};
// class ally_enemy : base_soldier{
//     public:
//         bool is_ally = true;
//         if (is_ally) {
//         bool emy_in_melee = false;
//         void dist_base_attack_mode(Vector2f target_player,float dt_time){
//             float gap_plyr_emy = abs(target_player.x - enemy_body.getPosition().x);
//             if( gap_plyr_emy >= 200) enemy_run_to_player(target_player,dt_time);/*walk and fire*/
//             else if(gap_plyr_emy >= 100 ) enemy_body.move({0,0});/*stand and fire*/
//             else if(gap_plyr_emy >=50) {
//                 enemy_run_to_player(target_player,dt_time);
//                 emy_in_melee = false;
//             }//fix bayonets and chargE
//             else {
//                 enemy_run_to_player(target_player,dt_time);
//                 emy_in_melee = true;
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
//                 emy_in_melee = false;
//             }//fix bayonets and chargE
//             else {
//                 enemy_run_to_player(target_player,dt_time);
//                 emy_in_melee = true;
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