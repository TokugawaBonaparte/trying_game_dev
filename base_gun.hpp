#ifndef base_gun_hpp
#pragma once
#include "base_bullet.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <vector>
using namespace sf;
class base_gun{
    private:
        RectangleShape gun_body;
        Clock timer_for_fire;
    public:
        base_gun(){
            // Vector2f pos_for_gun = .get_soldier_pos();
            // pos_for_gun.x += 7;
            // pos_for_gun.y -=30;
            gun_body.setOrigin({0,1.5f});
            gun_body.setFillColor(Color::Cyan);
            gun_body.setSize({25,3});
        }
        bool ready_to_fire = true;
        float angle;
        void gun_move_and_fire(RenderWindow &window, std::vector<bullet> &bullet_vector, Vector2f target_pos ,Vector2f owner_pos){// for up down movement bcs of mouse
            float delta_x_to_entity = target_pos.x - owner_pos.x;
            float delta_y_to_entity = target_pos.y - owner_pos.y ;
            float angle_formed = atan2(delta_y_to_entity, delta_x_to_entity); 
            gun_body.setRotation(radians(angle_formed));

            float gun_width = gun_body.getSize().x;
            float direction = gun_body.getScale().x;
            // direction 1 -> width + , direction -1 -> width -
            Vector2f muzzel_offset = {gun_width*direction, 1.5f} ;
            Vector2f final_pos_o_bullet = gun_body.getTransform().transformPoint( muzzel_offset);


            gun_body.setPosition(owner_pos) ;
            if((timer_for_fire.getElapsedTime().asSeconds()) >= 1.0f){ 
                bullet_vector.emplace_back(final_pos_o_bullet ,angle_formed);// fire bullet
                timer_for_fire.restart() ;// standard time
            }
        }
        void display_gun(RenderWindow &window, Vector2f owner_pos){
            gun_body.setPosition(owner_pos);
            window.draw(gun_body);
        }
        void changing_gnn_side(float scale){
            gun_body.setScale({scale, scale});
        }
        
        
};
#endif