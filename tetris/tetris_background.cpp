
#include "tetris_background.hpp"

namespace tetris
{



tetris_background::tetris_background()
: diesel::tiled_entity("assets/tetris_background.png", 20, 20, 4, 4, 800/20, 640/20)
{
    for (int x = 0; x < 800/20; x++)
        for (int y = 0; y < 640/20; y++)
            this->set_value(x, y, 2, 0);

    for (int x = 2; x < 200/20 + 2; x++)
        for (int y = 2; y < 600/20; y++)
            this->set_value(x, y, 1, 0);

    for (int y = 2; y < 600/20; y++)
        this->set_value(1, y, 0, 2);

    for (int y = 2; y < 600/20; y++)
        this->set_value(12, y, 2, 2);

    for (int x = 2; x < 200/20 + 2; x++)
        this->set_value(x, 1, 1, 1);

    for (int x = 2; x < 200/20 + 2; x++)
        this->set_value(x, 30, 1, 3);

}



}
