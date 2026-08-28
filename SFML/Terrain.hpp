#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include "SFML/Graphics.hpp"
#include "soldier.hpp"
class Terrain{
    public:
        Terrain(float x, float y, float length,float height);
        void collision_with_soldier(base_soldier& soldier,float delta_time);
        void display_terrain(RenderWindow &win);
    protected:
        RectangleShape base;
};
#endif