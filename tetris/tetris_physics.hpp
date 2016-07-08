
#pragma once

#include "tetromino.hpp"
#include "block_particle.hpp"


namespace tetris
{



class tetris_physics_service : public diesel::entity_service<tetromino>
{
private:
    int physics_tick = 0;
    int physics_interval = 30;

    SDL_Rect ground, left_wall, right_wall;

    tetromino* total_piece;

public:
    tetris_physics_service();

    void on_added(update_context* ctx);
    void update (update_context* ctx);

    void ground_piece(update_context* ctx, tetromino* part);
    int complete_lines(update_context* ctx);

    bool collides(tetromino* part);
    tetromino* collides_tetromino(tetromino* part);

    bool try_move(tetromino* part, int dx, int dy);
    bool try_rotate_90(tetromino* part);
    bool try_rotate_270(tetromino* part);

};



}


