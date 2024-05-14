#include <iostream>
#include <fstream>
#include <chrono> // for std::chrono functions
#include "FA.h"
#include "SA.h"
#include "DM.h"
using namespace std;

#pragma once

//This timer class will allow the project to calculate the elapsed time for the project
class Timer{//All timing is O(1)
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::steady_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> begin;

public:
    Timer() : begin(clock_t::now()) //Set starting time
    {
    }

    void reset() //Set new starting time
    {
        begin = clock_t::now();
    }

    double elapsed() const // Get current elapsed time
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - begin).count();
    }
};

string GetInput(string &input){ //Convert address line into string
    string ret;
    for(int i = 4; i < 12; i++){
        ret = input.substr(4,8);
    }
    return ret;
}

string HexToBin(string &hexdec)
{
    long int i = 0;
    string ret = "";
    while (hexdec[i]) {

        switch (hexdec[i]) {
            case '0':
                ret += "0000";
                break;
            case '1':
                ret += "0001";
                break;
            case '2':
                ret += "0010";
                break;
            case '3':
                ret += "0011";
                break;
            case '4':
                ret += "0100";
                break;
            case '5':
                ret += "0101";
                break;
            case '6':
                ret += "0110";
                break;
            case '7':
                ret += "0111";
                break;
            case '8':
                ret += "1000";
                break;
            case '9':
                ret += "1001";
                break;
            case 'A':
            case 'a':
                ret += "1010";
                break;
            case 'B':
            case 'b':
                ret += "1011";
                break;
            case 'C':
            case 'c':
                ret += "1100";
                break;
            case 'D':
            case 'd':
                ret += "1101";
                break;
            case 'E':
            case 'e':
                ret += "1110";
                break;
            case 'F':
            case 'f':
                ret += "1111";
                break;
            default:
                cout << "\nInvalid hexadecimal digit "
                     << hexdec[i];
                return ret;
        }
        i++;
    }
    return ret;
}


int main() {
    //file components
    ifstream file;
    file.open("gcc.txt");
    string input;
    string in_n;

    list<string> strings;

    // Get input for each line of  the txt file
    while(getline(file, input)){
        in_n = GetInput(input);
        string a = HexToBin(in_n);

        strings.push_front(a);
    }

//    for(auto it = strings.begin(); it != strings.end(); it++){
//        cout << *it << endl;
//    }

    // Size of txt file check


    // Temporary input test
//    for(int i = 0; i <5; i++){
//        if(file.is_open()) {
//            getline(file, input);
//            cout << input << endl;
//            in_n = GetInput(input);
//            string a = HexToBin(in_n);
//            cout << a << endl;
//            int b = log2(4);
//            string c = a.substr(0,a.length()-b);
//            cout << c << endl;
//        }
//        else{
//            cout  << "Frick, it happened again..." << endl;
//            return 0;
//        }
//    }

    //Temporary FA tests
//    int blocksFA = 8;
//    int bpbFA = 32;
//    FA test_1;
//    FA test_2;
//    test_1.setBlocks(blocksFA);
//    test_1.setBpb(bpbFA);
//    test_2.setBlocks(blocksFA);
//    test_2.setBpb(bpbFA);
//
//        for(auto it = strings.begin(); it != strings.end(); it++){
//                string in = "fifo";
//                test_1.input(*it,in);
//                cout << "Ratio now: " << test_1.ratio() << endl;
//        }
//
//    for(auto it = strings.begin(); it != strings.end(); it++){
//            string in = "fi";
//            test_2.input(*it,in);
//            cout << "Ratio now: " << test_2.ratio() << endl;
//
//    }
//    cout << "Ratio for Test 1: " << test_1.ratio() << "%" << endl;
//    cout << "Ratio for Test 1: " << test_2.ratio() << "%" << endl;

    // Here is where we will put all the test cases
        /*
         * Small Size:
         *  # of Sets = 2(2^1); # Blocks = 2; Size of blocks = 4
         *
         * Medium Size:
         *  # of Sets = 8(2^3); # Blocks = 8; Size of blocks = 16
         *
         * Large Size:
         *  # of Sets = 32(2^4); # Blocks = 32; Size of blocks = 32
         */
    // Fully-Associative Tests
        // FIFO Tests ***************************************************************************************************
    int blocksFA = 4;
    int bpbFA = 8;
    FA test_1;
    test_1.setBlocks(blocksFA);
    test_1.setBpb(bpbFA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fifo";
        test_1.input(*it,in);
        cout << "Ratio now: " << test_1.ratio() << endl;
    }
    blocksFA = 8;
    bpbFA = 16;
    FA test_2;
    test_2.setBlocks(blocksFA);
    test_2.setBpb(bpbFA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fifo";
        test_2.input(*it,in);
        cout << "Ratio now: " << test_2.ratio() << endl;
    }
    blocksFA = 16;
    bpbFA = 32;
    FA test_3;
    test_3.setBlocks(blocksFA);
    test_3.setBpb(bpbFA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fifo";
        test_3.input(*it,in);
        cout << "Ratio now: " << test_3.ratio() << endl;
    }

    // LRU Tests ******************************************************************************************************
    blocksFA = 4;
    bpbFA = 8;
    FA test_4;
    test_4.setBlocks(blocksFA);
    test_4.setBpb(bpbFA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fi";
        test_4.input(*it,in);
        cout << "Ratio now: " << test_4.ratio() << endl;
    }
    blocksFA = 8;
    bpbFA = 16;
    FA test_5;
    test_5.setBlocks(blocksFA);
    test_5.setBpb(bpbFA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fi";
        test_5.input(*it,in);
        cout << "Ratio now: " << test_5.ratio() << endl;
    }
    blocksFA = 16;
    bpbFA = 32;
    FA test_6;
    test_6.setBlocks(blocksFA);
    test_6.setBpb(bpbFA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "f";
        test_6.input(*it,in);
        cout << "Ratio now: " << test_6.ratio() << endl;
    }

    // Set-Associative Tests
        //FIFO Tests *************************************************************************************************
    int setsSA = 32;
    int blocksSA = 4;
    int bpbSA = 2;
    SA test_7;
    test_7.setSets(setsSA);
    test_7.setBlocks(blocksSA);
    test_7.setBpb(bpbSA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fifo";
        test_7.input(*it,in);
        cout << "Ratio now: " << test_7.ratio() << endl;
    }

    setsSA = 64;
    blocksSA = 4;
    bpbSA = 2;
    SA test_8;
    test_8.setSets(setsSA);
    test_8.setBlocks(blocksSA);
    test_8.setBpb(bpbSA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fifo";
        test_8.input(*it,in);
        cout << "Ratio now: " << test_8.ratio() << endl;
    }

    setsSA = 128;
    blocksSA = 4;
    bpbSA = 2;
    SA test_9;
    test_9.setSets(setsSA);
    test_9.setBlocks(blocksSA);
    test_9.setBpb(bpbSA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fifo";
        test_9.input(*it,in);
        cout << "Ratio now: " << test_9.ratio() << endl;
    }
        // RLU Tests **************************************************************************************************
    setsSA = 32;
    blocksSA = 4;
    bpbSA = 2;
    SA test_10;
    test_10.setSets(setsSA);
    test_10.setBlocks(blocksSA);
    test_10.setBpb(bpbSA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fi";
        test_10.input(*it,in);
        cout << "Ratio now: " << test_10.ratio() << endl;
    }

    setsSA = 64;
    blocksSA = 4;
    bpbSA = 2;
    SA test_11;
    test_11.setSets(setsSA);
    test_11.setBlocks(blocksSA);
    test_11.setBpb(bpbSA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fi";
        test_11.input(*it,in);
        cout << "Ratio now: " << test_11.ratio() << endl;
    }

    setsSA = 128;
    blocksSA = 4;
    bpbSA = 2;
    SA test_12;
    test_12.setSets(setsSA);
    test_12.setBlocks(blocksSA);
    test_12.setBpb(bpbSA);
    for(auto it = strings.begin(); it != strings.end(); it++){
        string in = "fi";
        test_12.input(*it,in);
        cout << "Ratio now: " << test_12.ratio() << endl;
    }

    // Direct-Mapped Tests *******************************************************************************************
    int setsDM = 8;
    int bpbDM = 4;
    DM test_13;
    test_13.setSets(setsDM);
    test_13.setBpb(bpbDM);
    for(auto it = strings.begin(); it != strings.end(); it++){
        test_13.input(*it);
        cout << "Ratio now: " << test_13.ratio() << endl;
    }

    setsDM = 16;
    bpbDM = 8;
    DM test_14;
    test_14.setSets(setsDM);
    test_14.setBpb(bpbDM);
    for(auto it = strings.begin(); it != strings.end(); it++){
        test_14.input(*it);
        cout << "Ratio now: " << test_14.ratio() << endl;
    }

    setsDM = 32;
    bpbDM = 16;
    DM test_15;
    test_15.setSets(setsDM);
    test_15.setBpb(bpbDM);
    for(auto it = strings.begin(); it != strings.end(); it++){
        test_15.input(*it);
        cout << "Ratio now: " << test_15.ratio() << endl;
    }

    // Post Results
    cout << "FA TESTS - FIFO" << endl;
    cout << "Ratio for Test 1: " << test_1.ratio() << "%" << endl;
    cout << "Ratio for Test 2: " << test_2.ratio() << "%" << endl;
    cout << "Ratio for Test 3: " << test_3.ratio() << "%" << endl;
    cout << "FA TESTS - RLU" << endl;
    cout << "Ratio for Test 4: " << test_4.ratio() << "%" << endl;
    cout << "Ratio for Test 5: " << test_5.ratio() << "%" << endl;
    cout << "Ratio for Test 6: " << test_6.ratio() << "%" << endl;
    cout << "SA TESTS - FIFO" << endl;
    cout << "Ratio for Test 7: " << test_7.ratio() << "%" << endl;
    cout << "Ratio for Test 8: " << test_8.ratio() << "%" << endl;
    cout << "Ratio for Test 9: " << test_9.ratio() << "%" << endl;
    cout << "SA TESTS - RLU" << endl;
    cout << "Ratio for Test 10: " << test_10.ratio() << "%" << endl;
    cout << "Ratio for Test 11: " << test_11.ratio() << "%" << endl;
    cout << "Ratio for Test 12: " << test_12.ratio() << "%" << endl;
    cout << "DM TESTS" << endl;
    cout << "Ratio for Test 13: " << test_13.ratio() << "%" << endl;
    cout << "Ratio for Test 14: " << test_14.ratio() << "%" << endl;
    cout << "Ratio for Test 15: " << test_15.ratio() << "%" << endl;
    return 0;
}


/* References and Materials
 * Timer model: https://www.learncpp.com/cpp-tutorial/timing-your-code/
 *
 */
