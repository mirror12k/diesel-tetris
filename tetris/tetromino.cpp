
#include "tetromino.hpp"

namespace tetris
{



block_piece::block_piece (int x, int y)
{
    this->x = x;
    this->y = y;
}





tetromino::tetromino(tetromino_type type)
: diesel::graphic_entity("assets/tetris_block_multicolor.png", 20, 20, 8)
{

    switch (type)
    {
    case TETROMINO_TYPE_S:
    {
        this->block_pieces.push_back(block_piece(0,1));
        this->block_pieces.push_back(block_piece(1,1));
        this->block_pieces.push_back(block_piece(1,0));
        this->block_pieces.push_back(block_piece(2,0));
        break;
    }
    case TETROMINO_TYPE_Z:
    {
        this->block_pieces.push_back(block_piece(0,0));
        this->block_pieces.push_back(block_piece(1,0));
        this->block_pieces.push_back(block_piece(1,1));
        this->block_pieces.push_back(block_piece(2,1));
        break;
    }
    case TETROMINO_TYPE_L:
    {
        this->block_pieces.push_back(block_piece(0,0));
        this->block_pieces.push_back(block_piece(0,1));
        this->block_pieces.push_back(block_piece(0,2));
        this->block_pieces.push_back(block_piece(1,2));
        break;
    }
    case TETROMINO_TYPE_J:
    {
        this->block_pieces.push_back(block_piece(1,0));
        this->block_pieces.push_back(block_piece(1,1));
        this->block_pieces.push_back(block_piece(1,2));
        this->block_pieces.push_back(block_piece(0,2));
        break;
    }
    case TETROMINO_TYPE_T:
    {
        this->block_pieces.push_back(block_piece(0,0));
        this->block_pieces.push_back(block_piece(1,0));
        this->block_pieces.push_back(block_piece(1,1));
        this->block_pieces.push_back(block_piece(2,0));
        break;
    }
    case TETROMINO_TYPE_O:
    {
        this->block_pieces.push_back(block_piece(0,0));
        this->block_pieces.push_back(block_piece(1,0));
        this->block_pieces.push_back(block_piece(1,1));
        this->block_pieces.push_back(block_piece(0,1));
        break;
    }
    case TETROMINO_TYPE_I:
    {
        this->block_pieces.push_back(block_piece(0,0));
        this->block_pieces.push_back(block_piece(0,1));
        this->block_pieces.push_back(block_piece(0,2));
        this->block_pieces.push_back(block_piece(0,3));
        break;
    }
    }
}



tetromino::tetromino(const vector<block_piece>& block_pieces)
: diesel::graphic_entity("assets/tetris_block_multicolor.png", 20, 20, 8)
{
    this->block_pieces = block_pieces;
}



void tetromino::update(update_context* ctx)
{
    if (rand() % 115 == 0)
        this->rotate_90();
}




void tetromino::draw(drawing_context* ctx)
{
    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
        ctx->draw_sprite_offset(&this->sprite, iter->x * 20, iter->y * 20);
}



void tetromino::rotate_90()
{
    int farthest_x = 0;
    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
    {
        int x = iter->x;
        iter->x = -iter->y;
        if (iter->x < farthest_x)
            farthest_x = iter->x;
        iter->y = x;
    }

    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
    {
        iter->x -= farthest_x;
    }
}
void tetromino::rotate_270()
{
    int farthest_y = 0;
    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
    {
        int x = iter->x;
        iter->x = iter->y;
        iter->y = -x;
        if (iter->y < farthest_y)
            farthest_y = iter->y;
    }

    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
    {
        iter->y -= farthest_y;
    }
}



}



