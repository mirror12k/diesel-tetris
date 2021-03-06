
#pragma once

#include "../diesel/diesel.hpp"


namespace tetris
{

using diesel::update_context;
using diesel::drawing_context;


enum tetromino_type {
    TETROMINO_TYPE_S,
    TETROMINO_TYPE_Z,

    TETROMINO_TYPE_L,
    TETROMINO_TYPE_J,

    TETROMINO_TYPE_T,
    TETROMINO_TYPE_O,
    TETROMINO_TYPE_I,
};


struct block_piece {
    int x;
    int y;
    int color_frame;

    block_piece (int x, int y, int color_frame);
};


class tetromino : public diesel::graphic_entity
{
public:
    vector<block_piece> block_pieces;
    int box_width, box_height;

    bool grounded = false;

    tetromino(tetromino_type type);
    tetromino(const vector<block_piece>& block_pieces);

    void update(update_context* ctx);
    void draw(drawing_context* ctx);

    void on_added(update_context* ctx);
    void on_removed(update_context* ctx);


    void append(const vector<block_piece>& block_pieces, int offsetx=0, int offsety=0);

    void clear_line(int height);

    void compute_box();

    void rotate_90();
    void rotate_270();

    bool collides(const tetromino* part) const;
    bool collides(const SDL_Rect* rect) const;


};



}


