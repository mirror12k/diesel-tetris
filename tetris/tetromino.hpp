
#pragma once

#include "../diesel/diesel.hpp"


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



class tetromino : public diesel::graphic_entity
{
private:
    tetromino_type type;
public:
    tetromino(tetromino_type type);

    void update(update_context* ctx);
    void draw(drawing_context* ctx);

};






