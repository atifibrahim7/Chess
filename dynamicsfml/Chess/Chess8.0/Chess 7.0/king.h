#ifndef KING_H
#define KING_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "pieces.h"
using namespace sf;

template<class T, class U>
class King : public Pieces<T, U>
{

public:
const int B_SIZE = 76;
T val1;
U val2;

King()
{
    val1 = 0;
    val2 = 0;
}

bool legal_move(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY) override
{
    bool count = 0;
    this->selected = selected_piece;
    this->posX_1 = select_posX;
    this->posY_1 = select_posY;
    this->posX_2 = place_posX;
    this->posY_2 = place_posY;

    if ((abs(this->posX_2 - this->posX_1) <= B_SIZE) && (abs(this->posY_2 - this->posY_1) <= B_SIZE))
    {
        count = 1;
        this->moved = 1;
    }

    return count;
}

~King()
{
    
}
};

#endif