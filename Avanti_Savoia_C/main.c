#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "soldier.h"

enum game_state_dtype {main_menu, battle, victory, defeat, credits};
enum game_state_dtype GAME_STATES = main_menu;

int main(){

    bullet total_bullets[100];

    //-------------------------//making weapons- start//-----------------------------//
    weapon* Carc_ptr = (weapon*) malloc(sizeof(weapon)); 
    if(Carc_ptr != NULL)*Carc_ptr = (weapon){1,10}; // using a compound literal.
    else return -1;

    weapon* Dag_ptr = (weapon*) malloc(sizeof(weapon)); 
    if(Dag_ptr != NULL)*Dag_ptr = (weapon){0.5f,40}; 
    else return -1;

    weapon* Villar_ptr = (weapon*) malloc(sizeof(weapon)); 
    if(Villar_ptr != NULL)*Villar_ptr = (weapon){0.5,10}; 
    else return -1;
    //-------------------------//meaking weapons - end//-----------------------------//

    //-------------------------//creatimg player - start//-----------------------------//

    soldier player = {{50,50,30,50},100.0f,{Carc_ptr,0,0},false,true};
    soldier* ply_ptr = &player;

    //-------------------------//creating player - end//-----------------------------//

    InitWindow(1920,1080,"Avanti Savoia");  // creates a single window object
    Texture2D main_menu_bg = LoadTexture("D:\\programming\\trying_game_dev\\Avanti_Savoia_C\\main_menu.png");
    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        ClearBackground(BLACK);
        
        //----------------------------------------//begin drawing//----------------------------------------//
        BeginDrawing(); 

            //-------------------------//game states - start//-----------------------------//
        switch(GAME_STATES){
            case (main_menu):
                DrawTexture(main_menu_bg,0,0,WHITE);
                if(IsKeyPressed(KEY_ENTER)) GAME_STATES = battle;
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