
#include "tetris_controller.hpp"

#include "tetris_physics.hpp"


#include <algorithm>
using std::random_shuffle;



namespace tetris
{



tetris_controller::tetris_controller()
: diesel::service("service::tetris::controller")
{}

void tetris_controller::update(update_context* ctx)
{
    if ((this->controlled_tetromino == nullptr) || (this->controlled_tetromino->grounded))
    {
        this->new_controlled_block(ctx);
    }

    const uint8_t* keystate = ctx->get_keyboard_state();

    tetris_physics_service* physics = ctx->get_service<tetris_physics_service>("service::tetris::physics");

    if ((not this->keystate_a) && (keystate[SDL_SCANCODE_A]))
        physics->try_move(this->controlled_tetromino, -20, 0);
    this->keystate_a = keystate[SDL_SCANCODE_A];

    if ((not this->keystate_d) && (keystate[SDL_SCANCODE_D]))
        physics->try_move(this->controlled_tetromino, 20, 0);
    this->keystate_d = keystate[SDL_SCANCODE_D];

    if ((not this->keystate_q) && (keystate[SDL_SCANCODE_Q]))
        physics->try_rotate_90(this->controlled_tetromino);
    this->keystate_q = keystate[SDL_SCANCODE_Q];

    if ((not this->keystate_e) && (keystate[SDL_SCANCODE_E]))
        physics->try_rotate_270(this->controlled_tetromino);
    this->keystate_e = keystate[SDL_SCANCODE_E];

    if ((not this->keystate_w) && (keystate[SDL_SCANCODE_W]))
        this->safe_store_tetromino(ctx);
    this->keystate_w = keystate[SDL_SCANCODE_W];

    if ((not this->keystate_s) && (keystate[SDL_SCANCODE_S]))
    {
        if (not physics->try_move(this->controlled_tetromino, 0, 20))
            this->keystate_s = true;
    }
    else if ((this->keystate_s) && (not keystate[SDL_SCANCODE_S]))
        this->keystate_s = false;

}


void tetris_controller::store_tetromino()
{

    if (this->stored_tetromino != nullptr)
    {
        this->stored_tetromino->grounded = false;
        this->stored_tetromino->sprite.rect.x = this->controlled_tetromino->sprite.rect.x;
        this->stored_tetromino->sprite.rect.y = this->controlled_tetromino->sprite.rect.y;
    }

    tetromino* swap = this->controlled_tetromino;
    this->controlled_tetromino = this->stored_tetromino;
    this->stored_tetromino = swap;

    this->stored_tetromino->grounded = true;
    this->stored_tetromino->sprite.rect.x = 600;
    this->stored_tetromino->sprite.rect.y = 20;
}

void tetris_controller::safe_store_tetromino(update_context* ctx)
{
    tetris_physics_service* physics = ctx->get_service<tetris_physics_service>("service::tetris::physics");

    this->store_tetromino();

    // if we don't have room here, re-swap again
    if ((this->controlled_tetromino != nullptr) && (physics->collides(this->controlled_tetromino)))
        this->store_tetromino();
}




void tetris_controller::new_controlled_block(update_context* ctx)
{
    this->controlled_tetromino = new tetromino(this->new_block_type());
    ctx->add_entity(this->controlled_tetromino);
    this->controlled_tetromino->move(40 + 60, 0);
}

tetromino_type tetris_controller::new_block_type()
{
    if (this->type_pool.size() == 0)
    {
        for (int i = 0; i < this->type_pool_size; i++)
        {
            this->type_pool.push_back(TETROMINO_TYPE_S);
            this->type_pool.push_back(TETROMINO_TYPE_Z);

            this->type_pool.push_back(TETROMINO_TYPE_L);
            this->type_pool.push_back(TETROMINO_TYPE_J);

            this->type_pool.push_back(TETROMINO_TYPE_T);
            this->type_pool.push_back(TETROMINO_TYPE_O);
            this->type_pool.push_back(TETROMINO_TYPE_I);
        }

        random_shuffle(this->type_pool.begin(), this->type_pool.end());
    }

    // i know we could just return this number, but i want to be safe

    tetromino_type type = this->type_pool.back();
    this->type_pool.pop_back();
    return type;
}



}


