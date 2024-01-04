#ifndef PIECES_H
#define PIECES_H

#include<iostream>
#include <SFML/Graphics.hpp>
#include<memory>
using namespace sf;
using namespace std;

template<class T, class U>
class Pieces
{

public: 

Texture tex;
Sprite sprite;
int selected;
int posX_1;
int posY_1;
int posX_2;
int posY_2;
//T temp;
//U val1;
bool flag_alive;
static int death_y;
static int death_x;
static int death_y2;
static int death_x2;
bool moved;
bool upgrade_flag;


Pieces<T, U>()
{
    sprite.setScale(0.425, 0.425);
    selected = -1;
    posX_1 = -1;
    posY_1 = -1;
    posX_2 = -1;
    posY_2 = -1;
    flag_alive = 1;
    //death_y = 0;
    moved = 0;
    upgrade_flag = 0;
    //temp = 0;
    //val1 = 0;
}

virtual bool capture_piece_white(Pieces<T, U>* black[], int posX_2, int posY_2)
{

    if (death_y >= 500)
    {
        death_y = 145;
        death_x += 40;
    }
    for (int i=0; i<16; i++)
    {
        if (black[i]->sprite.getPosition().x == posX_2 && black[i]->sprite.getPosition().y == posY_2)
        {
            black[i]->sprite.setScale(0.5, 0.5);
            black[i]->flag_alive = 0;
            black[i]->sprite.setPosition(death_x, death_y);
            death_y += 40;
            return 1;
        }
    }   

    return 0;
}

virtual bool capture_piece_black(Pieces<T, U>* black[], int posX_2, int posY_2)
{
    if (death_y2 >= 500)
    {
        death_y2 = 145;
        death_x2 += 40;
    }

    for (int i=0; i<16; i++)
    {
        
        if (black[i]->sprite.getPosition().x == posX_2 && black[i]->sprite.getPosition().y == posY_2)
        {
            black[i]->sprite.setScale(0.5, 0.5);
            black[i]->flag_alive = 0;
            black[i]->sprite.setPosition(death_x2, death_y2);
            death_y += 40;
            return 1;
        }
    }   

    return 0;
}

virtual bool legal_move(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY)
{
    selected = selected_piece;
    posX_1 = select_posX;
    posY_1 = select_posY;
    posX_2 = place_posX;
    posY_2 = place_posY;

    return 1;
}

virtual bool enemy_collision(int selected_piece, int select_posX, int select_posY, int place_posX, int place_posY, Pieces<T, U>* black[], Pieces<T, U>* white[])//std::shared_ptr<Pieces>* black, std::shared_ptr<Pieces>* white)
{
    return 0;
}

~Pieces()
{
    
}

};

template<class T, class U>
int Pieces<T, U>::death_y = 145;
template<class T, class U>
int Pieces<T, U>::death_x = 1025;
template<class T, class U>
int Pieces<T, U>::death_y2 = 145;
template<class T, class U>
int Pieces<T, U>::death_x2 = 160;

#endif