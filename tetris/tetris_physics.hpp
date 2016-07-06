
#pragma once

#include "tetromino.hpp"


namespace tetris
{



class tetris_physics_service : public diesel::entity_service<tetromino>
{
private:
    int physics_tick = 0;
    int physics_interval = 30;

public:
    tetris_physics_service();

    void update (update_context* ctx);

    tetromino* collides(tetromino* part);

};



}


