#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <bits/stdc++.h>
#include "base_gun.hpp"
#include "base_gun.hpp"
#include "base_soldier.hpp"
#include <optional>
#include <SFML/Graphics/Text.hpp>
using namespace std;
using namespace sf;

int main(){
    bool entity_alive = true; // TEMPO

    Font font("C:\\Users\\Ayush\\OneDrive\\Desktop\\programming\\trying_game_dev\\assets\\font\\adler\\adler.ttf");
    Text main_menu_text(font);
    Text Defeat_Screen_text(font);
    Text Victory_Screen_text(font);

    enum Game_State {Main_Menu,Battle, Victory_Screen, Defeat_Screen,Credits_Screen};
    class_player player;
    bool ply_is_alive = true;
    float delta_time; //IMP delta
    Game_State current_status = Main_Menu;

    Clock delta_clock; // IMP delta

    View player_following_camera({0,0},{800,600}); //defining scope of camera
    RenderWindow window(VideoMode({800, 600}), "Avanti Savoia");

    vector<bullet> bullet_vec ; // for bullets
    vector<class_enemy> enemy_vec; // for enemeies

    // start of enemy creation loop
    int trenches = 1;
    Vector2f pos_on_creation = {770,550};
    while(trenches <= 5){
        for(int enemies = 1; enemies <= 5 ; enemies ++ ){
            enemy_vec.emplace_back(class_enemy ({pos_on_creation}));
            pos_on_creation.y -=60;
        }
        trenches ++;
        pos_on_creation.x += 100 ;
        pos_on_creation.y = 550;
    }
    // end of enemy creation loop

    while(window.isOpen()){
        Time delta_elapsed_time = delta_clock.restart();
        delta_time = delta_elapsed_time.asSeconds();
        // if(enemy_1.hp <= 0) emy_is_alive = false;
        if(player.hp <= 0) ply_is_alive = false;
       
        //Start of deletion loop and health lessning of enemy :
        
        // end of deletion loop and health lessening
        
        while(const optional<Event> event = window.pollEvent()){
             /*runs until there is input from user
             waits for the OS's input so very slow for repeted things.
             used for one off tings like:
                seeing the map, opening the menu etc.  */
            if (event -> is<Event::Closed>()){
                window.close();
                }  
            if((Mouse::isButtonPressed(Mouse::Button::Right)) && (player.soldier_body_colour() == Color::Green)){
            player.melee();
        //     if((abs(player.get_soldier_pos().x - .get_soldier_pos().x) <= 25) && (emy_is_alive)){ // temporary enemy_1. later changed by for loop over list of enemies with nearest one being stabbed.
        //         enemy_1.hp -= (30.0f );
        //     }
        // }
            }       
        }
    
                   
        window.clear(); // IMP.

        switch(current_status){
            case Main_Menu:
                main_menu_text.setString("Press Enter to Go into battle");
                main_menu_text.setCharacterSize(30);
                main_menu_text.setFillColor(Color::White);
                window.draw(main_menu_text);
                    if(Keyboard::isKeyPressed(Keyboard::Key::Enter)) current_status = Battle;
                    break;
            case Battle:
                player_following_camera.setCenter({player.get_soldier_pos().x+200,player.get_soldier_pos().y - 200});
                window.setView(player_following_camera);
                if(player.is_soldier_alive) player.display_move_fire_player(delta_time, window, bullet_vec);
                
                for(auto& a_bullet : bullet_vec ){
                        a_bullet.render_bullet(window, delta_time);
                }

                for(auto& enemy : enemy_vec ){
                    if (enemy.is_soldier_alive){  // enemy
                        enemy.display_troop(window);
                        enemy.dist_base_attack_mode(player.get_soldier_pos(),delta_time);
                        if(enemy.emy_in_melee == true) player.take_damage(20.0f);
                    }
                }

                for(auto& bullet : bullet_vec){
                    for(auto& enemy : enemy_vec){
                        if(enemy.get_hitbox().findIntersection(bullet.get_hitbox())){
                        bullet.did_it_hit = true;
                        enemy.take_damage(20.0f); 
                        }
                    }
                }
                bullet_vec.erase(remove_if(bullet_vec.begin(), bullet_vec.end(), [](bullet& bullet){return bullet.did_it_hit; }), bullet_vec.end()); // IMP
                enemy_vec.erase(remove_if(enemy_vec.begin(), enemy_vec.end(), [](class_enemy& enemy){ return ! enemy.is_soldier_alive;}), enemy_vec.end()); // IMP
                
                if(enemy_vec.empty()) current_status = Victory_Screen;
                else if(player.hp <= 0) current_status = Defeat_Screen;
                break;
            case Victory_Screen:
                window.setView(window.getDefaultView());
                Victory_Screen_text.setString("You Won ! \n Viva la Italia !");
                window.draw(Victory_Screen_text);
                break;
             case Defeat_Screen:
             window.setView(window.getDefaultView());
                Defeat_Screen_text.setString("Defeat. \n siamo stati sconfitti, moriamo tutti");
                window.clear(Color :: Red);
                window.draw(Defeat_Screen_text);
                break;
            case Credits_Screen:
                break;
        }
        window.display();
    }
    return 0;
}