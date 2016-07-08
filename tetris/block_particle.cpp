
#include "block_particle.hpp"

namespace tetris
{



block_particle::block_particle(int x, int y, int timer)
: diesel::graphic_entity("assets/tetris_block_silver.png", 20, 20)
{
    this->move_to(x, y);
    this->timer = timer;
    this->max_timer = timer;

    this->vx = rand() % 5 - 2;
    this->vy = rand() % 5 - 2;
}


void block_particle::update(update_context* ctx)
{
    if (--this->timer == 0)
    {
        ctx->remove_entity(this);
    }
    else
        this->move(this->vx, this->vy);
}

void block_particle::draw(drawing_context* ctx)
{
    ctx->set_sprite_transparency(&this->sprite, ((float)this->timer / this->max_timer) * 255);
    ctx->draw_sprite(&this->sprite);
}




}
