#include<iostream>
#include "game.h"
using namespace std;

int main()
{   
    int state; 
    Game <int,int>g;
    do
    {
    if (g.start_menu() == 1)
    {
        g.name_menu();
        state=  g.start_game();
    }
    if (state == 111) break; 
    } while (99); 
        
    return 0;
}