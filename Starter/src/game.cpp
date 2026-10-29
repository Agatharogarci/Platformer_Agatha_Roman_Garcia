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

void Game::Run() {

    while (window.isOpen()) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            sprite->move({0,-1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            sprite->move({0,1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
            sprite->move({-1,0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            sprite->move({1,0});
        }

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scan::Escape) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);
        if (sprite.has_value()) {
            window.draw(*sprite);
        }
        window.display();
    }
}
