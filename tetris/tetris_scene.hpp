
#pragma once

#include "tetromino.hpp"

namespace tetris
{

class tetris_scene : public diesel::scene
{
public:
    void load_entities(update_context* ctx);
};


}



