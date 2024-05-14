//
// Created by Alex Chase on 12/6/21.
//
#include <vector>
#include <math.h>
using namespace std;
#ifndef CACHEPROJECTAC_SA_H
#define CACHEPROJECTAC_SA_H

class SA{
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

    vector<pair<int,vector<Node>>> nodes;
    vector<vector<Node>> Nodes;
    int sets = 0; // # of sets
    int blocks = 0; // # of blocks/ lines
    int bpb = 0; // Bytes per block

    float hits = 0.0;
    float total = 0.0;
    int curSize = 0; // # of blocks occupied

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
    void upRlu(){
        for(auto it = nodes.begin(); it != nodes.end(); it++){
            for(auto itr = it->second.begin(); itr != it->second.end(); itr++){ // Tag hit
                itr->last_used++;
            }
        }
    }

    void checker_fifo(string &tag, int &add){
//        for(auto it = nodes.begin(); it != nodes.end(); it++){
//            cout << "Comparing input " << tag << " to in cache " << it->second.address << endl;
//            if(add == it->first) {
//                if (tag == it->second.address) { //hit
//                    cout << "We got a hit!" << endl;
//                    this->hit();
//                    this->upRlu();
//                    return;
//                }
//                else break;
//            }
//
//        }
//        // miss
//        cout << "We missed..." << endl;
//        this->curSize++;
//        this->miss();
//        if(this->curSize > this->blocks){
//            cout << "Made replacement" << endl;
//            nodes.push_back(make_pair(add,Node(tag)));
//            nodes.pop_back();
//            this->curSize--;
//        }
//        else{
//            nodes.push_back(make_pair(add,Node(tag)));
//        }

        for(auto it = nodes.begin(); it != nodes.end(); it++){
            if(add ==  it->first){ // line # hit
                cout << "Line hit!" << endl;
                for(auto itr = it->second.begin(); itr != it->second.end(); itr++){
                    if(itr->address == tag) {// Tag hit
                        cout << "Tag Hit!" << endl;
                        this->hit();
                        return;
                    }
                }
                // line # hit, tag did not, update tags
                cout << "Tag miss." << endl;

                it->second.push_back(Node(tag));
                if(it->second.size() >this->blocks){
                    cout << "Tag Replacement" << endl;
                    it->second.pop_back();
                }
                this->miss();
                return;
            }
        }
        // Line # did not hit
        vector<Node> n;
        n.push_back(Node(tag));
        nodes.push_back(make_pair(add, n));
        if(nodes.size() > this->sets){
            nodes.pop_back();
        }
        this->miss();
    }

    void checker_rlu(string &tag, int &add){
//        for(auto it = nodes.begin(); it != nodes.end(); it++){
//            if(add == it->first) {
//                if (tag == it->second.address) { // hit
//                    cout << "Comparing input " << tag << " to in cache " << it->second.address << endl;
//                    cout << "RLU hit" << endl;
//                    this->hit();
//                    nodes.erase(it);
//                    nodes.push_back(make_pair(add, Node(tag)));
//                    this->upRlu();
//                    return;
//                }
//                else break;
//            }
//        }
//        // miss
//        cout << "Missed..." << endl;
//        this->curSize++;
//        this->miss();
//        if(this->curSize > this->blocks){
//            cout << "RLU replacement" << endl;
//            nodes.push_back(make_pair(add,Node(tag)));
//            nodes.pop_back();
//            this->curSize--;
//            this->upRlu();
//        }
//        else{
//            nodes.push_back(make_pair(add,Node(tag)));
//        }

        for(auto it = nodes.begin(); it != nodes.end(); it++){
            if(add ==  it->first){ // line # hit
                cout << "Line hit!" << endl;
                for(auto itr = it->second.begin(); itr != it->second.end(); itr++){
                    if(itr->address == tag) {// Tag hit
                        cout << "Tag Hit!" << endl;
                        this->hit();
                        it->second.erase(itr);
                        it->second.push_back(tag);
                        return;
                    }
                }
                // line # hit, tag did not, update tags
                cout << "Tag miss." << endl;
                it->second.push_back(Node(tag));
                auto itr = it->second;
                nodes.erase(it);
                nodes.push_back(make_pair(add,itr));
                if(it->second.size() >this->blocks){
                    cout << "Tag Replacement" << endl;
                    it->second.pop_back();
                }
                this->miss();
                return;
            }
        }
        // Line # did not hit
        vector<Node> n;
        n.push_back(Node(tag));
        nodes.push_back(make_pair(add, n));
        if(nodes.size() > this->sets){
            nodes.pop_back();
        }
        this->miss();
    }
public:
    void setSets(int &b){
        this->sets = b;
        return;
    }

    void setBlocks(int &b){
        this->blocks = b;
    }

    void setBpb(int &b){
        this->bpb = b;
        return;
    }

    void input(string &in, string &rp){
        int a = log2(this->bpb);
        string b = in.substr(0,in.length()-a);
        int c = this->sets/ ( this->blocks *this->bpb);
        c = log2(c);
        string line = b.substr(b.length()-c, c);
        string add = b.substr(0, b.length()-c);
        int l = binaryToDecimal(line);

        cout << "Tag: " << add << endl;
        cout << "Line: " << l << endl;
        string comp = "fifo";

        if(comp == rp){
            cout << "Sort Fifo" << endl;
            // Go to fifo replacement style
            this->checker_fifo(add,l);
        }
        else{
            cout << "Sort RLU" << endl;
            this->checker_rlu(add,l);
        }
    }

    float ratio(){
        return (this->hits/this->total) * 100.0;
    }
};
#endif //CACHEPROJECTAC_SA_H
