#ifndef W_KING_H
#define W_KING_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "king.h"
using namespace sf;

template<class T, class U>
class W_King : public King<T, U>
{

public:

W_King(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
	this->sprite.setScale(0.95, 0.95);
	// sprite.setScale(0.75,0.75);
}

~W_King()
{
	
}
};

#endif