#pragma once
#include "raylib.h"
class base_soldier{
    public:
        base_soldier();
        void display_soldier();
    protected:
        Vector3 Position ;  
        Vector3 Size;
};
class Player : public base_soldier{
    public:
        Player();
        void wasd_move(float delta_time);
        void camera_move(Camera3D &camera_3d);
};