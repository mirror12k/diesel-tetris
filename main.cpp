


#include <iostream>

using std::cout;
using std::endl;


#include "diesel/diesel.hpp"
#include "tetris/tetris_scene.hpp"



int main ()
{
    diesel::game game ("DTetris", 800, 640, 60);
    game.load_scene(new tetris::tetris_scene());
    game.run();


    return 0;
}



