#ifndef B_ROOK_H
#define B_ROOK_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "rook.h"
using namespace sf;

template<class T, class U>
class B_Rook : public Rook<T, U>
{

public:

B_Rook(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
	// sprite.setScale(0.75,0.75);
	this->sprite.setScale(0.95, 0.95);
}

~B_Rook()
{
	
}

};

#endif