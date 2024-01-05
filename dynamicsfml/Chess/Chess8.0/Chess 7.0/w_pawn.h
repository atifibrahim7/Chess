#ifndef W_PAWN_H
#define W_PAWN_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "pawn.h"
using namespace sf;

template<class T, class U>
class W_Pawn : public Pawn<T, U>
{

public:

const int B_SIZE = 76;
int count;

W_Pawn(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
    this->sprite.setScale(0.95, 0.95);
    count = 0;
}


bool legal_move(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY) override
{
    bool flag = 0;
    this->selected = selected_piece;
    this->posX_1 = select_posX;
    this->posY_1 = select_posY;
    this->posX_2 = place_posX;
    this->posY_2 = place_posY;

    if (count == 0)
    {
        if ((this->posX_2 == this->posX_1) && (abs(this->posY_2 - this->posY_1) <= B_SIZE*2) && (this->posY_2 < this->posY_1))
        {
            flag = 1;
            count++;
        }
        if (((this->posX_2 == this->posX_1 + B_SIZE) || (this->posX_2 == this->posX_1 - B_SIZE)) && ((this->posY_2 == this->posY_1 - B_SIZE)) && (this->diagonal_flag == 1))
        {
            flag = 1;
            count++;
        }
    }

    else
    {
        if ((this->posX_2 == this->posX_1) && (abs(this->posY_2 - this->posY_1) <= B_SIZE) && (this->posY_2 < this->posY_1))
            flag = 1;  
        if (((this->posX_2 == this->posX_1 + B_SIZE) || (this->posX_2 == this->posX_1 - B_SIZE)) && ((this->posY_2 ==this-> posY_1 - B_SIZE)) && (this->diagonal_flag == 1))
            flag = 1;
    }

    this->diagonal_flag = 0;
    return flag;
}

~W_Pawn()
{
    
}
};



#endif