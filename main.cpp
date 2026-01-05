#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
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
    Texture sample_background("C:\\Users\\Ayush\\OneDrive\\Desktop\\programming\\trying_game_dev\\assets\\background.png");
    Sprite sample_background_1(sample_background);

    Music main_menu_song;
    Music battle_song;
    Music victory_song;
    Music credits_song;
    if( ! victory_song.openFromFile("C:/Users/Ayush/OneDrive/Desktop/programming/trying_game_dev/assets/music and sounds/victory.ogg")){
        return -1;
    }
    if( ! battle_song.openFromFile("C:/Users/Ayush/OneDrive/Desktop/programming/trying_game_dev/assets/music and sounds/battle.ogg")){
        return -1;
    }
    if(! main_menu_song.openFromFile("C:\\Users\\Ayush\\OneDrive\\Desktop\\programming\\trying_game_dev\\assets\\music and sounds\\main.ogg")){
        return -1;
    }
    if( ! credits_song.openFromFile("C:/Users/Ayush/OneDrive/Desktop/programming/trying_game_dev/assets/music and sounds/credits.ogg")){
        return -1;
    }
    battle_song.setVolume(50.0f);
    main_menu_song.setLooping(true);
    main_menu_song.setVolume(50.0f);
    main_menu_song.play();
    Clock firing_timer;// for the delay in frigin of the soldiers, otherwise you die in an instant


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
    window.setFramerateLimit(120);
    FloatRect window_boundry(Vector2f{0.0f,0.0f}, Vector2f{window.getDefaultView().getSize()});

    vector<bullet> bullet_vec ; // for bullets
    vector<class_enemy> enemy_vec; // for enemeies

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
            main_menu_text.setString("Press Enter to Go into battle");
            main_menu_text.setCharacterSize(30);
            main_menu_text.setFillColor(Color::White);
            window.draw(main_menu_text);
            if(Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                // start of enemy creation loop
                Vector2f pos_on_creation = {770,550};
                for(int enemies = 1; enemies <= 5 ; enemies ++ ){
                    enemy_vec.emplace_back(class_enemy ({pos_on_creation}));
                    pos_on_creation.y -=60;
                }
                // end of enemy creation loop
                current_status = Battle;
                player.hp = 100.0f;
                player.reset_pos();
                firing_timer.restart(); 
            }    
            battle_song.play();
            break;
        case Battle:
            main_menu_song.stop();
            window.draw(sample_background_1);
            player_following_camera.setCenter({player.get_soldier_pos().x+200,player.get_soldier_pos().y - 200});
            window.setView(player_following_camera);
            if(player.is_soldier_alive) player.display_move_fire_player(delta_time, window, bullet_vec);
            
            for(auto& a_bullet : bullet_vec ){
                    a_bullet.render_bullet(window, delta_time);
            }
            for(auto& enemy : enemy_vec){
                if (enemy.is_soldier_alive){  // enemy
                    enemy.display_troop(window);
                    if(firing_timer.getElapsedTime().asSeconds() > 7.0f){
                        enemy.dist_base_attack_mode(window, bullet_vec,player.get_soldier_pos(),delta_time);
                        if(enemy.emy_in_melee == true) player.take_damage(20.0f*delta_time);
                }
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