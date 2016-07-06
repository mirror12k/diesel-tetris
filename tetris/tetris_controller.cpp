
#include "tetris_controller.hpp"

namespace tetris
{



tetris_controller::tetris_controller()
: diesel::service("service::tetris::controller")
{}

void tetris_controller::update(update_context* ctx)
{
    if ((this->controlled_tetromino == nullptr) || (this->controlled_tetromino->grounded))
    {
        this->controlled_tetromino = new tetromino(TETROMINO_TYPE_S);
        ctx->add_entity(this->controlled_tetromino);
    }
}



}


