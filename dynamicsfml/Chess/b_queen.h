#ifndef B_QUEEN_H
#define B_QUEEN_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "queen.h"
using namespace sf;

template<class T, class U>
class B_Queen : public Queen<T, U>
{

public:

B_Queen(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
	// sprite.setScale(0.75,0.75);
	this->sprite.setScale(0.95, 0.95);
}

~B_Queen()
{
	
}

};

#endif