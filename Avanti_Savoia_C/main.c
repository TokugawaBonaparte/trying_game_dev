#include "raylib.h"

#include "soldier.h"
 
int main(){


    ply_ptr->body.height = 50 ;
    ply_ptr->body.width = 20 ;
    ply_ptr->body.x = 50 ;
    ply_ptr->body.y = 50 ;


    InitWindow(1920,1080,"Avanti Savoia");  // creates a single window object
    Texture2D main_menu = LoadTexture("D:\\programming\\trying_game_dev\\Avanti_Savoia_C\\main_menu.png");
    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        ClearBackground(BLACK);
        
        //----------------------------------------begin drawing----------------------------------------//
        BeginDrawing(); // we draw the sprites between begin and end drawing(
        display_soldier(ply_ptr->body,GREEN);
        
        
        EndDrawing();
        player_ctrls(ply_ptr);
        //----------------------------------------end drawing----------------------------------------//
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