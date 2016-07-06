
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

    this->compute_box();
}



tetromino::tetromino(const vector<block_piece>& block_pieces)
: diesel::graphic_entity("assets/tetris_block_multicolor.png", 20, 20, 8)
{
    this->block_pieces = block_pieces;
    this->compute_box();
}



void tetromino::update(update_context* ctx)
{
    if (rand() % 115 == 0)
        this->rotate_90();
}




void tetromino::draw(drawing_context* ctx)
{
    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
        ctx->draw_sprite_rect(&this->sprite, iter->x * 20, iter->y * 20);
}



void tetromino::on_added(update_context* ctx)
{
    diesel::entity_service<tetromino>* phys = ctx->get_service<diesel::entity_service<tetromino>>("service::tetris::physics");
    phys->register_entity(this);
}
void tetromino::on_removed(update_context* ctx)
{
    diesel::entity_service<tetromino>* phys = ctx->get_service<diesel::entity_service<tetromino>>("service::tetris::physics");
    phys->unregister_entity(this);
}



void tetromino::compute_box()
{
    int width = 0;
    int height = 0;
    for (vector<block_piece>::iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
    {
        if (iter->x >= width)
            width = iter->x + 1;
        if (iter->y >= height)
            height = iter->y + 1;
    }

    this->sprite.rect.w = width * 20;
    this->sprite.rect.h = height * 20;
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

bool rects_collide(const SDL_Rect* r1, const SDL_Rect* r2)
{
    if ((r1->x >= r2->x + r2->w) || (r2->x >= r1->x + r1->w)
             || (r1->y >= r2->y + r2->h) || (r2->y >= r1->y + r1->h))
        return false;
    else
        return true;
}

bool tetromino::collides(const tetromino* part) const
{
    if (part->collides(&this->sprite.rect))
    {
        SDL_Rect block_rect;
        block_rect.w = 20;
        block_rect.h = 20;
        for (vector<block_piece>::const_iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
        {
            block_rect.x = this->sprite.rect.x + iter->x * 20;
            block_rect.y = this->sprite.rect.y + iter->y * 20;
            if (part->collides(&block_rect))
                return true;
        }
    }

    return false;
}

bool tetromino::collides(const SDL_Rect* rect) const
{
    if (rects_collide(&this->sprite.rect, rect))
    {
        SDL_Rect block_rect;
        block_rect.w = 20;
        block_rect.h = 20;
        for (vector<block_piece>::const_iterator iter = this->block_pieces.begin(), iter_end = this->block_pieces.end(); iter != iter_end; iter++)
        {
            block_rect.x = this->sprite.rect.x + iter->x * 20;
            block_rect.y = this->sprite.rect.y + iter->y * 20;
            if (rects_collide(&block_rect, rect))
                return true;
        }
    }

    return false;
}

}



