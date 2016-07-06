

#include "tetris_scene.hpp"
#include "tetris_physics.hpp"
#include "tetris_controller.hpp"



namespace tetris
{


void tetris_scene::load_entities(update_context* ctx)
{
    ctx->add_entity(new tetris_physics_service());
    ctx->add_entity(new tetris_controller());

//    ctx->add_entity(new tetromino(TETROMINO_TYPE_S));
//    ctx->add_entity(new tetromino(TETROMINO_TYPE_Z));
//    ctx->add_entity(new tetromino(TETROMINO_TYPE_L));
//    ctx->add_entity(new tetromino(TETROMINO_TYPE_J));
//    ctx->add_entity(new tetromino(TETROMINO_TYPE_T));
//    ctx->add_entity(new tetromino(TETROMINO_TYPE_O));
//    ctx->add_entity(new tetromino(TETROMINO_TYPE_S));
    this->set_entities_loaded();
}


}


