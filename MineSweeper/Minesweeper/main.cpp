#include <SFML/Graphics.hpp>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureManger.h"
#include "Board.h"
using namespace std;

void readConfig(int& x, int& y, int& z){
    //Read in as Rows, Columns, and # of Mines
    ifstream inFile("boards/config.cfg");
    string _x, _y, _z;

    getline(inFile, _x);
    getline(inFile, _y);
    getline(inFile, _z);
    x = stoi(_x);
    y = stoi(_y);
    z = stoi(_z);

    inFile.close();
}
int readBoard(Board& board, string filepath){
    int count = 0;
    int mines = 0;

    ifstream inFile(filepath);
    string heading;

    while(getline(inFile, heading)) {
        //Create stream buffer and variable placeholders
        istringstream stream(heading);
        string row;

        getline(stream, row);
        mines += board.generateTiles(row, count);
        count++;
    }
    inFile.close();
    return mines;
}
int main()
{
    //Variables and Containers
    int c, r, _nm;
    int numFlags = 0;
    int min = 0;
    int count = 0;
    bool win = false;
    bool lose = false;
    bool debug_mode = false;
    bool check = true;
    string path;
    //========================INITIALIZATION===============================================================
    //Read Config file and intialize board
    readConfig(c,r,_nm);
    Board board(r,c,_nm);
    board.randBoard(_nm);
    //Generate Textures
    sf::RenderWindow window(sf::VideoMode((c*32), ((r*32)+88)), "MineSweeper by Alex Chase: glhf lol");
    sf::Sprite TH(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite TR(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite N1(TextureManager::GetTexture("number_1"));
    sf::Sprite N2(TextureManager::GetTexture("number_2"));
    sf::Sprite N3(TextureManager::GetTexture("number_3"));
    sf::Sprite N4(TextureManager::GetTexture("number_4"));
    sf::Sprite N5(TextureManager::GetTexture("number_5"));
    sf::Sprite N6(TextureManager::GetTexture("number_6"));
    sf::Sprite N7(TextureManager::GetTexture("number_7"));
    sf::Sprite N8(TextureManager::GetTexture("number_8"));
    sf::Sprite T1(TextureManager::GetTexture("test_1"));
    sf::Sprite T2(TextureManager::GetTexture("test_2"));
    sf::Sprite T3(TextureManager::GetTexture("test_3"));
    sf::Sprite Debug(TextureManager::GetTexture("debug"));
    sf::Sprite FH(TextureManager::GetTexture("face_happy"));
    sf::Sprite FL(TextureManager::GetTexture("face_lose"));
    sf::Sprite FW(TextureManager::GetTexture("face_win"));
    sf::Sprite Digits(TextureManager::GetTexture("digits"));

    //=======================BEGIN_PROGRAM=================================================================
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mx = event.mouseButton.x;
                    int my = event.mouseButton.y;
                    //If in range of tiles
                    if(!win && !lose) {
                        if ((my / 32) < r) {
                            mx = mx / 32;
                            my = my / 32;
                            check = board.revealTile(my, mx);
                            count = 0;
                            if (!check) {
                                //This initiates losing
                                lose = true;
                                window.setTitle("BOOM! Game Over... :(");
                            }
                        }
                    }
                    //If in range of buttons
                    if((my >= (r * 32)) && (my < (r*32) + 64)){
                        //If reset button
                        int ref = (c*32)/2;
                        if(mx >= (ref - 32) && mx < (ref + 32)){
                            lose = false;
                            win = false;
                            window.setTitle("MineSweeper by Alex Chase: glhf lol");
                            readConfig(c,r,_nm);
                            board.randBoard(_nm);
                        }
                        //If other (check lose / win to prevent interaction)
                        if(!win && !lose) {
                            if (mx >= ref + (32 * 3) && mx < ref + (32 * 5)) {
                                //Debug
                                if (debug_mode) {
                                    debug_mode = false;
                                } else {
                                    debug_mode = true;
                                }
                            }
                        }
                            if(mx >= ref +(32 * 5) && mx < ref + (32 * 7)){
                                //Test1
                                lose = false;
                                win = false;
                                window.setTitle("MineSweeper by Alex Chase: glhf lol");
                                board.clearBoard();
                                path = "boards/testboard1.brd";
                                _nm = readBoard(board, path);
                                board.checkTiles();
                            }
                            if(mx >= ref +(32 * 7) && mx < ref + (32 * 9)){
                                //Test2
                                lose = false;
                                win = false;
                                window.setTitle("MineSweeper by Alex Chase: glhf lol");
                                board.clearBoard();
                                path = "boards/testboard2.brd";
                                _nm = readBoard(board, path);
                                board.checkTiles();
                            }
                            if(mx >= ref +(32 * 9) && mx < ref + (32 * 11)){
                                //Test3
                                lose = false;
                                win = false;
                                window.setTitle("MineSweeper by Alex Chase: glhf lol");
                                board.clearBoard();
                                path = "boards/testboard3.brd";
                                _nm = readBoard(board, path);
                                board.checkTiles();
                            }

                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if(!win && !lose) {
                        int mx = event.mouseButton.x;
                        int my = event.mouseButton.y;
                        if ((my / 32) < r) {
                            mx = mx / 32;
                            my = my / 32;
                            bool check_flag = board.flagTile(my, mx);
                            if(check_flag){
                                numFlags++;
                            }
                            else{
                                numFlags--;
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        //Start DrawBoard======================================================
        //Print tiles in order
        //If tile is revealed print background and number if necessary
        //If hidden print hidden, mine if necessary (debug) , and flag if necessary (flagged)
        count = 0;
        for(unsigned int i = 0; i < board.rows.size(); i++){
            for(unsigned int j = 0; j < board.rows.at(i).size(); j++){
                Board::Tile temp = board.rows.at(i).at(j);
                if(lose && temp.mine){
                    temp.reveal = true;
                }
                    if (temp.reveal) {
                        count++;
                        TR.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                        window.draw(TR);
                        if (!temp.mine) {
                            int x = temp.numMines;
                            switch (x) {
                                case 1:
                                    N1.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N1);
                                    break;
                                case 2:
                                    N2.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N2);
                                    break;
                                case 3:
                                    N3.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N3);
                                    break;
                                case 4:
                                    N4.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N4);
                                    break;
                                case 5:
                                    N5.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N5);
                                    break;
                                case 6:
                                    N6.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N6);
                                    break;
                                case 7:
                                    N7.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N7);
                                    break;
                                case 8:
                                    N8.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                                    window.draw(N8);
                                    break;
                            }
                        } else {
                            mine.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                            window.draw(mine);
                        }
                    } else {
                        TH.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                        window.draw(TH);
                        if (temp.flagged) {
                            flag.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                            window.draw(flag);
                        }
                    }
                if(debug_mode && temp.mine){
                    mine.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                    window.draw(mine);
                }
                //Win Condition Check
                if(count == ((r * c) - _nm)){
                    win = true;
                    window.setTitle("OMG your toats AMAZING!");
                    //Set Center button to Cool face
                }
                if(win && !temp.reveal){
                    flag.setPosition(sf::Vector2f(32.f * j, 32.f * i));
                    window.draw(flag);
                }
            }
        }
        //Print the flag counter. write as if(negative){} count++ position, then print digit and count++ for position
        int ref;
        if(win){
            ref = 0;
        }
        else{
            ref = _nm - numFlags;
        }

        int digit = 0;
        if(ref < 0){
            digit = 10;
            Digits.setTextureRect(sf::IntRect(21*digit,0,21,32));
            Digits.setPosition(sf::Vector2f(0.f,r * 32.f));
            window.draw(Digits);
            ref *= -1;
        }
        //Hundreds place
        digit = ref/100;
        ref = ref%100;
        Digits.setTextureRect(sf::IntRect(21*digit,0,21,32));
        Digits.setPosition(sf::Vector2f(32.f,r * 32.f));
        window.draw(Digits);
        //Tens Place
        digit = ref/10;
        Digits.setTextureRect(sf::IntRect(21*digit,0,21,32));
        Digits.setPosition(sf::Vector2f(64.f,r * 32.f));
        window.draw(Digits);
        //Ones PLace
        digit = ref%10;
        Digits.setTextureRect(sf::IntRect(21*digit,0,21,32));
        Digits.setPosition(sf::Vector2f(96.f,r * 32.f));
        window.draw(Digits);
        //Print Reset button w/ appropriate face, use checkWin() to change win bool
        float mid = (float)(c*32)/2;
        if(lose){
            FL.setPosition(sf::Vector2f(mid - 32.f,r * 32.f));
            window.draw(FL);
        }
        else if(win){
            FW.setPosition(sf::Vector2f(mid - 32.f,r * 32.f));
            window.draw(FW);
        }
        else{
            FH.setPosition(sf::Vector2f(mid - 32.f,r * 32.f));
            window.draw(FH);
        }
        //Print the test/ debug buttons
        Debug.setPosition(sf::Vector2f(mid +(32.f * 3),r * 32.f));
        window.draw(Debug);
        T1.setPosition(sf::Vector2f(mid +(32.f * 5),r * 32.f));
        window.draw(T1);
        T2.setPosition(sf::Vector2f(mid +(32.f * 7),r * 32.f));
        window.draw(T2);
        T3.setPosition(sf::Vector2f(mid +(32.f * 9),r * 32.f));
        window.draw(T3);
        //End DrawBoard========================================================
        window.display();
        count = 0;
    }
    //Clear data before exiting!
    TextureManager::Clear();
    return 0;
}
