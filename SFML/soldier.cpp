#include "gun.hpp"
#include "soldier.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Window/Window.hpp>
using namespace sf;

// enum StatesOfSoldiers {idle, walking, running, stand_firing, walk_firing, run_firing, charging, in_melee, dead};
//---Base soldier start---///
base_soldier::base_soldier(){ // constructor
    soldier_body.setSize(Vector2f(20,50));
}

void  base_soldier::gravity_pull(float delta_time){
    soldier_body.move({0,1*delta_time});
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
void base_soldier:: reset_melee(){
    if((melee_timer.getElapsedTime().asSeconds() >  0.2f) && (soldier_body.getFillColor() == Color::Red)){
        soldier_body.setFillColor(Color::Green);
        }
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
void class_player::reset_pos(){
    soldier_body.setPosition({20,551});
}
void class_player::plr_mov(float delta_time){
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
    if(Keyboard::isKeyPressed(Keyboard::Key::Space) && on_ground ){
        soldier_body.move({0.0f,-500.0f*delta_time});
    }
}
void class_player:: fire_player(float delta_time, RenderWindow &window, std::vector<bullet> &bullet_vec){
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
}
//---end of player class---///

//---start of enemy class---///
class_enemy::class_enemy(Vector2f set_pos_on_creation ){
    soldier_body.setPosition(set_pos_on_creation);
    soldier_body.setFillColor(Color::Red);
}
void class_enemy:: dist_base_attack_mode(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_player,float dt_time){
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
void class_enemy:: display_troop_gun(RenderWindow& window){
    window.draw(soldier_body);
    base_gun_object.display_gun(window, soldier_body.getPosition());
}
//---end of enemy class---///