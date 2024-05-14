//
// Created by Alex Chase on 12/4/21.
//
#include <list>
#include <math.h>
using namespace std;
#ifndef UNTITLED1_FA_H
#define UNTITLED1_FA_H


class FA{
    //Structure for Cache that is fully associative
private:
    struct Node{
        //Here is a node to store address info, last referenced, etc.
    public:
        string address;
        int last_used;

        Node(string &in){
            this->address = in;
            this->last_used = 0;
        }
    };

    // All of the following are in (2^ value) format
    float sets = 1.0; // # of sets (1 for FA)
    float blocks = 0.0; // # of blocks
    float bpb = 0.0; // Bytes per block

    float hits = 0.0;
    float total = 0.0;
    int curSize = 0; // # of blocks occupied

    list<Node> nodes;
    // update hit values
    void hit(){
        this->hits += 1.0;
        this->total += 1.0;
    }
    void miss(){
        this->total += 1.0;
    }
    void upRlu(){
        for(auto it = nodes.begin(); it != nodes.end(); it++){
            it->last_used++;
        }
    }

    // Check input if it's in cache, follow fifo protocol for replacement
    void checker_fifo(string block){
        for(auto it = nodes.begin(); it != nodes.end(); it++){
            cout << "Comparing input " << block << " to in cache " << it->address << endl;
            if(block == it->address){ //hit
                cout << "We got a hit!" << endl;
                this->hit();
                return;
            }

        }
        // miss
        cout << "We missed..." << endl;
        this->curSize++;
        this->miss();
        if(this->curSize > this->blocks){
            cout << "Made replacement" << endl;
            nodes.push_front(Node(block));
            nodes.pop_back();
            this->curSize--;
        }
        else{
            nodes.push_front(Node(block));
        }
        return;
    }
    void checker_rlu(string block){
        for(auto it = nodes.begin(); it != nodes.end(); it++){
            if(block == it->address){ // hit
                cout << "Comparing input " << block << " to in cache " << it->address << endl;
                cout << "RLU hit" << endl;
                this->hit();
                nodes.erase(it);
                nodes.emplace_front(Node(block));
                this->upRlu();
                return;
            }
        }
        // miss
        cout << "Missed..." << endl;
        this->curSize++;
        this->miss();
        if(this->curSize > this->blocks){
            cout << "RLU replacement" << endl;
            nodes.push_front(Node(block));
            nodes.pop_back();
            this->curSize--;
            this->upRlu();
        }
        else{
            nodes.push_front(Node(block));
        }

    }

public:
    void setBlocks(int &b){
        this->blocks = b;
    }

    void setBpb(int &b){
        this->bpb = b;
    }
    //receive input from main and update hit values
    void input(string &in, string &rp){ //send in address and replacement policy
        int a = log2(this->bpb);
        string b = in.substr(0,in.length()-a);
        string comp = "fifo";

        if(comp == rp){
            cout << "Sort Fifo" << endl;
            // Go to fifo replacement style
            this->checker_fifo(b);
        }
        else{
            cout << "Sort RLU" << endl;
            this->checker_rlu(b);
        }
    }

    // Get hit/miss ratio
    float ratio(){
        return (this->hits/this->total) * 100.0;
    }
};
#endif //UNTITLED1_FA_H
