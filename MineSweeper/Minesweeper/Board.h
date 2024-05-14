//
// Created by Alex Chase on 12/3/20.
//
#pragma once
#include <vector>
#include <string>
#include "Random.h"
using namespace std;

class Board {
    int height;
    int width;
    int numMine;
public:
    struct Tile{
        // Tiles contain whether the tile is a bomb, was revealed, and a list of adjacent tiles
        bool mine;
        bool reveal;
        bool flagged;
        int numMines;
    };
    vector<vector<Tile>> rows;
    Board();
    Board(int& _h, int& _w, int& _m);
    //General Functions
    void randBoard(int& num);
    int generateTiles(string& nums, int& index);
    void checkTiles();
    bool revealTile(int& i, int& j);
    bool flagTile(int& i, int& j);
    void clearBoard();
    //Accessors

};



