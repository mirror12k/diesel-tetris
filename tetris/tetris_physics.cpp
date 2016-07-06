
#include "tetris_physics.hpp"

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
//                (*iter)->move(0, 20);
                if (not this->try_move(*iter, 0, 20))
                {
//                    (*iter)->move(0, -20);
                    (*iter)->grounded = true;
                }
            }
        }
    }
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



}

