#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "gun.hpp"
#include "soldier.hpp"
#include <optional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace std;
using namespace sf;
int main(){
    bool entity_alive = true; // TEMPO
    // Texture battle_background_loading("assets\\background.png");
    // Sprite battle_background(battle_background_loading);    

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
    Game_State current_status = Main_Menu;

    class_player player;
    float delta_time; //IMP delta
    RectangleShape map_arr[10];
    

    Clock delta_clock; // IMP delta

    View player_following_camera({0,0},{1080,720}); //defining scope of camera
    RenderWindow window(VideoMode({1080,720}), "Avanti Savoia");
    window.setFramerateLimit(120);

    // FloatRect window_boundry(Vector2f{0.0f,0.0f}, Vector2f{window.getDefaultView().getSize()});

    vector<bullet> bullet_vec ; // for bullets
    vector<class_enemy> enemy_vec; // for enemeies

    while(window.isOpen()){
        Time delta_elapsed_time = delta_clock.restart();
        delta_time = delta_elapsed_time.asSeconds();
        // if(enemy_1.hp <= 0) emy_is_alive = false;
        if(player.hp <= 0) player.is_soldier_alive = false;        
        while(const optional<Event> event = window.pollEvent()){
             /*runs until there is input from user     
             waits for the OS's input so very slow for repeted things.
             used for one off tings like:
                seeing the map, opening the menu etc.  */
            if (event -> is<Event::Closed>()){
                window.close();
                }  
            // if((Mouse::isButtonPressed(Mouse::Button::Right)) && (player.soldier_body_colour() == Color::Green)){
            //     player.melee();
            //     for(auto& enemy : enemy_vec){
            //         if((abs(player.get_soldier_pos().x - enemy.get_soldier_pos().x) <= 21 && abs(player.get_soldier_pos().y - enemy.get_soldier_pos().y) < 10.0f) && (enemy.hp > 0.0f)){  // checking y axis to only kill the enemy in close proxmity, with a small difference for flexibility. 
            //             enemy.hp-= (50.0f);
            //         }
            //     }
            // }       
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
                Vector2f pos_on_creation = {1000,580};
                for(char enemies = 1; enemies <= 5 ; enemies ++ ){
                    enemy_vec.emplace_back(class_enemy ({pos_on_creation}));
                    pos_on_creation.x += 600;
                }
                // end of enemy creation loop
                current_status = Battle;
                player.hp = 100.0f;
                // map creation:
                float xaxis_platforms = 1000.0f; 
                for(char i = 0; i < 10; i++){
                    RectangleShape body;
                    body.setFillColor(Color::White);
                    if (i%2 != 0) {
                        body.setSize({580,40});
                        body.setPosition({xaxis_platforms,600});
                        xaxis_platforms += 580;
                    }
                    else {
                        body.setSize({20,10}) ;
                        body.setPosition({xaxis_platforms,630});
                        xaxis_platforms += 20;
                    }
                    map_arr[i] = body ;
                }
                player.reset_pos(); // 20,550
            }    
            battle_song.play();
            break;
        case Battle:
            main_menu_song.stop();
            for(char i = 0; i<10; i++) window.draw(map_arr[i]);
            // window.draw(battle_background);

            //---CODE CONCERNED WITH PLAYER START---//
            player_following_camera.setCenter({player.get_soldier_pos().x+200,player.get_soldier_pos().y - 200});
            window.setView(player_following_camera);

            if(player.is_soldier_alive){
                player.plr_mov(delta_time);
                player.fire_player(delta_time, window, bullet_vec);
                player.display_soldier(window);                
            }      
            //---CODE CONCERNED WITH PLAYER END---//



            //---CODE CONCERNED WITH ENEMY START ---//

            for(class_enemy& emy : enemy_vec){
                if(emy.hp <= 0){
                    emy.is_soldier_alive = false;
                }
                else if(emy.is_soldier_alive){
                    emy.dist_base_attack_mode(window, bullet_vec,player.get_soldier_pos(),delta_time);
                    if(emy.emy_in_melee == true) player.hp -= (20.0f*delta_time);
                    emy.display_troop_gun(window);
                }
            }
            // for(class_enemy& enemy : enemy_vec){ // loop to render enemy
            //     if (enemy.is_soldier_alive) enemy.display_troop_gun(window);
            // }
            //---CODE CONCERNED WITH ENEMY END ---//
            for(class_enemy& emy : enemy_vec){
                for(bullet& bullet : bullet_vec){
                    if(emy.get_hitbox().findIntersection(bullet.get_hitbox())){
                        bullet.did_it_hit = true;
                        emy.hp -= (20.0f); 
                    }
                    if( player.get_hitbox().findIntersection(bullet.get_hitbox())){ // need to worry about this logic when allies are added
                        bullet.did_it_hit = true;
                        player.hp -=(5.0f); // bcs damage is recorded 4 times per hit
                    }
                    // else if((bullet.bullet_pos().y > 1000.0f || bullet.bullet_pos().y > -1000.0f ) || (bullet.bullet_pos().x > 2000.0f || bullet.bullet_pos().x < -2000.0f)) bullet.did_it_hit = true; // casuing issues, somehow when this was running,no one, neither player nor enemy could fire
                }
            }
            //---CODE CHECKING BULLET HITS START---//
            for(auto& a_bullet : bullet_vec ){
                a_bullet.render_bullet(window, delta_time);
            }
            bullet_vec.erase(remove_if(bullet_vec.begin(), bullet_vec.end(), [](bullet& bullet){return bullet.did_it_hit; }), bullet_vec.end()); // IMP
            enemy_vec.erase(remove_if(enemy_vec.begin(), enemy_vec.end(), [](class_enemy& enemy){ return ! enemy.is_soldier_alive;}), enemy_vec.end()); // IMP
            //---CODE CHECKING BULLET HITS END---//

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