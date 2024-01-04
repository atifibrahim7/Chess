#ifndef PAWN_H
#define PAWN_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "pieces.h"
using namespace sf;

template<class T, class U>
class Pawn : public Pieces<T, U>
{

public:
static bool diagonal_flag;

Pawn()
{
    //diagonal_flag = 0;
}

virtual bool enemy_collision(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY, Pieces<T, U>* black[], Pieces<T, U>* white[])//std::shared_ptr<Pieces>* black, std::shared_ptr<Pieces>* white) override
{
    this->selected = selected_piece;
    this->posX_1 = select_posX;
    this->posY_1 = select_posY;
    this->posX_2 = place_posX;
    this->posY_2 = place_posY;

    for (int i=0; i<16; i++)
    {
        if (black[i]->sprite.getPosition().x == this->posX_1)
        {
            if (black[i]->sprite.getPosition().y == this->posY_2 && (black[i]->sprite.getPosition().x == this->posX_2) && (this->posX_1 == this->posX_2))
            {
                return 1;
            }
        }

        if ((black[i]->sprite.getPosition().y == this->posY_2) && (black[i]->sprite.getPosition().x == this->posX_2) && (this->posX_2 != this->posX_1))
        {
            this->diagonal_flag = 1;
            return 0;
        }
    }
    return 0;
}

~Pawn()
{
    
}
};

template<class T, class U>
bool Pawn<T, U>::diagonal_flag = 0;

#endif