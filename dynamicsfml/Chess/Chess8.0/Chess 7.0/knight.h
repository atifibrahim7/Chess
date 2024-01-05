#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "pieces.h"
using namespace sf;

template<class T, class U>
class Knight : public Pieces<T, U>
{

public:
const int B_SIZE = 76;

Knight()
{

}

bool enemy_collision(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY, Pieces<T, U>* black[], Pieces<T, U>* white[])//std::shared_ptr<Pieces>* black, std::shared_ptr<Pieces>* white) override
{
    return 0;
}

bool legal_move(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY) override
{
    bool count = 0;
    this->selected = selected_piece;
    this->posX_1 = select_posX;
    this->posY_1 = select_posY;
    this->posX_2 = place_posX;
    this->posY_2 = place_posY;

    if ((abs(this->posX_2 - this->posX_1) == B_SIZE*2) && (abs(this->posY_2 - this->posY_1) == B_SIZE))
        count = 1;
    
    if ((abs(this->posY_2 - this->posY_1) == B_SIZE*2) && (abs(this->posX_2 - this->posX_1) == B_SIZE))
        count = 1;

    return count;
}

~Knight()
{
    
}
};

#endif