#include <stdio.h>
#include "raylib.h"
#include "soldier.hpp"

int main(){
    InitWindow(1920,1080,"Avanti Savoia");
    // camera
    Camera3D cam = {0};
    cam.up = {0,2,0};
    cam.fovy = 45;
    cam.projection = CAMERA_PERSPECTIVE;
    Player player;
    while(! WindowShouldClose()){
        float delta_tine = GetFrameTime();
        ClearBackground(BLACK);
        BeginDrawing();
        BeginMode3D(cam);
        DrawGrid(100,1);

        player.wasd_move(delta_tine);
        player.display_soldier();
        player.camera_move(cam);
        // game_states()



        EndMode3D();
        EndDrawing();        
    }
}