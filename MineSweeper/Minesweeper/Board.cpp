//
// Created by Alex Chase on 12/3/20.
//

#include "Board.h"
#include <iostream>
using namespace std;

//Constructors===================================================
Board::Board(){
    this->width = 0;
    this->height = 0;
    this->numMine = 0;
}
Board::Board(int& _h, int& _w, int& _m){
    this->width = _w;
    this->height = _h;
    this->numMine = _m;
}
//General Functions==============================================
void Board::randBoard(int& num) {
    clearBoard();
    this->numMine = num;
    for(unsigned int i =  0; i < this->height; i++){
        vector<Tile> row;
        for(unsigned int j = 0; j < this->width; j++){
            Tile newTile;
            newTile.mine = false;
            newTile.flagged = false;
            newTile.numMines = false;
            newTile.reveal = false;

            row.push_back(newTile);
        }
        this->rows.push_back(row);
    }
    for(unsigned int i = 0; i < numMine; i++){
        int x = Random::Number(0, rows.at(0).size()-1);
        int y = Random::Number(0,rows.size()-1);
        if(x < rows.at(0).size() && y < rows.size()) {
            if (!rows.at(y).at(x).mine) {
                rows.at(y).at(x).mine = true;
            } else {
                i--;
            }
        }
    }
    checkTiles();
}
int Board::generateTiles(string& nums, int& index){
    //Reads in Values given into vectors, first clear data
    vector<Tile> row;
    int mines = 0;
    for(unsigned int i = 0; i < nums.size(); i++){
        char m = nums.at(i);
        if(m == '1' || m == '0') {
            Tile newTile;
            if (m == '0') {
                newTile.mine = false;
            }
            if (m == '1') {
                newTile.mine = true;
                mines++;
            }
            newTile.reveal = false;
            newTile.flagged = false;
            newTile.numMines = 0;
            row.push_back(newTile);
        }
    }
    this->rows.push_back(row);
    this->numMine = mines;
    return mines;
}
void Board::checkTiles() {

    for(unsigned int i = 0; i < rows.size(); i++){
        for(unsigned int j = 0; j < rows.at(i).size(); j++){
            Tile temp = this->rows.at(i).at(j);
            int count = 0;
            //Check each space around the tile individually
                if (i > 0 && j > 0) {
                    bool tempo = this->rows.at(i - 1).at(j - 1).mine;
                    if (tempo)
                        count++;
                }
                if (i > 0) {
                    bool tempo = this->rows.at(i - 1).at(j).mine;
                    if (tempo)
                        count++;
                }
                if (j > 0) {
                    bool tempo = this->rows.at(i).at(j - 1).mine;
                    if (tempo)
                        count++;
                }
                if (i < (rows.size() - 1) && j > 0) {
                    bool tempo = this->rows.at(i + 1).at(j - 1).mine;
                    if (tempo)
                        count++;
                }
                if (i > 0 && j < (rows.at(i).size() - 1)) {
                    bool tempo = this->rows.at(i - 1).at(j + 1).mine;
                    if (tempo)
                        count++;
                }
                if (i < (rows.size() - 1)) {
                    bool tempo = this->rows.at(i + 1).at(j).mine;
                    if (tempo)
                        count++;
                }
                if (j < (rows.at(i).size() - 1)) {
                    bool tempo = this->rows.at(i).at(j + 1).mine;
                    if (tempo)
                        count++;
                }
                if (i < (rows.size() - 1) && j < (rows.at(i).size() - 1)) {
                    bool tempo = this->rows.at(i + 1).at(j + 1).mine;
                    if (tempo)
                        count++;
                }
            this->rows.at(i).at(j).numMines = count;
        }
    }
}
bool Board::revealTile(int& i, int& j) {

    if((i < rows.size())) {

        if(j < rows.at(i).size()) {

            Tile temp = this->rows.at(i).at(j);
            if (!temp.flagged) {
                if(!temp.reveal) {
                    if(!temp.mine) {
                        if (temp.numMines != 0) {
                            this->rows.at(i).at(j).reveal = true;
                            return true;
                        } else {
                            this->rows.at(i).at(j).reveal = true;
                            //Check each space around the tile individually
                            if (i > 0 && j > 0) {
                                int x = i - 1;
                                int y = j - 1;
                                revealTile(x, y);
                            }
                            if (i > 0) {
                                int x = i - 1;
                                int y = j;
                                revealTile(x, y);
                            }
                            if (j > 0) {
                                int x = i;
                                int y = j - 1;
                                revealTile(x, y);
                            }
                            if (i < (rows.size() - 1) && j > 0) {
                                int x = i + 1;
                                int y = j - 1;
                                revealTile(x, y);
                            }
                            if (i > 0 && j < (rows.at(i).size() - 1)) {
                                int x = i - 1;
                                int y = j + 1;
                                revealTile(x, y);
                            }
                            if (i < (rows.size() - 1)) {
                                int x = i + 1;
                                int y = j;
                                revealTile(x, y);
                            }
                            if (j < (rows.at(i).size() - 1)) {
                                int x = i;
                                int y = j + 1;
                                revealTile(x, y);
                            }
                            if (i < (rows.size() - 1) && j < (rows.at(i).size() - 1)) {
                                int x = i + 1;
                                int y = j + 1;
                                revealTile(x, y);
                            }
                            return true;
                        }
                    }else {
                        this->rows.at(i).at(j).reveal = true;
                        return false;
                    }
                }else {return true;}
            } else {return true;}
        }
    }
    return true;
}
bool Board::flagTile(int &i, int &j) {
    if(this->rows.at(i).at(j).flagged){
        this->rows.at(i).at(j).flagged = false;
        return false;
    }
    else if(!this->rows.at(i).at(j).reveal) {
        this->rows.at(i).at(j).flagged = true;
        return true;
    } else{
        this->rows.at(i).at(j).flagged = false;
        return false;
    }
}
void Board::clearBoard() {
    //Clear vectors
    for(unsigned int i = 0; i < this->rows.size(); i++){
        rows.at(i).clear();
    }
    rows.clear();
    this->numMine = 0;
}