#ifndef W_QUEEN_H
#define W_QUEEN_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "queen.h"
using namespace sf;

template<class T, class U>
class W_Queen : public Queen<T, U>
{

public:

W_Queen(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
	this->sprite.setScale(0.95, 0.95);
	// sprite.setScale(0.75,0.75);
}

~W_Queen()
{

}

};

#endif