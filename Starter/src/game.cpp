//
// Created by Agatha on 29.10.2026.
//
#include <print>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "../include/game.h"
#include "../include/constants.h"

Game::Game() {
    if (b2World_IsValid(world)) {
        b2DestroyWorld(world);
    }
}
void Game::Initialize() {



    //Set the window and frame rate ---------------------------------------------------
    window.create(sf::VideoMode({960, 540}),"Platformer");
    window.setFramerateLimit(60);


    // Initialisation Box2D
    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, 9.81f}; // Gravité vers le bas en m/s²
    world = b2CreateWorld(&def);

    player.SetupPhysics(world, {Conversions::ScreenToPhysics(200.f), Conversions::ScreenToPhysics(200.f)});
}



void Game::Run() {


    sf::Clock clock;
    //Close window action ----------------------------------------------------------



    while (window.isOpen()) {
        // Clock logic

        float dt = clock.restart().asSeconds();

        if (dt > 0.2f) {
            dt = 0.2f;
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
            while (accumulator >= kTimeStep) {
                b2World_Step(world, kTimeStep, kSubSteps);
                accumulator -= kTimeStep;
            }
        }

        player.Update(dt);
        window.clear(sf::Color::Black);
        player.Draw(window);
        window.display();
    }
}
