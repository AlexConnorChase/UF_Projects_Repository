//
// Created by Alex Chase on 12/5/21.
//
#include <map>
#include <math.h>
using namespace std;
#ifndef CACHEPROJECTAC_DM_H
#define CACHEPROJECTAC_DM_H

class DM{
private:
    // Variables
    map<int,string> nodes;
    int sets = 0; // # of sets
    int blocks = 1; // # of blocks (1 for DM)
    int bpb = 0; // Bytes per block

    float hits = 0.0;
    float total = 0.0;

    // Helper functions
    int binaryToDecimal(string n)
    {
        int dec_value = 0;

        // Initializing base value to 1, i.e 2^0
        int base = 1;

        for(int i = n.length()-1; i > 0; i--) {
            if((n.at(i)) == '1'){
                dec_value +=  base;
            }

            base = base * 2;
        }
        cout << "Bin2Dec: " << dec_value << endl;
        return dec_value;
    }

    void hit(){
        this->hits += 1.0;
        this->total += 1.0;
    }
    void miss(){
        this->total += 1.0;
    }

    void checker(string &tag, int &line){
        if(nodes.find(line) != nodes.end()) {
            if (nodes.at(line) == tag) { // Hit
                cout << "Hit!" << endl;
                this->hit();
                return;
            }
        }

        //If miss
        cout << "Miss..." << endl;
        nodes.emplace(line,tag);
        this->miss();
        return;
    }

public:
    void setSets(int &b){
        this->sets = b;
        return;
    }

    void setBpb(int &b){
        this->bpb = b;
        return;
    }

    void makeMap(int &b){
        for(int i = 0;  i < 2^b; i++){
            nodes.emplace(i, "00");
        }
    }

    void input(string &in){ //send in address and replacement policy
        int a = log2(this->bpb);
        string b = in.substr(0,in.length()-a);
        int c = this->sets - this->bpb;
        string line = b.substr(b.length()-c, c);
        string add = b.substr(0, b.length()-(c));
        //We have the tag + line address, solve for that then insert into list
        int l = binaryToDecimal(line);
        this->checker(add,l);
        return;
    }

    // Get hit/miss ratio
    float ratio(){
        return (this->hits/this->total) * 100.0;
    }
};
#endif //CACHEPROJECTAC_DM_H
