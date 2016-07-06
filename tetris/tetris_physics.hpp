
#pragma once

#include "tetromino.hpp"


namespace tetris
{



class tetris_physics_service : public diesel::entity_service<tetromino>
{
private:
    int physics_tick = 0;
    int physics_interval = 30;

    SDL_Rect ground, left_wall, right_wall;

public:
    tetris_physics_service();

    void update (update_context* ctx);

    bool collides(tetromino* part);
    tetromino* collides_tetromino(tetromino* part);
    bool try_move(tetromino* part, int dx, int dy);

};



}


