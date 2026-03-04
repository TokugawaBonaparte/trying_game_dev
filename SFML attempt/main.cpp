#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "gun.hpp"
#include "base_soldier.hpp"
#include <optional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace std;
using namespace sf;
// // ----------------- start loading all the sprites of all soldiers of every state ---------------------- //
// //ITALY 
// //idle
// Texture player_txr_loading_idle_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_idle_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_idle_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_idle_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_idle_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //walking
// Texture player_txr_loading_walking_1("assets/sprites/italy/walking/arditi_walk_1.png");
// Texture player_txr_loading_walking_2("assets/sprites/italy/walking/arditi_walk_2.png");
// Texture player_txr_loading_walking_3("assets/sprites/italy/walking/arditi_walk_3.png");
// Texture player_txr_loading_walking_4("assets/sprites/italy/walking/arditi_walk_4.png");
// Texture player_txr_loading_walking_5("assets/sprites/italy/walking/arditi_walk_5.png");
// //running
// Texture player_txr_loading_running_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_running_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_running_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_running_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_running_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //standing and firing
// Texture player_txr_loading_stand_fire_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_stand_fire_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_stand_fire_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_stand_fire_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_stand_fire_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //walking and firing
// Texture player_txr_loading_walk_fire_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_walk_fire_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_walk_fire_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_walk_fire_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_walk_fire_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //charging
// Texture player_txr_loading_charging_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_charging_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_charging_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_charging_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_charging_5("assets/sprites/italy/idle/arditi_idle_5.png");
// // engaging in melee
// Texture player_txr_loading_in_melee_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_in_melee_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_in_melee_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_in_melee_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_in_melee_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //additional sprites for running and firing
// // dead
// Texture player_txr_loading_dead_1 ("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture player_txr_loading_dead_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture player_txr_loading_dead_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture player_txr_loading_dead_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture player_txr_loading_dead_5("assets/sprites/italy/idle/arditi_idle_5.png");

// // AUSTRIA - HUNGARY 
// //idle
// Texture enemy_txr_loading_idle_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_idle_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_idle_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_idle_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_idle_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //walking
// Texture enemy_txr_loading_walking_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_walking_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_walking_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_walking_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_walking_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //running
// Texture enemy_txr_loading_running_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_running_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_running_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_running_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_running_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //standing and firing
// Texture enemy_txr_loading_stand_fire_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_stand_fire_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_stand_fire_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_stand_fire_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_stand_fire_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //walking and firing
// Texture enemy_txr_loading_walk_fire_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_walk_fire_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_walk_fire_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_walk_fire_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_walk_fire_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //charging
// Texture enemy_txr_loading_charging_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_charging_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_charging_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_charging_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_charging_5("assets/sprites/italy/idle/arditi_idle_5.png");
// // engaging in melee
// Texture enemy_txr_loading_in_melee_1("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_in_melee_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_in_melee_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_in_melee_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_in_melee_5("assets/sprites/italy/idle/arditi_idle_5.png");
// //dead
// Texture enemy_txr_loading_dead_1 ("assets/sprites/italy/idle/arditi_idle_1.png");
// Texture enemy_txr_loading_dead_2("assets/sprites/italy/idle/arditi_idle_2.png");
// Texture enemy_txr_loading_dead_3("assets/sprites/italy/idle/arditi_idle_3.png");
// Texture enemy_txr_loading_dead_4("assets/sprites/italy/idle/arditi_idle_4.png");
// Texture enemy_txr_loading_dead_5("assets/sprites/italy/idle/arditi_idle_5.png");

// //


// // MAKING SPRITES
// // ITALY
// vector<vector<s>>
// // idle
// Sprite player_txr_idle_1(player_txr_loading_idle_1);
// Sprite player_txr_idle_2(player_txr_loading_idle_2);
// Sprite player_txr_idle_3(player_txr_loading_idle_3);
// Sprite player_txr_idle_4(player_txr_loading_idle_4);
// Sprite player_txr_idle_5(player_txr_loading_idle_5);
// // walking
// Sprite player_txr_walking_1(player_txr_loading_walking_1);
// Sprite player_txr_walking_2(player_txr_loading_walking_2);
// Sprite player_txr_walking_3(player_txr_loading_walking_3);
// Sprite player_txr_walking_4(player_txr_loading_walking_4);
// Sprite player_txr_walking_5(player_txr_loading_walking_5);
// // running
// Sprite player_txr_running_1(player_txr_loading_running_1);
// Sprite player_txr_running_2(player_txr_loading_running_2);
// Sprite player_txr_running_3(player_txr_loading_running_3);
// Sprite player_txr_running_4(player_txr_loading_running_4);
// Sprite player_txr_running_5(player_txr_loading_running_5);

// //standing and firing
// Sprite player_txr_stand_fire_1(player_txr_loading_stand_fire_1);
// Sprite player_txr_stand_fire_2(player_txr_loading_stand_fire_2);
// Sprite player_txr_stand_fire_3(player_txr_loading_stand_fire_3);
// Sprite player_txr_stand_fire_4(player_txr_loading_stand_fire_4);
// Sprite player_txr_stand_fire_5(player_txr_loading_stand_fire_5);
// //walking and firing
// Sprite player_txr_walk_fire_1(player_txr_loading_walk_fire_1);
// Sprite player_txr_walk_fire_2(player_txr_loading_walk_fire_2);
// Sprite player_txr_walk_fire_3(player_txr_loading_walk_fire_3);
// Sprite player_txr_walk_fire_4(player_txr_loading_walk_fire_4);
// Sprite player_txr_walk_fire_5(player_txr_loading_walk_fire_5);
// //charging
// Sprite player_txr_charging_1(player_txr_loading_charging_1);
// Sprite player_txr_charging_2(player_txr_loading_charging_2);
// Sprite player_txr_charging_3(player_txr_loading_charging_3);
// Sprite player_txr_charging_4(player_txr_loading_charging_4);
// Sprite player_txr_charging_5(player_txr_loading_charging_5);
// // engaging in melee
// Sprite player_txr_in_melee_1(player_txr_loading_in_melee_1);
// Sprite player_txr_in_melee_2(player_txr_loading_in_melee_2);
// Sprite player_txr_in_melee_3(player_txr_loading_in_melee_3);
// Sprite player_txr_in_melee_4(player_txr_loading_in_melee_4);
// Sprite player_txr_in_melee_5(player_txr_loading_in_melee_5);
// //dead
// Sprite player_txr_dead_1(player_txr_loading_dead_1);
// Sprite player_txr_dead_2(player_txr_loading_dead_2);
// Sprite player_txr_dead_3(player_txr_loading_dead_3);
// Sprite player_txr_dead_4(player_txr_loading_dead_4);
// Sprite player_txr_dead_5(player_txr_loading_dead_5);

// // AUSTRIA - HUNGARY
// // idle
// Sprite enemy_txr_idle_1(enemy_txr_loading_idle_1);
// Sprite enemy_txr_idle_2(enemy_txr_loading_idle_2);
// Sprite enemy_txr_idle_3(enemy_txr_loading_idle_3);
// Sprite enemy_txr_idle_4(enemy_txr_loading_idle_4);
// Sprite enemy_txr_idle_5(enemy_txr_loading_idle_5);
// // walking
// Sprite enemy_txr_walking_1(enemy_txr_loading_walking_1);
// Sprite enemy_txr_walking_2(enemy_txr_loading_walking_2);
// Sprite enemy_txr_walking_3(enemy_txr_loading_walking_3);
// Sprite enemy_txr_walking_4(enemy_txr_loading_walking_4);
// Sprite enemy_txr_walking_5(enemy_txr_loading_walking_5);
// // running
// Sprite enemy_txr_running_1(enemy_txr_loading_running_1);
// Sprite enemy_txr_running_2(enemy_txr_loading_running_2);
// Sprite enemy_txr_running_3(enemy_txr_loading_running_3);
// Sprite enemy_txr_running_4(enemy_txr_loading_running_4);
// Sprite enemy_txr_running_5(enemy_txr_loading_running_5);
// //standing and firing
// Sprite enemy_txr_stand_fire_1(enemy_txr_loading_stand_fire_1);
// Sprite enemy_txr_stand_fire_2(enemy_txr_loading_stand_fire_2);
// Sprite enemy_txr_stand_fire_3(enemy_txr_loading_stand_fire_3);
// Sprite enemy_txr_stand_fire_4(enemy_txr_loading_stand_fire_4);
// Sprite enemy_txr_stand_fire_5(enemy_txr_loading_stand_fire_5);
// //walking and firing
// Sprite enemy_txr_walk_fire_1(enemy_txr_loading_walk_fire_1);
// Sprite enemy_txr_walk_fire_2(enemy_txr_loading_walk_fire_2);
// Sprite enemy_txr_walk_fire_3(enemy_txr_loading_walk_fire_3);
// Sprite enemy_txr_walk_fire_4(enemy_txr_loading_walk_fire_4);
// Sprite enemy_txr_walk_fire_5(enemy_txr_loading_walk_fire_5);
// //charging
// Sprite enemy_txr_charging_1(enemy_txr_loading_walk_fire_1);
// Sprite enemy_txr_charging_2(enemy_txr_loading_walk_fire_1);
// Sprite enemy_txr_charging_3(enemy_txr_loading_walk_fire_1);
// Sprite enemy_txr_charging_4(enemy_txr_loading_walk_fire_1);
// Sprite enemy_txr_charging_5(enemy_txr_loading_walk_fire_1);
// // engaging in melee
// Sprite enemy_txr_in_melee_1(enemy_txr_loading_in_melee_1);
// Sprite enemy_txr_in_melee_2(enemy_txr_loading_in_melee_2);
// Sprite enemy_txr_in_melee_3(enemy_txr_loading_in_melee_3);
// Sprite enemy_txr_in_melee_4(enemy_txr_loading_in_melee_4);
// Sprite enemy_txr_in_melee_5(enemy_txr_loading_in_melee_5);
// //dead
// Sprite enemy_txr_dead_1(enemy_txr_loading_dead_1);
// Sprite enemy_txr_dead_2(enemy_txr_loading_dead_2);
// Sprite enemy_txr_dead_3(enemy_txr_loading_dead_3);
// Sprite enemy_txr_dead_4(enemy_txr_loading_dead_4);
// Sprite enemy_txr_dead_5(enemy_txr_loading_dead_5);

// -------------------------- end of loading textures and sprites-------------------------------- //


int main(){
    bool entity_alive = true; // TEMPO
    Texture battle_background_loading("assets\\background.png");
    Sprite battle_background(battle_background_loading);    

    Music main_menu_song;
    Music battle_song;
    Music victory_song;
    Music credits_song;
    if( ! victory_song.openFromFile("assets/music and sounds/victory.ogg")){
        return -1;
    }
    if( ! battle_song.openFromFile("assets/music and sounds/battle.ogg")){
        return -1;
    }
    if(! main_menu_song.openFromFile("assets\\music and sounds\\main.ogg")){
        return -1;
    }
    if( ! credits_song.openFromFile("assets/music and sounds/credits.ogg")){
        return -1;
    }
    battle_song.setVolume(50.0f);
    main_menu_song.setLooping(true);
    main_menu_song.setVolume(50.0f);
    main_menu_song.play();


    Font font("assets\\font\\adler\\adler.ttf");
    Text main_menu_text_1(font);
    Text Defeat_Screen_text(font);
    Text Victory_Screen_text(font);

    Texture main_menu_bg_loading;
    if(! main_menu_bg_loading.loadFromFile("assets\\main_menu.png")) return -1;
    sf::Sprite main_menu_bg(main_menu_bg_loading);
    enum Game_State {Main_Menu,Battle, Victory_Screen, Defeat_Screen,Credits_Screen};
    class_player player;
    bool ply_is_alive = true;
    float delta_time; //IMP delta
    Game_State current_status = Main_Menu;

    Clock delta_clock; // IMP delta

    View player_following_camera({0,0},{1920,1080}); //defining scope of camera
    RenderWindow window(VideoMode({1920,1080}), "Avanti Savoia");
    window.setFramerateLimit(120);

    // FloatRect window_boundry(Vector2f{0.0f,0.0f}, Vector2f{window.getDefaultView().getSize()});

    vector<bullet> bullet_vec ; // for bullets
    vector<class_enemy> enemy_vec; // for enemeies

    while(window.isOpen()){
        delta_time = delta_clock.getElapsedTime().asSeconds();
        // if(enemy_1.hp <= 0) emy_is_alive = false;
        if(player.hp <= 0) ply_is_alive = false;        
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
                for(auto& enemy : enemy_vec){
                    if((abs(player.get_soldier_pos().x - enemy.get_soldier_pos().x) <= 21 && abs(player.get_soldier_pos().y - enemy.get_soldier_pos().y) < 10.0f) && (enemy.hp > 0.0f)){  // checking y axis to only kill the enemy in close proxmity, with a small difference for flexibility. 
                        enemy.take_damage(50.0f);
                    }
                }
            }       
        }

    window.clear(); // IMP.
    switch(current_status){
        case Main_Menu:
            player.is_soldier_alive = true;
            window.draw(main_menu_bg);
            main_menu_text_1.setString("AVANTI SAVOIA !");
            main_menu_text_1.setCharacterSize(100);
            main_menu_text_1.setFillColor(Color::Black);
            window.draw(main_menu_text_1);
            if(Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                // start of enemy creation loop
                Vector2f pos_on_creation = {2000,550};
                for(int enemies = 1; enemies <= 5 ; enemies ++ ){
                    enemy_vec.emplace_back(class_enemy ({pos_on_creation}));
                    pos_on_creation.y -=60;
                }
                // end of enemy creation loop
                current_status = Battle;
                player.hp = 100.0f;
                player.reset_pos();
            }    
            battle_song.play();
            break;
        case Battle:
            main_menu_song.stop();
            window.draw(battle_background);
            player_following_camera.setCenter({player.get_soldier_pos().x+200,player.get_soldier_pos().y - 200});
            window.setView(player_following_camera);
            if(player.is_soldier_alive){
                player.display_move_fire_player(delta_time, window, bullet_vec);
            }
            
            for(auto& a_bullet : bullet_vec ){
                    a_bullet.render_bullet(window, delta_time);
            }
            for(auto& enemy : enemy_vec){
                if (enemy.is_soldier_alive){  // enemy
                    enemy.display_troop(window);
                    // enemy.firing_timer -= delta_time;
                    // if(static_cast<float>(enemy.firing_timer <= 0)) enemy.firing_timer += 2 + (static_cast<float> (rand() %100)/100.0f);
                    if(enemy.firing_clock.getElapsedTime().asSeconds() >= 2){
                        enemy.dist_base_attack_mode(window, bullet_vec,player.get_soldier_pos(),delta_time);
                        enemy.firing_clock.restart();
                    }
                    if(enemy.in_melee == true) player.take_damage(20.0f*delta_time);
                }
                for(auto& bullet : bullet_vec){
                    if(enemy.get_hitbox().findIntersection(bullet.get_hitbox())){
                        bullet.did_it_hit = true;
                        enemy.take_damage(20.0f); 
                    }
                    if(player.get_hitbox().findIntersection(bullet.get_hitbox())){ // need to worry about this logic when allies are added
                        bullet.did_it_hit = true;
                        player.take_damage(20.0f);  
                    }
                    // else if((bullet.bullet_pos().y > 1000.0f || bullet.bullet_pos().y > -1000.0f ) || (bullet.bullet_pos().x > 2000.0f || bullet.bullet_pos().x < -2000.0f)) bullet.did_it_hit = true;
                }
            }
            bullet_vec.erase(remove_if(bullet_vec.begin(), bullet_vec.end(), [](bullet& bullet){return bullet.did_it_hit; }), bullet_vec.end()); // IMP
            enemy_vec.erase(remove_if(enemy_vec.begin(), enemy_vec.end(), [](class_enemy& enemy){ return ! enemy.is_soldier_alive;}), enemy_vec.end()); // IMP
            
            if(enemy_vec.empty()){
                current_status =  Victory_Screen;
                victory_song.play();
            }
            else if(player.hp <= 0) {
                current_status = Defeat_Screen;
                enemy_vec.clear();
            }
            break;
        case Victory_Screen:
            battle_song.stop();
            window.setView(window.getDefaultView());
            Victory_Screen_text.setString("You Won ! \n Viva la Italia !");
            window.draw(Victory_Screen_text);
            if(Keyboard::isKeyPressed(Keyboard::Key::Space)){
                current_status = Credits_Screen;
                victory_song.stop();
                credits_song.play();
            }
            break;
            case Defeat_Screen:
            battle_song.stop();
            window.setView(window.getDefaultView());
            Defeat_Screen_text.setString("Defeat. \n siamo stati sconfitti, moriamo tutti");
            window.draw(Defeat_Screen_text);
            if(Keyboard::isKeyPressed(Keyboard::Key::Space)){
                current_status = Credits_Screen;
                credits_song.play();

            }
            break;
        case Credits_Screen:
            if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                current_status = Main_Menu;
                main_menu_song.play();
                credits_song.stop();
            }
            
            break;
    }
    window.display();
    }
    return 0;
}