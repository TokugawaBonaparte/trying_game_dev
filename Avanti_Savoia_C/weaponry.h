#include "raylib.h"

typedef struct{
    Rectangle body;
    float reload_time;
    // float number_of_bullets per magazine or cartridge . to be added later
}gun;

gun Carcano = {{0,0,5,20},1.0f};


void bullet_mech(){
    DrawCircle(0,0,1,BLACK);
    
}