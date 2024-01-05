#ifndef B_BISHOP_H
#define B_BISHOP_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include "bishop.h"
using namespace sf;

template<class T, class U>
class B_Bishop : public Bishop<T, U>
{

public:

B_Bishop(std::string png_path) 
{
    this->tex.loadFromFile(png_path);
	this->sprite.setTexture(this->tex);
    this->sprite.setScale(0.95, 0.95);
}

~B_Bishop()
{

}

};

#endif