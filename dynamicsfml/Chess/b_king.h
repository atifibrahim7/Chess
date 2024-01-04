#ifndef B_KING_H
#define B_KING_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "king.h"
using namespace sf;

template<class T, class U>
class B_King : public King<T, U>
{

public:

B_King(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
    this->sprite.setScale(0.95, 0.95);}

~B_King()
{
	
}
};

#endif