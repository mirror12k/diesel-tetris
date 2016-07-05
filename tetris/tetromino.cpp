
#include "tetromino.hpp"



tetromino::tetromino(tetromino_type type)
: diesel::graphic_entity("assets/tetris_block_multicolor.png", 20, 20, 8), type(type)
{}



void tetromino::update(update_context* ctx)
{
    if (rand() % 100 == 0)
        this->type = (tetromino_type)(rand() % 7);
}





void tetromino::draw(drawing_context* ctx)
{
    switch (this->type)
    {
    case TETROMINO_TYPE_S:
    {
        ctx->draw_sprite_offset(&this->sprite, 20, 0);
        ctx->draw_sprite_offset(&this->sprite, 40, 0);
        ctx->draw_sprite_offset(&this->sprite, 0, 20);
        ctx->draw_sprite_offset(&this->sprite, 20, 20);
        break;
    }
    case TETROMINO_TYPE_Z:
    {
        ctx->draw_sprite_offset(&this->sprite, 0, 0);
        ctx->draw_sprite_offset(&this->sprite, 20, 0);
        ctx->draw_sprite_offset(&this->sprite, 20, 20);
        ctx->draw_sprite_offset(&this->sprite, 40, 20);
        break;
    }
    case TETROMINO_TYPE_L:
    {
        ctx->draw_sprite_offset(&this->sprite, 0, 0);
        ctx->draw_sprite_offset(&this->sprite, 0, 20);
        ctx->draw_sprite_offset(&this->sprite, 0, 40);
        ctx->draw_sprite_offset(&this->sprite, 20, 40);
        break;
    }
    case TETROMINO_TYPE_J:
    {
        ctx->draw_sprite_offset(&this->sprite, 20, 0);
        ctx->draw_sprite_offset(&this->sprite, 20, 20);
        ctx->draw_sprite_offset(&this->sprite, 20, 40);
        ctx->draw_sprite_offset(&this->sprite, 0, 40);
        break;
    }
    case TETROMINO_TYPE_T:
    {
        ctx->draw_sprite_offset(&this->sprite, 0, 0);
        ctx->draw_sprite_offset(&this->sprite, 20, 0);
        ctx->draw_sprite_offset(&this->sprite, 40, 0);
        ctx->draw_sprite_offset(&this->sprite, 20, 20);
        break;
    }
    case TETROMINO_TYPE_O:
    {
        ctx->draw_sprite_offset(&this->sprite, 0, 0);
        ctx->draw_sprite_offset(&this->sprite, 0, 20);
        ctx->draw_sprite_offset(&this->sprite, 20, 0);
        ctx->draw_sprite_offset(&this->sprite, 20, 20);
        break;
    }
    case TETROMINO_TYPE_I:
    {
        ctx->draw_sprite_offset(&this->sprite, 0, 0);
        ctx->draw_sprite_offset(&this->sprite, 0, 20);
        ctx->draw_sprite_offset(&this->sprite, 0, 40);
        ctx->draw_sprite_offset(&this->sprite, 0, 60);
        break;
    }
    }
}



