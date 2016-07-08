
#include "tetris_physics.hpp"


#include "tetris_controller.hpp"


namespace tetris
{



tetris_physics_service::tetris_physics_service()
: entity_service("service::tetris::physics")
{
    this->ground.x = 0;
    this->ground.y = 600;
    this->ground.w = 800;
    this->ground.h = 40;

    this->left_wall.x = 0;
    this->left_wall.y = 0;
    this->left_wall.w = 40;
    this->left_wall.h = 640;

    this->right_wall.x = 240;
    this->right_wall.y = 0;
    this->right_wall.w = 40;
    this->right_wall.h = 640;
}



void tetris_physics_service::on_added(update_context* ctx)
{
    this->total_piece = new tetromino(vector<block_piece>());
    this->total_piece->grounded = true;
    ctx->add_entity(this->total_piece);
}


void tetris_physics_service::update (update_context* ctx)
{
    if (++this->physics_tick == this->physics_interval)
    {
        this->physics_tick = 0;

        for (list<tetromino*>::iterator iter = this->registered_entites.begin(), iter_end = this->registered_entites.end();
                iter != iter_end; iter++)
        {
            if (not (*iter)->grounded)
            {
                if (not this->try_move(*iter, 0, 20))
                {
                    this->ground_piece(ctx, *iter);
                }
            }
        }
    }
}



void tetris_physics_service::ground_piece(update_context* ctx, tetromino* part)
{
    this->total_piece->append(part->block_pieces, part->sprite.rect.x / 20, part->sprite.rect.y / 20);
    ctx->remove_entity(part);

    tetris_controller* srv = ctx->get_service<tetris_controller>("service::tetris::controller");
    srv->new_controlled_block(ctx);

    this->complete_lines(ctx);
}



int tetris_physics_service::complete_lines(update_context* ctx)
{
    int sums [32];
    for (int i = 0; i < 32; i++)
        sums[i] = 0;

    for (vector<block_piece>::iterator iter = this->total_piece->block_pieces.begin(), iter_end = this->total_piece->block_pieces.end();
        iter != iter_end; iter++)
    {
        if ((iter->y < 32) && (iter->y >= 0))
            sums[iter->y]++;
    }

    int lines_completed = 0;
    for (int i = 0; i < 32; i++)
    {
        if (sums[i] >= 10)
        {
            lines_completed++;
            this->total_piece->clear_line(i);
            for (int x = 2; x < 12; x++)
                ctx->add_entity(new block_particle(x * 20, i * 20, 30));
        }
    }

    return lines_completed;
}


bool tetris_physics_service::collides(tetromino* part)
{
    if ((part->collides(&this->ground)) || (part->collides(&this->left_wall)) || (part->collides(&this->right_wall)))
        return true;
    else if (this->collides_tetromino(part))
        return true;
    else
        return false;
}


tetromino* tetris_physics_service::collides_tetromino(tetromino* part)
{
    for (list<tetromino*>::iterator iter = this->registered_entites.begin(), iter_end = this->registered_entites.end();
            iter != iter_end; iter++)
    {
        if ((*iter != part) && ((*iter)->collides(part)))
            return *iter;
    }
    return nullptr;
}





bool tetris_physics_service::try_move(tetromino* part, int dx, int dy)
{
    part->move(dx, dy);
    if (this->collides(part))
    {
        part->move(-dx, -dy);
        return false;
    }
    else
        return true;
}

bool tetris_physics_service::try_rotate_90(tetromino* part)
{
    part->rotate_90();
    if (this->collides(part))
    {
        part->rotate_270();
        return false;
    }
    else
        return true;
}
bool tetris_physics_service::try_rotate_270(tetromino* part)
{
    part->rotate_270();
    if (this->collides(part))
    {
        part->rotate_90();
        return false;
    }
    else
        return true;
}



}

