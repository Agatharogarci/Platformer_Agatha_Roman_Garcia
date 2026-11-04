//
// Created by Agatha on 29.10.2026.
//
#include <print>
#include <SFML/Graphics.hpp>
#include "../include/game.h"

void Game::Initialize() {

    player.Play();

    //Set the window and frame rate ---------------------------------------------------
    window.create(sf::VideoMode({800, 600}),"Platformer");
    window.setFramerateLimit(60);
}


void Game::Run() {

    //Close window action ----------------------------------------------------------

    while (window.isOpen()) {

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

        player.Update();
        window.clear(sf::Color::Black);
        player.Draw(window);
        window.display();
    }
}
