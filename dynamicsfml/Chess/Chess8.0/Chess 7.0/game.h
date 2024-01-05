#include <SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
#include<memory>
#include "menu.h"
#include "pieces.h"
#include "rook.h"
#include "w_rook.h"
#include "b_rook.h"
#include "king.h"
#include "w_king.h"
#include "b_king.h"
#include "queen.h"
#include "w_queen.h"
#include "b_queen.h"
#include "bishop.h"
#include "w_bishop.h"
#include "b_bishop.h"
#include "knight.h"
#include "w_knight.h"
#include "b_knight.h"
#include "pawn.h"
#include "w_pawn.h"
#include "b_pawn.h"
using namespace sf;
using namespace std;

const char title[] = "Chess Game";
const int B_WIDTH = 8;
const int B_HEIGHT = 8;
const int B_SIZE = 76;
const float SQUARE = B_SIZE / B_WIDTH;
const int CENTRE = SQUARE / 2;
const int HEIGHT_PIXELS = 512;
const int SIZE_PIXELS = 512/8;
const int offset_x = 335;
const int offset_y = 55;
const int SQUARE_SIZE = 76;


template<class T1, class T2>
class Game
{

private:
RectangleShape b_squares[B_HEIGHT][B_WIDTH];
Color col1 = Color::White;
Color col2 = Color::Black;
Sprite background; //Game background sprite
Texture bg_texture;
Music bg_music ,whitepieceselect , blackpieceselect , invalidmusic;


T1 posx_a;
T2 posy_a;
bool selected;
bool turn;
int selected_piece;
int place_posX;
int place_posY;
int select_posX;
int select_posY;
bool check_white;
bool check_black;
bool final_check;

    std::shared_ptr<Menu<T1, T2>> m;
    std::shared_ptr<Pieces<T1, T2>> w_rook[2];
    std::shared_ptr<Pieces<T1, T2>> b_rook[2];
    std::shared_ptr<Pieces<T1, T2>> w_king;
    std::shared_ptr<Pieces<T1, T2>> b_king;
    std::shared_ptr<Pieces<T1, T2>> w_queen;
    std::shared_ptr<Pieces<T1, T2>> b_queen;
    std::shared_ptr<Pieces<T1, T2>> w_bishop[2];
    std::shared_ptr<Pieces<T1, T2>> b_bishop[2];
    std::shared_ptr<Pieces<T1, T2>> w_knight[2];
    std::shared_ptr<Pieces<T1, T2>> b_knight[2];
    std::shared_ptr<Pieces<T1, T2>> w_pawn[8];
    std::shared_ptr<Pieces<T1, T2>> b_pawn[8];
    Pieces<T1, T2>* white_piece[16];
    Pieces<T1, T2>* black_piece[16];

float coord_x[8];
float coord_y[8];

public:
    void name_menu()
    {
        m->names_menu();
    }
// MAIN CONSTRUCTOR
Game()
{       
    whitepieceselect.openFromFile("asserts/whitemove.wav");
    blackpieceselect.openFromFile("asserts/blackmove.wav");
    bg_music.openFromFile("asserts/bgmusic.wav");
    invalidmusic.openFromFile("asserts/invalidmove.wav");
    bg_texture.loadFromFile("asserts/Board.png");

    background.setTexture(bg_texture);
    //background.setScale(0.73, 0.73);

    selected = 0;
    selected_piece = -1;
    place_posX = -1;
    place_posY = -1;
    select_posX = -1;
    select_posY = -1;
    turn = 0;
    check_white = 0;
    check_black = 0;
    final_check = 1;

        m = std::make_shared<Menu<T1, T2>>();

        w_king = std::make_shared<W_King<T1, T2>>("images/Peices/King W.png");
        b_king = std::make_shared<B_King<T1, T2>>("images/Peices/King B.png");

        w_queen = std::make_shared<W_Queen<T1, T2>>("images/Peices/Queen W.png");
        b_queen = std::make_shared<B_Queen<T1, T2>>("images/Peices/Queen B.png");

        for (int i = 0; i < 2; i++)
        {
            w_rook[i] = std::make_shared<W_Rook<T1, T2>>("images/Peices/Rook W.png");
            b_rook[i] = std::make_shared<B_Rook<T1, T2>>("images/Peices/Rook B.png");

            w_bishop[i] = std::make_shared<W_Bishop<T1, T2>>("images/Peices/Bishop W.png");
            b_bishop[i] = std::make_shared<B_Bishop<T1, T2>>("images/Peices/Bishop B.png");

            w_knight[i] = std::make_shared<W_Knight<T1, T2>>("images/Peices/Knight W.png");
            b_knight[i] = std::make_shared<B_Knight<T1, T2>>("images/Peices/Knight B.png");
        }

        // for (int i=0; i<16; i++)
        // {
        //     white_piece[i] = make_shared<Pieces>();
        //     black_piece[i] = make_shared<Pieces>();
        // }

        for (int i = 0; i < 8; i++)
        {
            w_pawn[i] = std::make_shared<W_Pawn<T1, T2>>("images/Peices/Pawn W.png");
            b_pawn[i] = std::make_shared<B_Pawn<T1, T2>>("images/Peices/Pawn B.png");
            // white_piece[i + 8] = std::move(w_pawn[i]);
            // black_piece[i + 8] = std::move(b_pawn[i]);
            white_piece[i+8] = w_pawn[i].get();
            black_piece[i+8] = b_pawn[i].get();
            // white_piece[i+8] = std::make_shared<Pieces>(std::move(w_pawn[i]));
            // black_piece[i+8] = std::make_shared<Pieces>(std::move(b_pawn[i]));
        }


    white_piece[0] = w_rook[0].get();
    white_piece[1] = w_knight[0].get();
    white_piece[2] = w_bishop[0].get();
    white_piece[3] = w_queen.get();
    white_piece[4] = w_king.get();
    white_piece[5] = w_bishop[1].get();
    white_piece[6] = w_knight[1].get();
    white_piece[7] = w_rook[1].get();

    black_piece[0] = b_rook[0].get();
    black_piece[1] = b_knight[0].get();
    black_piece[2] = b_bishop[0].get();
    black_piece[3] = b_queen.get();
    black_piece[4] = b_king.get();
    black_piece[5] = b_bishop[1].get();
    black_piece[6] = b_knight[1].get();
    black_piece[7] = b_rook[1].get();

   
}

// DRAWING BOARD HERE//
void draw_board(RenderTarget& window)
{



    for (int i=0; i<B_HEIGHT; i++)
    {
        bool color_flag = 0;

        if (i % 2 == 0)
            color_flag = 1;
        
        for (int j=0; j<B_WIDTH; j++)
        {
            b_squares[i][j].setPosition(Vector2f(j*SQUARE_SIZE + offset_x, i*SQUARE_SIZE + offset_y));
            b_squares[i][j].setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            
            if (!color_flag)
                b_squares[i][j].setFillColor(col2);
            else if(color_flag)
                b_squares[i][j].setFillColor(col1);

            color_flag = !color_flag;
        }
    }
}

// START
bool start_menu()
{
   return m->display_menu();
}

// SET POSITIONS OF PIECES
void set_positions()
{


    for (int i=0; i<8; i++)
    {
        coord_x[i] = b_squares[0][i].getPosition().x + CENTRE; 
        coord_y[i] = b_squares[i][0].getPosition().y + CENTRE; 
    }

    w_rook[0]->sprite.setPosition(coord_x[0], coord_y[7]);
    w_rook[1]->sprite.setPosition(coord_x[7], coord_y[7]);
    b_rook[0]->sprite.setPosition(coord_x[0], coord_y[0]);
    b_rook[1]->sprite.setPosition(coord_x[7], coord_y[0]);

    w_king->sprite.setPosition(coord_x[4], coord_y[7]);
    b_king->sprite.setPosition(coord_x[4], coord_y[0]);

    w_queen->sprite.setPosition(coord_x[3], coord_y[7]);
    b_queen->sprite.setPosition(coord_x[3], coord_y[0]);

    w_bishop[0]->sprite.setPosition(coord_x[2], coord_y[7]);
    w_bishop[1]->sprite.setPosition(coord_x[5], coord_y[7]);
    b_bishop[0]->sprite.setPosition(coord_x[2], coord_y[0]);
    b_bishop[1]->sprite.setPosition(coord_x[5], coord_y[0]);

    w_knight[0]->sprite.setPosition(coord_x[1], coord_y[7]);
    w_knight[1]->sprite.setPosition(coord_x[6], coord_y[7]);
    b_knight[0]->sprite.setPosition(coord_x[1], coord_y[0]);
    b_knight[1]->sprite.setPosition(coord_x[6], coord_y[0]);

    for (int i=0; i<8; i++)
    {
        w_pawn[i]->sprite.setPosition(coord_x[i], coord_y[6]);
        b_pawn[i]->sprite.setPosition(coord_x[i], coord_y[1]);
    }
}

// CHECK COLLISION
bool collision()
{
    int enemy_collision = 0;
    for (int i=0; i<16; i++)
    {
        if (!turn) //WHITE TURN
        {
            if (white_piece[i]->sprite.getPosition().x == place_posX && white_piece[i]->sprite.getPosition().y == place_posY)
                return 1; //COLLISION WITH SAME PIECE

            // if (white_piece[i]->enemy_collision(selected_piece, select_posX, select_posY, place_posX, place_posY, black_piece, white_piece) == 1)
            if (white_piece[selected_piece]->enemy_collision(selected_piece, select_posX, select_posY, place_posX, place_posY, black_piece, white_piece) == true)
            {  

                    return 1; //CHECK TO NOT SKIP OVER A PIECE
            }
        }

        else //BLACK TURN
        {
            if (black_piece[i]->sprite.getPosition().x == place_posX && black_piece[i]->sprite.getPosition().y == place_posY)
                return 1;

            if (white_piece[selected_piece]->enemy_collision(selected_piece, select_posX, select_posY, place_posX, place_posY, white_piece, black_piece) == 1)
            {   
                return 1;
            }
        }
    }

    return 0;
}

// bool find_check()
// {
//     for (int i=0; i<16; i++)
//     {
        
//         if (i == 4)
//             continue;

//         if (!turn)
//         {
//             if (!white_piece[i]->enemy_collision(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y, black_piece, white_piece) 
//             &&  (white_piece[i]->legal_move(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y)))
//             {
//                 cout<<"black check";
//                 check_black = 1;
//                 return check_black; 
//             }

//             if (!black_piece[i]->enemy_collision(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y, white_piece, black_piece)
//             &&  (black_piece[i]->legal_move(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y)))
//             {  
//                 cout<<"white check";
//                 check_white = 1;
//                 return check_white;
//             }
//         }

//         else
//         {
//             if (!black_piece[i]->enemy_collision(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y, white_piece, black_piece)
//             &&  (black_piece[i]->legal_move(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y)))
//             {  
//                 cout<<"white check";
//                 check_white = 1;
//                 return check_white;
//             }

//             if (!white_piece[i]->enemy_collision(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y, black_piece, white_piece) 
//             &&  (white_piece[i]->legal_move(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y)))
//             {
//                 cout<<"black check";
//                 check_black = 1;
//                 return check_black;
//             }
//         }
//     }
//     check_white = 0;
//     check_black = 0;
//     return 0;
// }


bool find_check()
{
    check_white = 0;
    check_black = 0;

    for (int i=0; i<16; i++)
    {
        // if (i == 4)
        //     continue;
        
        //if (!turn)
        {
            
            if (white_piece[i]->flag_alive == 0)
                continue;

            if (!white_piece[i]->enemy_collision(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y, black_piece, white_piece) 
            &&  (white_piece[i]->legal_move(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y)))
            {
                cout<<"black check";
                check_black = 1;
                check_white = 0;
                return check_black; 
            }
        }

       // else
        {
            if (black_piece[i]->flag_alive == 0)
                continue;

            if (!black_piece[i]->enemy_collision(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y, white_piece, black_piece)
            &&  (black_piece[i]->legal_move(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y)))
            {  
                cout<<"white check";
                check_white = 1;
                check_black = 0;
                return check_white;
            }
        }
    }

    return 0;
}

// bool find_check()
// {
//     check_white = 0;
//     check_black = 0;

//     for (int i=0; i<16; i++)
//     {
//         if (i == 4)
//             continue;

//         if (white_piece[i]->legal_move(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y))
//         {  
//             if (!white_piece[i]->enemy_collision(selected_piece, white_piece[i]->sprite.getPosition().x, white_piece[i]->sprite.getPosition().y, b_king->sprite.getPosition().x, b_king->sprite.getPosition().y, black_piece, white_piece))
//             {
//                 cout<<"black check";
//                 check_black = 1;
//                 check_white = 0;
//                 return check_black; 
//             }
//         }
//         if (black_piece[i]->legal_move(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y))
//         {
//             if (!black_piece[i]->enemy_collision(selected_piece, black_piece[i]->sprite.getPosition().x, black_piece[i]->sprite.getPosition().y, w_king->sprite.getPosition().x, w_king->sprite.getPosition().y, white_piece, black_piece))
//             {  
//                 cout<<"white check";
//                 check_white = 1;
//                 check_black = 0;
//                 return check_white;
//             }
//         }
//     }

//     return 0;
// }

// bool check_mate()
// {
//     final_check = 1;

//     for (int i=0; i<16; i++)
//     {
//         if (white_piece[i]->flag_alive == 0)
//             continue;
        
//         if (black_piece[i]->flag_alive == 0)
//             continue;
        
//         for (int y=0; y<8; y++)
//         {

//             for (int x=0; x<8; x++)
//             {

//                 //if (!turn)
//                 {
//                     int orig_posX = white_piece[i]->sprite.getPosition().x; 
//                     int orig_posY = white_piece[i]->sprite.getPosition().y;

//                     if ((white_piece[i]->legal_move(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y]))
//                      && (!white_piece[i]->enemy_collision(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y], black_piece, white_piece)))
//                     {
//                         white_piece[i]->sprite.setPosition(coord_x[x], coord_y[y]);
//                         find_check();
//                         if (check_white)
//                         {
//                             white_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                         }

//                         else
//                         {
//                             white_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                             final_check = 0;
//                             cout<<final_check;
//                             break;
//                             //return final_check;
//                         }
//                     }
//                 }

//                 //else if (turn)
//                 {
//                     int orig_posX = black_piece[i]->sprite.getPosition().x; 
//                     int orig_posY = black_piece[i]->sprite.getPosition().y;

//                     if ((black_piece[i]->legal_move(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y])) 
//                     && (!black_piece[i]->enemy_collision(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y], white_piece, black_piece))) 
                    
//                     {
//                         black_piece[i]->sprite.setPosition(coord_x[x], coord_y[y]);
//                         find_check();
//                         if (check_black)
//                         {
//                             black_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                         }

//                         else
//                         {
//                             black_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                             final_check = 0;
//                             break;
//                            // return final_check;
//                         }
//                     }
//                 }
                
//             }
//         }
//     }
//     cout<<final_check;
//     return final_check;
// }

// bool check_mate()
// {
//     final_check = 1;

//     for (int i=0; i<16; i++)
//     {
//         for (int y=0; y<8; y++)
//         {

//             for (int x=0; x<8; x++)
//             {

//                 if (turn)
//                 {

//                     cout<<"CHECKING FOR BLACK PIECE";
//                     if (white_piece[i]->flag_alive == 0)
//                         continue;

//                     if (i == 4)
//                         continue;

//                     int orig_posX = white_piece[i]->sprite.getPosition().x; 
//                     int orig_posY = white_piece[i]->sprite.getPosition().y;

//                     if (white_piece[i]->legal_move(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y]))
//                     {
//                         if (!white_piece[i]->enemy_collision(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y], black_piece, white_piece))
//                         {
//                             white_piece[i]->sprite.setPosition(coord_x[x], coord_y[y]);
//                             find_check();
//                             if (check_white)
//                             {
//                                 white_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                                 cout<<" HELLO ";
//                             }

//                             else
//                             {
//                                 if (i==4)
//                                 {
//                                     if (white_piece[i]->capture_piece_white(black_piece, coord_x[x], coord_y[y]))
//                                     {
//                                         cout<<">>>>?????";
//                                         find_check();
//                                         if (check_white);
//                                         continue;
//                                     }
//                                     cout<<"PLS KING";
//                                     find_check();
//                                     if (check_white)
//                                         continue;
//                                 }
//                                 white_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                                 final_check = 0;
//                                 cout<<"BINGO WHITE";
//                                 cout<<final_check;
//                                 return final_check;
//                             }
//                         }
//                     }
//                 }

//                 else if (!turn)
//                 {
//                     cout<<"WHITE CHECKING";
//                     if (black_piece[i]->flag_alive == 0)
//                         continue;

//                     int orig_posX = black_piece[i]->sprite.getPosition().x; 
//                     int orig_posY = black_piece[i]->sprite.getPosition().y;

//                     if (black_piece[i]->legal_move(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y]))
//                     {
//                         if (!black_piece[i]->enemy_collision(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y], white_piece, black_piece))
//                         {
//                             black_piece[i]->sprite.setPosition(coord_x[x], coord_y[y]);
//                             find_check();
//                             if (check_black)
//                             {
//                                 black_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                                 cout<< "HELLO BLACK PIECE";
//                             }

//                             else
//                             {

//                                 black_piece[i]->sprite.setPosition(orig_posX, orig_posY);
//                                 final_check = 0;
//                                 cout<<"BINGO PLS WORK";
//                                 return final_check;
//                             }
//                         }
//                     }
//                 }
                
//             }
//         }
//     }
//     cout<<final_check;
//     return final_check;
// }

bool check_mate()
{
    final_check = true;

    for (int i = 0; i < 16; i++)
    {
        if (i == 4)
            continue;

        if (i==0 || i==1 || i == 2 || i == 7 || i == 8 || i == 9 || i==10 || i == 14 || i == 15 || i == 3)
            continue;

        Pieces<T1, T2> *piece = turn ? white_piece[i] : black_piece[i];
        int orig_posX = piece->sprite.getPosition().x;
        int orig_posY = piece->sprite.getPosition().y;

        for (int y = 0; y < 8; y++)
        {
            if (y > 2 || y < 5)
                continue;

            for (int x = 0; x < 8; x++)
            {
                if (x <= 3 || x > 6)
                    continue;

                int test_count = 0;

                if (piece->legal_move(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y]))
                {
                    cout<<"WHAT";
                    if (!piece->enemy_collision(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y], turn ? black_piece : white_piece, turn ? white_piece : black_piece))
                    {
                        cout<<"BAINGAN";
                        // Simulate the move
                        piece->sprite.setPosition(B_SIZE * x + CENTRE, B_SIZE * y + CENTRE);
                        find_check();

                        if (!turn && !check_white && check_black)
                        {
                            piece->sprite.setPosition(orig_posX, orig_posY);
                            cout<<test_count++;
                            cout<<"NUMBER";
                        }
                        else if (turn && !check_black && check_white)
                        {
                            cout<<"WHAT ARE YOU DOING HERE";
                            piece->sprite.setPosition(orig_posX, orig_posY);
                        }
                        else
                        {
                            cout<<"NO MATE";
                            piece->sprite.setPosition(orig_posX, orig_posY);
                            final_check = false;
                            cout<<"NO CHECKMATE";
                            cout << final_check;
                            return final_check;
                        }
                    }
                }
            }
        }
    }

    //cout << final_check;
    return final_check;
}

// bool check_mate()
// {
//     final_check = true;

//     for (int i = 4; i <= 4; i++)
//     {
//         // if (i == 4)
//         //     continue;

//         Pieces<T1, T2> *piece = turn ? white_piece[i] : black_piece[i];
//         int orig_posX = piece->sprite.getPosition().x;
//         int orig_posY = piece->sprite.getPosition().y;

//         for (int y = 0; y < 8; y++)
//         {
//             for (int x = 0; x < 8; x++)
//             {
//                 int test_count = 0;

//                 if (piece->legal_move(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y]))
//                 {
//                     cout<<"WHAT";
//                     if (!piece->enemy_collision(selected_piece, orig_posX, orig_posY, coord_x[x], coord_y[y], turn ? black_piece : white_piece, turn ? white_piece : black_piece))
//                     {
//                         cout<<"BAINGAN";
//                         // Simulate the move
//                         piece->sprite.setPosition(B_SIZE * x + CENTRE, B_SIZE * y + CENTRE);
//                         find_check();



//                         if (!turn && !check_white && check_black && !piece->capture_piece_black(white_piece, place_posX, place_posY))
//                         {
//                             //if (piece->capture_piece_black)
//                             piece->sprite.setPosition(orig_posX, orig_posY);
//                             cout<<test_count++;
//                             cout<<"NUMBER";
//                         }
//                         else if (turn && !check_black && check_white && !piece->capture_piece_white(black_piece, place_posX, place_posY))
//                         {
//                             cout<<"WHAT ARE YOU DOING HERE";
                            
//                             piece->sprite.setPosition(orig_posX, orig_posY);
//                         }
//                         else
//                         {
//                             cout<<"NO MATE";
//                             piece->sprite.setPosition(orig_posX, orig_posY);
//                             final_check = false;
//                             cout<<"NO CHECKMATE";
//                             cout << final_check;
//                             return final_check;
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     //cout << final_check;
//     return final_check;
// }

// void short_castle()
// {
//     if (!turn)
//     {
//         w_king->sprite.setPosition(select_posX + 64*2, select_posY);
//         w_rook[1]->sprite.setPosition(select_posX + 62, select_posY);
//     }

//     else
//     {
//         b_king->sprite.setPosition(select_posX + 64*2, select_posY);
//         b_rook[1]->sprite.setPosition(select_posX + 62, select_posY);
//     }
// }

// CHECK VALID MOVES
bool valid_move()
{
    if (collision())
    {
        return 0;
    }

    
    if (!turn) // WHITE TURN
    {

     

        if (!white_piece[selected_piece]->legal_move(selected_piece, select_posX, select_posY, place_posX, place_posY))
            return 0;
    }

    else // BLACK TURN
    {

        

        if (!black_piece[selected_piece]->legal_move(selected_piece, select_posX, select_posY, place_posX, place_posY))
            return 0;

    }

    return 1;
}

// SELECT PIECE
void select_piece(int posX, int posY, RenderWindow& window)
{
    select_posX = -1;
    select_posY = -1;

    for (int i=0; i<8; i++)
    {
        if (posY >= (i)*B_SIZE + offset_y && posY < (i+1)*B_SIZE + offset_y)
            select_posY = b_squares[i][0].getPosition().y + CENTRE;

        if (posX >= (i)*B_SIZE +offset_x && posX < (i+1)*B_SIZE+offset_x)
            select_posX = b_squares[0][i].getPosition().x + CENTRE;
    }

    if (!turn)
    {
        for (int i=0; i<16; i++)
        {
            if (white_piece[i]->sprite.getPosition().x == select_posX && white_piece[i]->sprite.getPosition().y == select_posY)
            {
                selected_piece = i;
                selected = 1;
                whitepieceselect.stop();
                whitepieceselect.play();
            //    cout<<"YET";
                break;
            }
        }
    } 

    else
    {
        for (int i=0; i<16; i++)
        {
            if (black_piece[i]->sprite.getPosition().x == select_posX && black_piece[i]->sprite.getPosition().y == select_posY)
            {
                selected_piece = i;
                selected = 1;
              //  cout << "HEHEHHEHEHEHE";
                blackpieceselect.stop();
                blackpieceselect.play();
                break;
            }
        }
    }

    //cout<<"YEET";
}


// MOVE PIECE
void move_piece(int posX, int posY, RenderWindow& window, Event& e)
{
    int track = -1;
    bool capture = 0;

    for (int i=0; i<8; i++)
    {
        if (posY >= i*B_SIZE + offset_y && posY < (i+1)*B_SIZE +offset_y)
            place_posY = b_squares[i][0].getPosition().y + CENTRE;

        if (posX >= i*B_SIZE+offset_x && posX < (i+1)*B_SIZE+offset_x)
            place_posX = b_squares[0][i].getPosition().x + CENTRE;
        
    }

    if (valid_move())
    {   
        whitepieceselect.stop();
        whitepieceselect.play();
        if (!turn)
        {
            white_piece[selected_piece]->sprite.setPosition(place_posX, place_posY);

            for (int i=0; i<16; i++)
            {
                if (black_piece[i]->sprite.getPosition().x == place_posX && black_piece[i]->sprite.getPosition().y == place_posY)
                    track = i;
            }

            if (white_piece[selected_piece]->capture_piece_white(black_piece, place_posX, place_posY))
                capture = 1;


            for (int i=0; i<8; i++)
            {
                if (selected_piece >= 8)
                {
                    check_upgrade_white(e);
                }
            }

            find_check();
            if (check_white)
            {
                white_piece[selected_piece]->sprite.setPosition(select_posX, select_posY);
                if (capture == 1)
                {
                    black_piece[track]->sprite.setPosition(place_posX, place_posY);
                    black_piece[track]->sprite.setScale(0.95, 0.95);
                    black_piece[track]->flag_alive = 1;   
                }
                cout<<"yay2";
                //cout << "Checkmate white";
                return;
            }

            if (check_black)
            {
                //cout << "Check! You can't move there." << endl;
                check_mate();
                if (final_check)
                {
                    cout<<"Checkmate black";
                   window.close();
                   m->gameover();
                }
            }

                
        }

            // if (white_piece[selected_piece]->sprite.getPosition().x == place_posX && white_piece[selected_piece]->sprite.getPosition().y == place_posY)
            //     white_piece[selected_piece]->capture_piece(black_piece, place_posX, place_posY);    // CHECK AND UPDATE IF CAPTURED
            
        
        else
        {
            black_piece[selected_piece]->sprite.setPosition(place_posX, place_posY); 

            for (int i=0; i<16; i++)
            {
                if (white_piece[i]->sprite.getPosition().x == place_posX && white_piece[i]->sprite.getPosition().y == place_posY)
                    track = i;
            }

            if (black_piece[selected_piece]->capture_piece_black(white_piece, place_posX, place_posY))
                capture = 1;

            for (int i=0; i<8; i++)
            {
                if (selected_piece >= 8)
                {
                    check_upgrade_black(e);
                }
            }

            find_check(); 
            if (check_black)
            {
                black_piece[selected_piece]->sprite.setPosition(select_posX, select_posY);
                if (capture == 1)
                {
                    white_piece[track]->sprite.setPosition(place_posX, place_posY);
                    white_piece[track]->sprite.setScale(0.95, 0.95);
                    white_piece[track]->flag_alive = 1;
                }
                cout<<"yay2";
                return; 
            }

            if (check_white)
            {
                cout<<"pls";
                check_mate();
                if (final_check)
                {
                    cout<<"Checkmate White";
                    cout<<"Close will you";
                    window.close();
                    m->gameover();
                }
            }
                
                   
        

            // if (black_piece[selected_piece]->sprite.getPosition().x == place_posX && black_piece[selected_piece]->sprite.getPosition().y == place_posY)
            //     black_piece[selected_piece]->capture_piece(white_piece, place_posX, place_posY);
              
        }

        //cout<<"NOOO";
        turn = !turn;
    }
    else {
        invalidmusic.stop();
        invalidmusic.play();
    }
    selected = 0;
}

void check_upgrade_white(Event& e)
{
    float tempPos_x = white_piece[selected_piece]->sprite.getPosition().x;
    float tempPos_y = white_piece[selected_piece]->sprite.getPosition().y;
    float temp_select = selected_piece;

        if (white_piece[selected_piece]->sprite.getPosition().y == coord_y[0] && !white_piece[selected_piece]->upgrade_flag)
        {
            white_piece[selected_piece];
            //std::shared_ptr<Pieces> temp_piece;
            Pieces<T1, T2>* temp_piece;
            // if (e.key.code == sf::Keyboard::Num1)
           // temp_piece = std::make_shared<W_Queen>("images/Peices/Queen W.png");
            temp_piece = new W_Queen<T1, T2>("images/Peices/Queen W.png");
            // if (e.key.code == sf::Keyboard::Num2)
            //     temp_piece = new W_Queen("images/Peices/Rook W.png");

            // if (e.key.code == sf::Keyboard::Num3)
            //     temp_piece = new W_Queen("images/Peices/Bishop W.png");

            // if (e.key.code == sf::Keyboard::Num4)
            //     temp_piece = new W_Queen("images/Peices/Knight W.png");

            //white_piece[selected_piece] = std::move(temp_piece);
            white_piece[selected_piece] = temp_piece;
            white_piece[selected_piece]->upgrade_flag = 1;
            white_piece[selected_piece]->sprite.setPosition(tempPos_x, tempPos_y);
        }
}

void check_upgrade_black(Event& e)
{
    float tempPos_x = black_piece[selected_piece]->sprite.getPosition().x;
    float tempPos_y = black_piece[selected_piece]->sprite.getPosition().y;
    float temp_select = selected_piece;

        if (black_piece[selected_piece]->sprite.getPosition().y == coord_y[7] && !black_piece[selected_piece]->upgrade_flag)
        {
            black_piece[selected_piece];
            Pieces<T1, T2>* temp_piece;
            // if (e.key.code == sf::Keyboard::Num1)
                //temp_piece = make_shared<B_Queen>("images/Peices/Queen B.png");
                temp_piece = new B_Queen<T1, T2>("images/Peices/Queen B.png");
 
            // if (e.key.code == sf::Keyboard::Num2)
            //     temp_piece = new W_Queen("images/Peices/Rook W.png");

            // if (e.key.code == sf::Keyboard::Num3)
            //     temp_piece = new W_Queen("images/Peices/Bishop W.png");

            // if (e.key.code == sf::Keyboard::Num4)
            //     temp_piece = new W_Queen("images/Peices/Knight W.png");

            black_piece[selected_piece] = temp_piece;
            black_piece[selected_piece]->upgrade_flag = 1;
            black_piece[selected_piece]->sprite.setPosition(tempPos_x, tempPos_y);
        }
}

/////////////////////// GAME FUNCTION ////////////////////////////////////////////////
int  start_game()
{   
    if(m->getMusicFlag())
    bg_music.play();

    srand(time(0));
    RenderWindow window(VideoMode(1280, 720), title);
    Clock clock;
    float timer=0;
    

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time; 
    
//////////////////////////////// START EVENT ////////////////////////////////////////
        Event e;
            while (window.pollEvent(e))
            {  
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    exit(1);
                    //window.close(); //close the game      

                if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    std::cout << "x : " << mousePos.x << " " << "|| y : " << mousePos.y << std::endl;
                    if (mousePos.x >= 8 && mousePos.x <= 83 && mousePos.y >= 8 && mousePos.y <= 85)
                    {
                        std::cout << "Home";
                        return 999;         // Means go to menu back 

                    }
                    if (mousePos.x >= 1199 && mousePos.x <= 1263 && mousePos.y >= 8 && mousePos.y <= 85)
                    {
                        std::cout << "exit from game";
                        return 111;         // Means go to Exit back 

                    }
                }



                
                if(e.type == sf::Event::MouseButtonPressed)
                {
                    if(e.mouseButton.button == sf::Mouse::Left)
                    {       
                        int click_posX = e.mouseButton.x;
                        int click_posY = e.mouseButton.y;

                        if (!selected)                            
                            select_piece(click_posX, click_posY, window);

                        else
                        {
                            move_piece(click_posX, click_posY, window, e);
                        }
                    }


                }               	    
            }

////////////////////// CALL FUNCTIONS ////////////////////////////////////////////////
        draw_board(window);
        static bool start1 = 1;
        if (start1 == 1)
        {
            set_positions();
            start1 = 0;
        }

        // if (check_black || check_white)
        // {
        //     check_mate();
        //     if (final_check)
        //     {
        //         cout<<"Checkmate";
        //         //window.close();
        //         m->gameover();
        //     }
        // }



////////////////////// DRAW EVERYTHING ///////////////////////////////////////////////
        window.clear(Color::Black); //clears the screen
        window.draw(background);  // setting background

      

        for (int i=0; i<16; i++)
        {
            window.draw(white_piece[i]->sprite);
            window.draw(black_piece[i]->sprite);

        }

        window.display();  //Displying all the sprites
    }
}

~Game()
{
    // delete m;
    // delete b_king;
    // delete w_king;
    // delete b_queen;
    // delete w_queen;

    // for (int i=0; i<2; i++)
    // {
    //     delete w_rook[i];
    //     delete b_rook[i];
    //     delete w_bishop[i];
    //     delete b_bishop[i];
    //     delete w_knight[i];
    //     delete b_knight[i];
    // }

    // for (int i=0; i<8; i++)
    // {
    //     delete w_pawn[i];
    //     delete b_pawn[i];
    // }

    // for (int i=0; i<16; i++)
    // {
    //     delete white_piece[i];
    //     delete black_piece[i];
    // }
}
};