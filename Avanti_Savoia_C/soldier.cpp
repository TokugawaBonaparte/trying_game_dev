#include "raylib.h"
#include "soldier.hpp"
//player :
base_soldier::base_soldier(){
    Size = {1,1,1};
}
Player::Player(){
    Position = {0,0.5,0};
};
void Player::wasd_move(float delta_time){
    if(IsKeyDown(KEY_W)){
        Position.z -= 2*delta_time;
    }
     if(IsKeyDown(KEY_A)){
        Position.x -= 2*delta_time;
    }
     if(IsKeyDown(KEY_S)){
        Position.z += 2*delta_time;
    }
     if(IsKeyDown(KEY_D)){
        Position.x += 2*delta_time;
    }
}
void Player::camera_move(Camera3D &cam){
    cam.target = Position;
    cam.position.x = Position.x + 0;
    cam.position.y = Position.y + 6;
    cam.position.z = Position.z + 8;
}
//base_class
void base_soldier::display_soldier(){
    DrawCubeV(Position,Size,GREEN);
}