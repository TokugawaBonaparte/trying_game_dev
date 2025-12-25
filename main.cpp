#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
using namespace std;
using namespace sf;
class soldier{
    public:
    soldier(){ //constructor
        body.setSize(Vector2f(20,50));
        body.setPosition({20,550});
        body.setFillColor(Color::Green);
         
        }
        void reset_melee(){
            if((melee_timer.getElapsedTime().asSeconds() >  0.2f) && (body.getFillColor() == Color::Red)){
                body.setFillColor(Color::Green);
                }
        }
        void melee(){
            body.setFillColor(Color::Red);
            melee_timer.restart(); //resets to 0 .
        }
        void reset_pos(){
            body.setPosition({20,550});
        }
        void display_troop(RenderWindow& window){
            window.draw(body);
        }
        void move(float x, float y){
            body.move(Vector2f(x, y));
        }
        int healt = 100;
        int damage = 10;
private:
    RectangleShape body;
    Clock melee_timer;
};
float speed = 0.1;
int main(){
    RenderWindow window(VideoMode({800, 600}), "Avanti Savoia");
    soldier player;
    while(window.isOpen()){
        while(const optional event = window.pollEvent()){
             /*runs until there is input from user
             waits for the OS's input so very slow for repeted things.
             used for one off tings like:
                seeing the map, opening the menu etc.  */
                if(event -> is<Event::KeyPressed>()){
                    if(Keyboard::isKeyPressed(Keyboard::Key::Space)){
                        player.melee();
                    }
                }
                if (event -> is<Event::Closed>()){
                    window.close();
                    }
            }
        // movement
        if(Keyboard::isKeyPressed(Keyboard::Key::LShift)){ //sprinting
            if(Keyboard::isKeyPressed(Keyboard::Key::D)){
                player.move(0.2,0);
            }
            else if(Keyboard::isKeyPressed(Keyboard::Key::A)){
                player.move(-0.2,0);
            }
        }
        if(Keyboard::isKeyPressed((Keyboard::Key::D))){ // IMP
            player.move(speed,0); // wrong to type {speed,0}
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::A)){
            player.move(-speed,0);
        }
        // if(Event::KeyPressed::shift){
        // }
        if(Keyboard::isKeyPressed(Keyboard::Key::R)){
            player.reset_pos();
        }
        player.reset_melee();
        




        window.clear(); // IMP.
        player.display_troop(window); //  if using .draw directly. -> error
        window.display();

    }

    return 0;
}
