//
// Created by Agatha on 29.10.2026.
//
#include <print>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "../include/game.h"
#include "../include/constants.h"
#include "../include/contact.h"

Game::~Game() {
    if (b2World_IsValid(world)) {
        b2DestroyWorld(world);
    }
}
void Game::Initialize() {



    //Set the window and frame rate ---------------------------------------------------
    window.create(sf::VideoMode({960, 800}),"Platformer");
    window.setFramerateLimit(144);

    //Set menu----------------------------------------------------
    menu.Initialize();

    // Initialisation Box2D
    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, 40.f}; // Gravité vers le bas en m/s²
    world = b2CreateWorld(&def);

    player.SetupPhysics(world, {Conversions::ScreenToPhysics(200.f),
        Conversions::ScreenToPhysics(200.f)});

    enemy.SetupPhysicsM(world, {Conversions::ScreenToPhysics(400.f),
        Conversions::ScreenToPhysics(675.f)});

    const sf::Vector2f groundScreenSize = {960.f, 40.f};
    const sf::Vector2f groundScreenPos = {480.f, 750.f};

    groundShape.setSize(groundScreenSize);
    groundShape.setOrigin({groundScreenSize.x / 2.f, groundScreenSize.y / 2.f}); // Origine au centre comme Box2D
    groundShape.setPosition(groundScreenPos);
    groundShape.setFillColor(sf::Color::Red);

    //  Initialiser la physique du sol
    b2Vec2 groundPhysicsPos = {
        Conversions::ScreenToPhysics(groundScreenPos.x),
        Conversions::ScreenToPhysics(groundScreenPos.y)
    };
    b2Vec2 groundHalfSize = {
        Conversions::ScreenToPhysics(groundScreenSize.x / 2.f),
        Conversions::ScreenToPhysics(groundScreenSize.y / 2.f)
    };


    groundPhysics.Setup(world, b2_staticBody, groundPhysicsPos, groundHalfSize);
}




void Game::Run() {


    sf::Clock clock;

    while (window.isOpen()) {
        // Clock logic

        float dt = clock.restart().asSeconds();

        if (dt > 0.2f) {
            dt = 0.2f;
        }

        //Close window action && Menu ----------------------------------------------------------
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scan::Escape) {
                    window.close();
                }

            if (state == GameState::Menu) {
                MenuAction action = menu.HandleInput(*key);
                if (action == MenuAction::Play) {
                    state = GameState::Playing;
                } else if (action == MenuAction::Quit) {
                    window.close();
                }
            }
        }
            else if (const auto* resize = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resize->size));
                window.setView(sf::View(visibleArea));
            }

        }
        if (state == GameState::Playing) {
            accumulator += dt;
            while (accumulator >= kTimeStep) {
                b2World_Step(world, kTimeStep, kSubSteps);
                SensorContact(world);
                accumulator -= kTimeStep;
            }
        }
        player.Update(dt);
        enemy.UpdateSaw(dt);
        window.clear(sf::Color::Black);
        if (state == GameState::Menu) {
            menu.DrawMenu(window);
        }
        else if (state == GameState::Playing) {
            window.draw(groundShape);
            player.Draw(window);
            enemy.Draw(window);
        }
        window.display();
    }
}
