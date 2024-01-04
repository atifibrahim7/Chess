#ifndef W_ROOK_H
#define W_ROOK_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "rook.h"
using namespace sf;

template<class T, class U>
class W_Rook : public Rook<T, U>
{

public:

W_Rook(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
	this->sprite.setScale(0.95, 0.95);
	// sprite.setScale(0.75,0.75);
}

~W_Rook()
{
	
}

};

#endif