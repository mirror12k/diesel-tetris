
#include "tetris_physics.hpp"

namespace tetris
{



tetris_physics_service::tetris_physics_service()
: entity_service("service::tetris::physics")
{}

void tetris_physics_service::update (update_context* ctx)
{
    if (++this->physics_tick == this->physics_interval)
    {
        this->physics_tick = 0;

        for (list<tetromino*>::iterator iter = this->registered_entites.begin(), iter_end = this->registered_entites.end();
                iter != iter_end; iter++)
        {
//            if ((*iter)->grounded)
            (*iter)->move(0, 20);
        }
    }
}



tetromino* tetris_physics_service::collides(tetromino* part)
{
    for (list<tetromino*>::iterator iter = this->registered_entites.begin(), iter_end = this->registered_entites.end();
            iter != iter_end; iter++)
    {
        if ((*iter)->collides(part))
            return *iter;
    }
    return nullptr;
}



}

