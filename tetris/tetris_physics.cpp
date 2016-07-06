
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

        SDL_Rect ground;
        ground.x = 0;
        ground.y = 600;
        ground.w = 800;
        ground.h = 40;

        for (list<tetromino*>::iterator iter = this->registered_entites.begin(), iter_end = this->registered_entites.end();
                iter != iter_end; iter++)
        {
            if (not (*iter)->grounded)
            {
                (*iter)->move(0, 20);
                if ((*iter)->collides(&ground) || this->collides(*iter))
                {
                    (*iter)->move(0, -20);
                    (*iter)->grounded = true;
                }
            }
        }
    }
}



tetromino* tetris_physics_service::collides(tetromino* part)
{
    for (list<tetromino*>::iterator iter = this->registered_entites.begin(), iter_end = this->registered_entites.end();
            iter != iter_end; iter++)
    {
        if ((*iter != part) && ((*iter)->collides(part)))
            return *iter;
    }
    return nullptr;
}



}

