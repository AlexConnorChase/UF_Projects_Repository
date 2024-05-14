//
// Created by Alex Chase on 12/3/20.
//
#include "TextureManger.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
    //Set file path
    string path = "images/" + fileName + ".png";
    //Load Texture into map object
    textures[fileName].loadFromFile(path);
}
sf::Texture& TextureManager::GetTexture(string textureN){
    //Check if loaded, call this in main
    if(textures.find(textureN) == textures.end()){
        LoadTexture(textureN);
    }
    return textures[textureN];
}
void TextureManager::Clear() {
    //Clear the map
    textures.clear();
}
