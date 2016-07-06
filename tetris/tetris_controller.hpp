
#pragma once

#include "tetromino.hpp"

namespace tetris
{



class tetris_controller : public diesel::service
{
private:
    tetromino* controlled_tetromino = nullptr;
    tetromino* stored_tetromino = nullptr;

    bool keystate_a = false, keystate_d = false;
    bool keystate_q = false, keystate_e = false;
    bool keystate_w = false;
    // keystate_s behaves differently than the others
    bool keystate_s = false;
public:
    tetris_controller();
    void update(update_context* ctx);

    void store_tetromino();
};



}




