#ifndef BISHOP_H
#define BISHOP_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "pieces.h"
using namespace sf;

template<class T, class U>
class Bishop : public Pieces<T, U>
{

public:
const int B_SIZE = 76;

Bishop()
{

}


bool enemy_collision(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY, Pieces<T, U>* black[], Pieces<T, U>* white[])//std::shared_ptr<Pieces>* black, std::shared_ptr<Pieces>* white) override
{
    this->selected = selected_piece;
    this->posX_1 = select_posX;
    this->posY_1 = select_posY;
    this->posX_2 = place_posX;
    this->posY_2 = place_posY;

    int count = 0;

    // Check if the rook is moving horizontally
    if (this->posY_1 == this->posY_2)
    {   
        int stepX = (this->posX_2 > this->posX_1) ? B_SIZE : -B_SIZE;
        int stepY = (this->posY_2 > this->posY_1) ? B_SIZE : -B_SIZE;

        if (this->posX_2 > this->posX_1)
        {
            for (int i = this->posX_1 + stepX; i <= this->posX_2; i += stepX)
            {
                for (int j = 0; j < 16; j++)
                {
                    if (black[j]->sprite.getPosition().x == i && black[j]->sprite.getPosition().y == this->posY_1)
                    {
                        if (i == this->posX_2)
                        {
                            return false;
                        }
                        else
                            return 1;
                    }

                    if (j == this->selected)
                        continue;
                        
                    if (white[j]->sprite.getPosition().x == i && white[j]->sprite.getPosition().y == this->posY_1)
                    {
                        return 1;
                    }
                }
            }
        }

        else
        {
            for (int i = this->posX_1 + stepX; i >= this->posX_2; i += stepX)
            {
                for (int j = 0; j < 16; j++)
                {
                    if (black[j]->sprite.getPosition().x == i && black[j]->sprite.getPosition().y == this->posY_1)
                    {
                        if (i != this->posX_2)
                        {
                            return 1;
                        }
                        else
                            return 0;
                    }

                    if (j == this->selected)
                        continue;
                        
                    if (white[j]->sprite.getPosition().x == i && white[j]->sprite.getPosition().y == this->posY_1)
                    {
                        return 1;
                    }
                }
            }
        }

    }
    // Check if the rook is moving vertically
    else if (this->posX_1 == this->posX_2)
    {
        int stepX = (this->posX_2 > this->posX_1) ? B_SIZE : -B_SIZE;
        int stepY = (this->posY_2 > this->posY_1) ? B_SIZE : -B_SIZE;
        
        if (this->posY_2 > this->posY_1)
        {
            for (int i = this->posY_1 + stepY; i <= this->posY_2; i += stepY)
            {
                for (int j = 0; j < 16; j++)
                {
                    if (black[j]->sprite.getPosition().x == this->posX_1 && black[j]->sprite.getPosition().y == i)
                    {
                        if (i == this->posY_2)
                        {
                            return false;
                        }

                        else
                            return 1;
                    }

                    if (j == this->selected)
                        continue;
        
                    if (white[j]->sprite.getPosition().x == this->posX_1 && white[j]->sprite.getPosition().y == i)
                    {
                        return 1;
                    }
                }
            }
        }

        else
        {
            for (int i = this->posY_1 + stepY; i >= this->posY_2; i += stepY)
            {
                for (int j = 0; j < 16; j++)
                {
                    if (black[j]->sprite.getPosition().x == this->posX_1 && black[j]->sprite.getPosition().y == i)
                    {
                        if (i != this->posY_2)
                        {
                            return 1;
                        }

                        else
                            return 0;
                    }

                    if (j == this->selected)
                        continue;
        
                    if (white[j]->sprite.getPosition().x == this->posX_1 && white[j]->sprite.getPosition().y == i)
                    {
                        return 1;
                    }
                }
            }
        }

    }
    
    // Check if the bishop is moving diagonally
    int deltaX = abs(this->posX_2 - this->posX_1);
    int deltaY = abs(this->posY_2 - this->posY_1);

    if (deltaX == deltaY)
    {
        int stepX = (this->posX_2 > this->posX_1) ? B_SIZE : -B_SIZE;
        int stepY = (this->posY_2 > this->posY_1) ? B_SIZE : -B_SIZE;
        int x = this->posX_1 + stepX;
        int y = this->posY_1 + stepY;

        while (x != this->posX_2 && y != this->posY_2)
        {
            for (int i = 0; i < 16; i++)
            {
                if (black[i]->sprite.getPosition().x == x && black[i]->sprite.getPosition().y == y)
                {
                    if (x == this->posX_2 && y == this->posY_2)
                    {
                        // capture_piece(black, i);
                        return 0;
                    }    
                    else
                        return 1;
                }

                if (i == this->selected)
                    continue;

                if (white[i]->sprite.getPosition().x == x && white[i]->sprite.getPosition().y == y)
                {
                    return 1; 
                }
            }

            x += stepX;
            y += stepY;
        }
    }

    return 0; // No piece on the path
}

bool legal_move(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY) override
{
    bool count = 0;
    this->selected = selected_piece;
    this->posX_1 = select_posX;
    this->posY_1 = select_posY;
    this->posX_2 = place_posX;
    this->posY_2 = place_posY;

    for (int i=0; i<8; i++)
    {
        if (((this->posX_2 == this->posX_1 + B_SIZE*i) || (this->posX_2 == this->posX_1 - B_SIZE*i)) && ((this->posY_2 == this->posY_1 + B_SIZE*i) || (this->posY_2 == this->posY_1 - B_SIZE*i)))
            count = 1;
    }

    return count;
}

~Bishop()
{
    
}
};

#endif