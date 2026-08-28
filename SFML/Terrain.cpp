#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "Terrain.hpp"

using namespace  sf;
//---class terrain start---//
Terrain::Terrain(float x, float y, float length,float height){
    base.setPosition({x,y});
    base.setSize({length,height});
    base.setFillColor(Color::White);
}
void Terrain::collision_with_soldier(base_soldier& soldier,float delta_time){
    if(soldier.get_hitbox().findIntersection(base.getGlobalBounds())){
        soldier.move_pos({0,-10*delta_time});
        // soldier.on_ground = 1;
    }
    else {
        soldier.gravity_pull(delta_time);
        // soldier.on_ground = 0;
    }
}
void Terrain::display_terrain(RenderWindow &win){
    win.draw(base);
}
//---class terrain end---//