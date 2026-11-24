#include "gun.hpp"
#include "soldier.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <SFML/Window/Window.hpp>
using namespace sf;

// enum StatesOfSoldiers {idle, walking, running, stand_firing, walk_firing, run_firing, charging, in_melee, dead};
//---Base soldier start---///
base_soldier::base_soldier(){ // constructor
    soldier_body.setSize(Vector2f(20,50));
}

void base_soldier::display_soldier(RenderWindow& win){
    win.draw(soldier_body);
}

void base_soldier::turn_soldier_right(){
    // soldier_body.setScale({1.0f,1.0f});
    base_gun_object.changing_gnn_side(1.0f);
}
void base_soldier::turn_soldier_left(){
    // soldier_body.setScale({1.0f,1.0f});
    base_gun_object.changing_gnn_side(-1.0f);
}

Color base_soldier:: soldier_body_colour(){
    return soldier_body.getFillColor();
}

void base_soldier:: fire_bullet(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_pos){
    base_gun_object.gun_move_and_fire(window,bullet_vector ,target_pos ,soldier_body.getPosition());
}
void base_soldier:: move_pos(Vector2f pos){
    soldier_body.move(pos);
}
Vector2f base_soldier::get_soldier_pos(){ // to get the real time position of the soldier_body like player
    return soldier_body.getPosition();
}  
FloatRect base_soldier::get_hitbox(){
    return soldier_body.getGlobalBounds();
}
//---Base soldier end---///

//---start of player class---///
class_player::class_player(){
    soldier_body.setPosition({20,550});
    soldier_body.setFillColor(Color::Green);
}
void class_player::reset_melee_colour(){
    if((melee_attack_colour_timer.getElapsedTime().asSeconds() >  0.2f) && (soldier_body.getFillColor() == Color::Red))
    {
        soldier_body.setFillColor(Color::Blue);
    }
}
void class_player::reset_pos(){
    soldier_body.setPosition({20,551});
}
void class_player::plr_mov(float& delta_time){
    if(melee_mode) v_X = 200.0f;
    else v_X = 150;
    if(Keyboard::isKeyPressed((Keyboard::Key::W))){ // IMP
        if(Keyboard::isKeyPressed(Keyboard::Key::RShift)) {
            v_X += 50.0f;
        }
        soldier_body.move({v_X*delta_time,0.0f}); 
        turn_soldier_right();
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::S)){
        if(Keyboard::isKeyPressed(Keyboard::Key::RShift)){
            v_X += 50.0f;
        }
        soldier_body.move({-v_X*delta_time,0.0f});
        turn_soldier_left();
    }
    
    soldier_body.move({0,v_Y});
}
void class_player::fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec){
    base_gun_object.display_gun(window,soldier_body.getPosition()); // SUBJECT TO CHANGE
    if(Mouse::isButtonPressed(Mouse::Button::Left) && ! melee_mode){
        Vector2i mouse_pos = Mouse::getPosition(window) ; 
        Vector2f world_mouse_pos = window.mapPixelToCoords(mouse_pos);
        fire_bullet(window, bullet_vec,world_mouse_pos);
    }
}

void class_player::melee(std::vector<class_enemy>& emy_vec){
    if(Mouse::isButtonPressed(Mouse::Button::Right) && ! melee_mode && melee_mode_timer.getElapsedTime().asSeconds() >=2.0f){
        melee_mode_timer.restart();
        melee_mode = 1;
        soldier_body.setFillColor(Color::Blue);
    }
    else if(Mouse::isButtonPressed(Mouse::Button::Left) && melee_mode && melee_attack_timer.getElapsedTime().asSeconds() >= 0.5f){
        melee_attack_timer.restart();
        melee_attack_colour_timer.restart();
        soldier_body.setFillColor(Color::Red);
        //issue starts here
        for(class_enemy &emy : emy_vec)
        {
            if((std::abs(soldier_body.getPosition().x - emy.get_soldier_pos().x) <= 21) && (abs(emy.get_soldier_pos().y - soldier_body.getPosition().y)<1.0f))
            { 
                emy.hp -= 50.0f;
            }
        }   
    }
    else if(Mouse::isButtonPressed(Mouse::Button::Right) && melee_mode && melee_mode_timer.getElapsedTime().asSeconds() >= 2.0f) {
        melee_mode = 0;
        soldier_body.setFillColor(Color::Green);
        melee_mode_timer.restart();
    }
}

//---end of player class---///

//---start of enemy class---///
class_enemy::class_enemy(Vector2f set_pos_on_creation ){
    soldier_body.setPosition(set_pos_on_creation);
    soldier_body.setFillColor(Color::Red);
}
void class_enemy::dist_base_attack_mode(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_player,float dt_time){
    float gap_plyr_emy = abs(target_player.x - soldier_body.getPosition().x);

    if(soldier_body.getPosition().x > target_player.x) turn_soldier_left();

    else if(soldier_body.getPosition().x < target_player.x) turn_soldier_right();

    if(gap_plyr_emy >= 100 && gap_plyr_emy <= 600) {
        emy_in_melee = 0;
        fire_bullet(window, bullet_vector, target_player);
    }/*stand and fire*/

    else if(gap_plyr_emy <= 21 && (abs(target_player.y - soldier_body.getPosition().y)<1.0f))
    {
        emy_in_melee = 1;
    }
}
float class_enemy::enemy_melee(float& plyr_hp)
{
    if(melee_attack_timer.getElapsedTime().asSeconds() >= 1.0f)
    {
        melee_attack_timer.restart();
        plyr_hp -= 30;
    }  
    return plyr_hp;//fixes  warning: control reaches end of non-void function
}
void class_enemy:: display_troop_gun(RenderWindow& window){
    window.draw(soldier_body);
    base_gun_object.display_gun(window, soldier_body.getPosition());
}
//---end of enemy class---///