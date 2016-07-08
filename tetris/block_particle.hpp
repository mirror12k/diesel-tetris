
#pragma once

#include "tetromino.hpp"




namespace tetris
{



class block_particle : public diesel::graphic_entity
{
protected:
    int vx, vy;
    int timer, max_timer;
public:
    block_particle(int x, int y, int timer);

    void update(update_context* ctx);
    void draw(drawing_context* ctx);
};



}



