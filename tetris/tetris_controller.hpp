
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

    vector<tetromino_type> type_pool;
    const int type_pool_size = 2;
public:
    tetris_controller();
    void update(update_context* ctx);

    void store_tetromino();
    void safe_store_tetromino(update_context* ctx);

    void new_controlled_block(update_context* ctx);
    tetromino_type new_block_type();
};



}




