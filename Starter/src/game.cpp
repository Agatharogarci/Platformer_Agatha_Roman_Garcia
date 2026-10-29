//
// Created by Agatha on 29.10.2026.
//
#include <print>
#include <SFML/Graphics.hpp>
#include "../include/game.h"

void Game::Initialize() {
    //Set the window and frame rate
    window.create(sf::VideoMode({800, 600}),"Platformer");
    window.setFramerateLimit(60);

    //Sprite

    texture.loadFromFile("../../Starter/ressources/character_purple_front.png");

    sprite = sf::Sprite(texture);
    if (sprite) {
        sprite->setTexture(texture);
        sprite->setPosition({800, 600});
        sprite->setOrigin({800, 600});
    }



}


