#include "raylib.h"
enum weapon_d_type {carbine, dagger, grenade};

typedef struct{
    Rectangle body;
    float health ;
    enum weapon_d_type weapons[3] ;
    bool in_melee_mode;
    bool is_alive; // might be removed
     
}soldier;

soldier player = {{50,50,30,50},100.0f};
soldier* ply_ptr = &player;

void display_soldier( Rectangle rec, Color colour){
    DrawRectangleRec(rec,colour);
}

void player_ctrls(soldier* ply_ptr){
    //----------------------------------------//movement-start//----------------------------------------//
    if(IsKeyDown(KEY_W))  {
        if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))  ply_ptr->body.y -= 4 ;
        else ply_ptr->body.y -= 2 ;
    }
    else if(IsKeyDown(KEY_A))  {
        if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))  ply_ptr->body.x -= 4 ;
        else ply_ptr->body.x -= 2 ;
    }
    else if(IsKeyDown(KEY_S))  {
        if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))  ply_ptr->body.y += 4 ;
        else ply_ptr->body.y += 2 ;
    }
    else if(IsKeyDown(KEY_D))  {
        if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))  ply_ptr->body.x += 4 ;
        else ply_ptr->body.x += 2 ;
    }
    //----------------------------------------//movement end//----------------------------------------//

    //----------------------------------------//melee,shotting-start//----------------------------------------//
    if(IsMouseButtonPressed(KEY_LEFT)){
        // if melee mode -> melee damage
        // else shoot
    }
    else if(IsMouseButtonPressed(KEY_RIGHT)){
        // enter melee mode
    }
    else if(IsMouseButtonPressed(KEY_RIGHT)){
        // enter melee mode
    }
    //----------------------------------------//melee,shotting-end//----------------------------------------//
    
}
