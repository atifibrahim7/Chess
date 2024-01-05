#ifndef B_KNIGHT_H
#define B_KNIGHT_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "knight.h"
using namespace sf;

template<class T, class U>
class B_Knight : public Knight<T, U>
{

public:

B_Knight(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
    this->sprite.setScale(0.95, 0.95);
}

~B_Knight()
{
    
}

};

#endif