

#include "tetris_scene.hpp"



void tetris_scene::load_entities(update_context* ctx)
{
    ctx->add_entity(new tetromino(TETROMINO_TYPE_T));
    this->set_entities_loaded();
}


