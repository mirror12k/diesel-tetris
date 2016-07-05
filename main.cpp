


#include <iostream>

using std::cout;
using std::endl;


#include "diesel/diesel.hpp"



int main ()
{
    cout << "hello world" << endl;

    diesel::game game ("DTetris", 800, 640, 60);
    game.run();


    return 0;
}



