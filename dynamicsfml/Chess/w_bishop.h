#ifndef W_BISHOP_H
#define W_BISHOP_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "bishop.h"
using namespace sf;

template<class T, class U>
class W_Bishop : public Bishop<T, U>
{

public:

W_Bishop(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
    this->sprite.setScale(0.95, 0.95);
}

~W_Bishop()
{

}

};

#endif