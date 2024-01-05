#ifndef W_KNIGHT_H
#define W_KNIGHT_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "knight.h"
using namespace sf;

template<class T, class U>
class W_Knight : public Knight<T, U>
{

public:

W_Knight(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
    this->sprite.setScale(0.95, 0.95);
}

W_Knight()
{
    
}

};

#endif