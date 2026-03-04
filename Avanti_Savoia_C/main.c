#include "raylib.h"

#include "soldier.h"

enum game_state_dtype {main_menu, battle, victory, defeat, credits};
enum game_state_dtype GAME_STATES = main_menu;

int main(){


    InitWindow(1920,1080,"Avanti Savoia");  // creates a single window object
    Texture2D main_menu_bg = LoadTexture("D:\\programming\\trying_game_dev\\Avanti_Savoia_C\\main_menu.png");
    SetTargetFPS(60);
    // float frame_time = 0;
    while(!WindowShouldClose()){
        ClearBackground(BLACK);
        
        //----------------------------------------//begin drawing//----------------------------------------//
        BeginDrawing(); 

            //-------------------------//game states - start//-----------------------------//
        switch(GAME_STATES){
            case (main_menu):
                DrawTexture(main_menu_bg,0,0,WHITE);
                if(IsKeyPressed(KEY_ENTER)){
                    GAME_STATES = battle;
                }
                break;
            case (battle):
                display_soldier(ply_ptr->body,GREEN);
                player_ctrls(ply_ptr);
                break;
            case (victory):
                break;       
            case (defeat):
                break;      
            case (credits):
                DrawTexture(main_menu_bg,54,96,WHITE);
                break;                  
        }
            //-------------------------//game states - end//-----------------------------//

        
        EndDrawing();
        
        //----------------------------------------//end drawing//----------------------------------------//
    }
    CloseWindow();
    return 0;
}

// ClearBackground(RED); // clears the screen and puts <red> all over it
/* drawing a line with some thickness
Vector2 a  = {0,0};
Vector2 b  = {500,200};
DrawLineEx(a,b,10.0f,RED);
*/