#ifndef base_bullet_hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp> 
#include <iostream>
#include <math.h>
using namespace sf;
class bullet{
     //so imediate access for the bullet object 
    public: 
        bullet(Vector2f bullet_pos, float angle_formed){ // IMP because we gave 2 args in vector in walk_and_fire() of base_gun class;
            bullet_body.setRadius(1.0f);   
            velocity = calc_velocity(angle_formed);     
            bullet_body.setFillColor(Color::White);
            bullet_body.setPosition(bullet_pos);
            bullet_body.setRotation(degrees(angle_formed));
            bullet_body.setOrigin({1.0f,1.0f});
            
        }bool did_it_hit = false;
        //rendering bullet
        void render_bullet(RenderWindow &window,float delta_time){
            velocity.y -= (100.0f * delta_time);
            window.draw(bullet_body);
            bullet_body.move(velocity * delta_time);
        }
        //hitbox
        FloatRect get_hitbox(){
            return bullet_body.getGlobalBounds();
        }
        //finding velocity
        float speed = 1168.0f;
        Vector2f calc_velocity(float angle){
            // float conversion_to_radian = angle *(3.14159f / 180);
            float velocity_x = cos(angle) * speed;
            float velocity_y = sin(angle) * speed;
            return {velocity_x, velocity_y};
        }
        Vector2f bullet_pos(){
            return bullet_body.getPosition();
        }
        private:
            CircleShape bullet_body; 
            Vector2f velocity;
};
#endif