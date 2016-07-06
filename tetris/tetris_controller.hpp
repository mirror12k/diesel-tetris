
#pragma once

#include "tetromino.hpp"

namespace tetris
{



class tetris_controller : public diesel::service
{
private:
    tetromino* controlled_tetromino = nullptr;
public:
    tetris_controller();
    void update(update_context* ctx);
};



}




