//
// Created by Alex Chase on 12/3/20.
//
#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};

