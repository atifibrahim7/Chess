#include<iostream>
#include "game.h"
using namespace std;

int main()
{
    Game <int,int>g;

    if (g.start_menu() == 1)
    {
        g.name_menu();
        g.start_game();
    }
        
    return 0;
}