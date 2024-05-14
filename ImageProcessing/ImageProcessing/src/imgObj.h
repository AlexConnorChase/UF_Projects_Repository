//
// Created by Alex Chase on 11/11/20.
//
#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class imgObj{
public:
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    struct Pixel{
        unsigned char Red;
        unsigned char Blue;
        unsigned char Green;
    };

    vector<Pixel> fileData;

    //Constructors
    imgObj();
    imgObj(char& _iL, char& _CMT, char& _DTC, short& _CMO, short& _CML, char& _CMD, short& _xO, short& _yO, short& _w, short& _h, char& _BPP, char& _iD);
    void addPixel(unsigned char& rVal, unsigned char& bVal, unsigned char& gVal);
    //Functions
    bool subtract(imgObj& rhs);
    bool multiply(imgObj& rhs);
    bool screen(imgObj& rhs);
    bool add(imgObj& rhs, char channel);
    void clear();
    bool overlay(imgObj& rhs, char channel);
    //Operators
    bool operator==(const imgObj& rhs) const;
};

imgObj::imgObj() {
    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 0;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    width = 0;
    height = 0;
    bitsPerPixel = 0;
    imageDescriptor = 0;
}
imgObj::imgObj(char &_iL, char &_CMT, char &_DTC, short &_CMO, short &_CML, char &_CMD, short &_xO, short &_yO,short &_w, short &_h, char &_BPP, char &_iD) {
    idLength = _iL;
    colorMapType = _CMT;
    dataTypeCode = _DTC;
    colorMapOrigin = _CMO;
    colorMapLength = _CML;
    colorMapDepth = _CMD;
    xOrigin = _xO;
    yOrigin = _yO;
    width = _w;
    height = _h;
    bitsPerPixel = _BPP;
    imageDescriptor = _iD;
}
void imgObj::addPixel(unsigned char &bVal, unsigned char &gVal, unsigned char &rVal) {
    Pixel newPix;
    newPix.Blue = bVal;
    newPix.Green = gVal;
    newPix.Red = rVal;
    fileData.push_back(newPix);
}
//Begin Functions ******************************************************************************************************
bool imgObj::subtract(imgObj& rhs){
    if(this->fileData.size() == rhs.fileData.size()){
        for(unsigned int i = 0; i < fileData.size(); i++){
            int R1 = this->fileData[i].Red;
            int B1 = this->fileData[i].Blue;
            int G1 = this->fileData[i].Green;
            int R2 = rhs.fileData[i].Red;
            int B2 = rhs.fileData[i].Blue;
            int G2 = rhs.fileData[i].Green;

            if(R1 > R2){
                R1 -= R2;
                this->fileData[i].Red = R1;
            }
            else{
                this->fileData[i].Red = 0;
            }
            if(B1 > B2){
                B1 -= B2;
                this->fileData[i].Blue = B1;
            }
            else{
                this->fileData[i].Blue = 0;
            }
            if(G1 > G2){
                G1 -= G2;
                this->fileData[i].Green = G1;
            }
            else{
                this->fileData[i].Green = 0;
            }
        }
        return true;
    }
    else{
        return false;
    }
}
bool imgObj::multiply(imgObj &rhs) {
    if(this->fileData.size() == rhs.fileData.size()) {
        for (unsigned int i = 0; i < fileData.size(); i++) {
            float R1 = this->fileData[i].Red / 255.0f;
            float B1 = this->fileData[i].Blue / 255.0f;
            float G1 = this->fileData[i].Green / 255.0f;
            float R2 = rhs.fileData[i].Red / 255.0f;
            float B2 = rhs.fileData[i].Blue / 255.0f;
            float G2 = rhs.fileData[i].Green / 255.0f;

            R1 *= R2;
            R1 *= 255.0f;
            R1 += 0.5f;
            B1 *= B2;
            B1 *= 255.0f;
            B1 += 0.5f;
            G1 *= G2;
            G1 *= 255.0f;
            G1 += 0.5f;

            this->fileData[i].Red = (unsigned char)R1;
            this->fileData[i].Blue = (unsigned char)B1;
            this->fileData[i].Green = (unsigned char)G1;
        }
        return true;
    }
    else{
        return false;
    }
}
bool imgObj::screen(imgObj &rhs) {
    if(this->fileData.size() == rhs.fileData.size()) {
        for (unsigned int i = 0; i < fileData.size(); i++) {
            float R1 = this->fileData[i].Red / 255.0f;
            float B1 = this->fileData[i].Blue / 255.0f;
            float G1 = this->fileData[i].Green / 255.0f;
            float R2 = rhs.fileData[i].Red / 255.0f;
            float B2 = rhs.fileData[i].Blue / 255.0f;
            float G2 = rhs.fileData[i].Green / 255.0f;

            R1 = 1-((1-R1)*(1-R2));
            R1 *= 255.0f;
            R1 += 0.5f;
            B1 = 1-((1-B1)*(1-B2));
            B1 *= 255.0f;
            B1 += 0.5f;
            G1 = 1-((1-G1)*(1-G2));
            G1 *= 255.0f;
            G1 += 0.5f;

            this->fileData[i].Red = (unsigned char)R1;
            this->fileData[i].Blue = (unsigned char)B1;
            this->fileData[i].Green = (unsigned char)G1;
        }
        return true;
    }
    else{
        return false;
    }
}
bool imgObj::add(imgObj &rhs, char channel) {
    if(this->fileData.size() == rhs.fileData.size()){
        for(unsigned int i = 0; i < fileData.size(); i++){
            int R1 = this->fileData[i].Red;
            int B1 = this->fileData[i].Blue;
            int G1 = this->fileData[i].Green;
            int R2 = rhs.fileData[i].Red;
            int B2 = rhs.fileData[i].Blue;
            int G2 = rhs.fileData[i].Green;

            if(channel == 'r') {
                if ((R1 + R2) > 255) {
                    this->fileData[i].Red = 255;
                } else {
                    R1 += R2;
                    this->fileData[i].Red = R1;
                }
            }
            if(channel == 'b') {
                if ((B1 + B2) > 255) {
                    this->fileData[i].Blue = 255;
                } else {
                    B1 += B2;
                    this->fileData[i].Blue = B1;
                }
            }
            if(channel == 'g') {
                if ((G1 + G2) > 255) {
                    this->fileData[i].Green = 255;
                } else {
                    G1 += G2;
                    this->fileData[i].Green = G1;
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}
void imgObj::clear() {
    for(unsigned int i = 0; i < fileData.size(); i++){
        fileData[i].Red = 0;
        fileData[i].Blue = 0;
        fileData[i].Green = 0;
    }
}
bool imgObj::overlay(imgObj &rhs, char channel) {
    if(this->fileData.size() == rhs.fileData.size()) {
        for (unsigned int i = 0; i < fileData.size(); i++) {
            float Val1;
            float Val2;
            if (channel == 'r') {
                Val1 = this->fileData[i].Red / 255.0f;
                Val2 = rhs.fileData[i].Red / 255.0f;
            }
            if (channel == 'g') {
                Val1 = this->fileData[i].Green / 255.0f;
                Val2 = rhs.fileData[i].Green / 255.0f;
            }
            if (channel == 'b') {
                Val1 = this->fileData[i].Blue / 255.0f;
                Val2 = rhs.fileData[i].Blue / 255.0f;
            }

            if (Val2 > 0.5f) {
                Val1 = 1 - (2 * (1 - Val1) * (1 - Val2));
                Val1 *= 255.0f;
                Val1 += 0.5f;

                if (channel == 'r') {
                    this->fileData[i].Red = (unsigned char) Val1;
                }
                if (channel == 'b') {
                    this->fileData[i].Blue = (unsigned char) Val1;
                }
                if (channel == 'g') {
                    this->fileData[i].Green = (unsigned char) Val1;
                }

            }
            if (Val2 <= 0.5f) {
                Val1 = (2 * Val1 * Val2);
                Val1 *= 255.0f;
                Val1 += 0.5f;

                if (channel == 'r') {
                    this->fileData[i].Red = (unsigned char) Val1;
                }
                if (channel == 'b') {
                    this->fileData[i].Blue = (unsigned char) Val1;
                }
                if (channel == 'g') {
                    this->fileData[i].Green = (unsigned char) Val1;
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}
//Begin Operators ******************************************************************************************************
bool imgObj::operator==(const imgObj &rhs) const {

    if(this->fileData.size() == rhs.fileData.size()){
        for(unsigned int i = 0; i < fileData.size(); i++){
            if(this->fileData[i].Red != rhs.fileData[i].Red){
             return false;
            }
            else if(this->fileData[i].Blue != rhs.fileData[i].Blue){
                return false;
            }
            else if(this->fileData[i].Green != rhs.fileData[i].Green){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}