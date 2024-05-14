//
// Created by Alex Chase on 11/11/20.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "imgObj.h"
// Function area just in case
void readFile(vector<imgObj>& given,string filePath){
    ifstream inFile(filePath, ios_base::binary);

    char idL;
    inFile.read((char*)&idL, sizeof(idL));
    char cMT;
    inFile.read((char*)&cMT, sizeof(cMT));
    char dTC;
    inFile.read((char*)&dTC, sizeof(dTC));
    short cMO;
    inFile.read((char*)&cMO, sizeof(cMO));
    short cML;
    inFile.read((char*)&cML, sizeof(cML));
    char cMD;
    inFile.read((char*)&cMD, sizeof(cMD));
    short xO;
    inFile.read((char*)&xO, sizeof(xO));
    short yO;
    inFile.read((char*)&yO, sizeof(yO));
    short w;
    inFile.read((char*)&w, sizeof(w));
    short h;
    inFile.read((char*)&h, sizeof(h));
    char bPP;
    inFile.read((char*)&bPP, sizeof(bPP));
    char iDes;
    inFile.read((char*)&iDes, sizeof(iDes));

    imgObj newImg = imgObj(idL, cMT, dTC, cMO, cML, cMD, xO, yO, w, h, bPP, iDes);

    for(unsigned int i = 0; i < (w*h);i++){

        unsigned char Bv;
        inFile.read((char*)&Bv, sizeof(Bv));
        unsigned char Gv;
        inFile.read((char*)&Gv, sizeof(Gv));
        unsigned char Rv;
        inFile.read((char*)&Rv, sizeof(Rv));

        newImg.addPixel(Bv, Gv, Rv);
    }

    given.push_back(newImg);
}
void writeFile(imgObj& given, string filePath){
    ofstream binaryFile("output/" + filePath, ios_base::binary);

    binaryFile.write((char*)&given.idLength,sizeof(given.idLength));

    binaryFile.write((char*)&given.colorMapType,sizeof(given.colorMapType));

    binaryFile.write((char*)&given.dataTypeCode,sizeof(given.dataTypeCode));

    binaryFile.write((char*)&given.colorMapOrigin,sizeof(given.colorMapOrigin));

    binaryFile.write((char*)&given.colorMapLength,sizeof(given.colorMapLength));

    binaryFile.write((char*)&given.colorMapDepth,sizeof(given.colorMapDepth));

    binaryFile.write((char*)&given.xOrigin,sizeof(given.xOrigin));

    binaryFile.write((char*)&given.yOrigin,sizeof(given.yOrigin));

    binaryFile.write((char*)&given.width,sizeof(given.width));

    binaryFile.write((char*)&given.height,sizeof(given.height));

    binaryFile.write((char*)&given.bitsPerPixel,sizeof(given.bitsPerPixel));

    binaryFile.write((char*)&given.imageDescriptor,sizeof(given.imageDescriptor));


    for(unsigned int i = 0; i < (given.fileData.size()); i++){
        binaryFile.write((char*)&given.fileData[i].Blue,sizeof(given.fileData[i].Blue));

        binaryFile.write((char*)&given.fileData[i].Green,sizeof(given.fileData[i].Green));

        binaryFile.write((char*)&given.fileData[i].Red,sizeof(given.fileData[i].Red));
    }
}
void writeFlip(imgObj& given, string filePath){
    ofstream binaryFile("output/" + filePath, ios_base::binary);

    binaryFile.write((char*)&given.idLength,sizeof(given.idLength));

    binaryFile.write((char*)&given.colorMapType,sizeof(given.colorMapType));

    binaryFile.write((char*)&given.dataTypeCode,sizeof(given.dataTypeCode));

    binaryFile.write((char*)&given.colorMapOrigin,sizeof(given.colorMapOrigin));

    binaryFile.write((char*)&given.colorMapLength,sizeof(given.colorMapLength));

    binaryFile.write((char*)&given.colorMapDepth,sizeof(given.colorMapDepth));

    binaryFile.write((char*)&given.xOrigin,sizeof(given.xOrigin));

    binaryFile.write((char*)&given.yOrigin,sizeof(given.yOrigin));

    binaryFile.write((char*)&given.width,sizeof(given.width));

    binaryFile.write((char*)&given.height,sizeof(given.height));

    binaryFile.write((char*)&given.bitsPerPixel,sizeof(given.bitsPerPixel));

    binaryFile.write((char*)&given.imageDescriptor,sizeof(given.imageDescriptor));


    for(unsigned int i = given.fileData.size(); i > 0; i--){
        binaryFile.write((char*)&given.fileData[i-1].Blue,sizeof(given.fileData[i-1].Blue));

        binaryFile.write((char*)&given.fileData[i-1].Green,sizeof(given.fileData[i-1].Green));

        binaryFile.write((char*)&given.fileData[i-1].Red,sizeof(given.fileData[i-1].Red));
    }
}
void writeChannel(imgObj& given, string filePath, char channel){
    ofstream binaryFile("output/" + filePath, ios_base::binary);

    binaryFile.write((char*)&given.idLength,sizeof(given.idLength));

    binaryFile.write((char*)&given.colorMapType,sizeof(given.colorMapType));

    binaryFile.write((char*)&given.dataTypeCode,sizeof(given.dataTypeCode));

    binaryFile.write((char*)&given.colorMapOrigin,sizeof(given.colorMapOrigin));

    binaryFile.write((char*)&given.colorMapLength,sizeof(given.colorMapLength));

    binaryFile.write((char*)&given.colorMapDepth,sizeof(given.colorMapDepth));

    binaryFile.write((char*)&given.xOrigin,sizeof(given.xOrigin));

    binaryFile.write((char*)&given.yOrigin,sizeof(given.yOrigin));

    binaryFile.write((char*)&given.width,sizeof(given.width));

    binaryFile.write((char*)&given.height,sizeof(given.height));

    binaryFile.write((char*)&given.bitsPerPixel,sizeof(given.bitsPerPixel));

    binaryFile.write((char*)&given.imageDescriptor,sizeof(given.imageDescriptor));


    for(unsigned int i = 0; i < (given.fileData.size()); i++){

        if(channel == 'b') {
            binaryFile.write((char *) &given.fileData[i].Blue, sizeof(given.fileData[i].Blue));
            binaryFile.write((char *) &given.fileData[i].Blue, sizeof(given.fileData[i].Blue));
            binaryFile.write((char *) &given.fileData[i].Blue, sizeof(given.fileData[i].Blue));

        }
        if(channel == 'g') {
            binaryFile.write((char *) &given.fileData[i].Green, sizeof(given.fileData[i].Green));
            binaryFile.write((char *) &given.fileData[i].Green, sizeof(given.fileData[i].Green));
            binaryFile.write((char *) &given.fileData[i].Green, sizeof(given.fileData[i].Green));
        }
        if(channel == 'r') {
            binaryFile.write((char *) &given.fileData[i].Red, sizeof(given.fileData[i].Red));
            binaryFile.write((char *) &given.fileData[i].Red, sizeof(given.fileData[i].Red));
            binaryFile.write((char *) &given.fileData[i].Red, sizeof(given.fileData[i].Red));
        }
    }
}
//Begin Main
int main(){
    int choice = 1;
    vector<imgObj> images;

    cout << "Begin running tests..." << endl;

    switch (choice){
        case 1:
            readFile(images, "input/layer1.tga");
            readFile(images, "input/pattern1.tga");
            readFile(images, "examples/EXAMPLE_part1.tga");

            images[0].multiply(images[1]);

            writeFile(images[0], "part1.tga");

            if(images[0] == images[2]){
                cout << "1: Success" << endl;
            }
            else{
                cout << "1: Failed" << endl;
            }
            images.clear();
        case 2:
            readFile(images, "input/layer2.tga");
            readFile(images, "input/car.tga");
            readFile(images, "examples/EXAMPLE_part2.tga");

            images[1].subtract(images[0]);

            writeFile(images[1], "part2.tga");

            if(images[1] == images[2]){
                cout << "2: Success" << endl;
            }
            else{
                cout << "2: Failed" << endl;
            }
            images.clear();
        case 3:
            readFile(images, "input/layer1.tga");
            readFile(images, "input/pattern2.tga");
            readFile(images, "input/text.tga");
            readFile(images, "examples/EXAMPLE_part3.tga");

            images[0].multiply(images[1]);
            images[2].screen(images[0]);

            writeFile(images[2], "part3.tga");

            if(images[2] == images[3]){
                cout << "3: Success" << endl;
            }
            else{
                cout << "3: Failed" << endl;
            }
            images.clear();
        case 4:
            readFile(images, "input/layer2.tga");
            readFile(images, "input/circles.tga");
            readFile(images, "input/pattern2.tga");
            readFile(images, "examples/EXAMPLE_part4.tga");

            images[0].multiply(images[1]);
            images[0].subtract(images[2]);

            writeFile(images[0], "part4.tga");

            if(images[0] == images[3]){
                cout << "4: Success" << endl;
            }
            else{
                cout << "4: Failed" << endl;
            }
            images.clear();
        case 5:
            readFile(images, "input/layer1.tga");
            readFile(images, "input/pattern1.tga");
            readFile(images, "examples/EXAMPLE_part5.tga");

            writeFile(images[0], "layer1.tga");

            images[0].overlay(images[1], 'r');
            images[0].overlay(images[1], 'g');
            images[0].overlay(images[1], 'b');

            writeFile(images[0], "layer_complete.tga");
            writeFile(images[1], "pattern1.tga");
            writeFile(images[2], "part5.tga");

            if(images[0] == images[2]){
                cout << "5: Success" << endl;
            }
            else{
                cout << "5: Failed" << endl;
            }
            images.clear();
        case 6:
            readFile(images, "input/car.tga");
            readFile(images, "examples/EXAMPLE_part6.tga");

            for (unsigned int i = 0; i < images[0].fileData.size(); i++) {
                int G1 = images[0].fileData[i].Green;

                G1 += 200;

                if(G1 > 255){
                    G1 = 255;
                }

                images[0].fileData[i].Green = G1;
            }

            writeFile(images[0], "part6.tga");

            if(images[0] == images[1]){
                cout << "6: Success" << endl;
            }
            else{
                cout << "6: Failed" << endl;
            }
            images.clear();
        case 7:
            readFile(images, "input/car.tga");
            readFile(images, "examples/EXAMPLE_part7.tga");

            for (unsigned int i = 0; i < images[0].fileData.size(); i++) {
                int R1 = images[0].fileData[i].Red;
                int B1 = images[0].fileData[i].Blue;

                R1 *= 4;
                B1 *= 0;

                if(R1 > 255){
                    R1 = 255;
                }

                images[0].fileData[i].Red = R1;
                images[0].fileData[i].Blue = B1;
            }

            writeFile(images[0], "part7.tga");

            if(images[0] == images[1]){
                cout << "7: Success" << endl;
            }
            else{
                cout << "7: Failed" << endl;
            }
            images.clear();
        case 8:
            readFile(images, "input/car.tga");
            readFile(images, "examples/EXAMPLE_part8_r.tga");
            readFile(images, "examples/EXAMPLE_part8_g.tga");
            readFile(images, "examples/EXAMPLE_part8_b.tga");


            writeChannel(images[0], "part8_r.tga", 'r');
            writeChannel(images[0], "part8_g.tga", 'g');
            writeChannel(images[0], "part8_b.tga", 'b');

            readFile(images, "output/part8_r.tga");
            readFile(images, "output/part8_g.tga");
            readFile(images, "output/part8_b.tga");

            if(images[1] == images[4] && images[2] == images[5] && images[3] == images[6]){
                cout << "8: Success" << endl;
            }
            else{
                cout << "8: Failed" << endl;
            }
            images.clear();
        case 9:
            readFile(images, "input/layer_red.tga");
            readFile(images, "input/layer_red.tga");
            readFile(images, "input/layer_green.tga");
            readFile(images, "input/layer_blue.tga");
            readFile(images, "examples/EXAMPLE_part9.tga");

            images[0].clear();
            images[0].add(images[1], 'r');
            images[0].add(images[2], 'g');
            images[0].add(images[3], 'b');


            writeFile(images[0], "part9.tga");

            if(images[0] == images[4]){
                cout << "9: Success" << endl;
            }
            else{
                cout << "9: Failed" << endl;
            }
            images.clear();
        case 10:
            readFile(images, "input/text2.tga");
            readFile(images, "examples/EXAMPLE_part10.tga");

            writeFlip(images[0], "part10.tga");

            readFile(images, "output/part10.tga");

            if(images[1] == images[2]) {
                cout << "10: Success" << endl;
            }
            else{
                cout << "10: Failed" << endl;
            }
            images.clear();
    }
    return 0;
}
