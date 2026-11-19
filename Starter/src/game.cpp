//
// Created by Agatha on 29.10.2026.
//
#include <print>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <box2d/box2d.h>
#include "../include/game.h"
#include "../include/constants.h"
#include "../include/contact.h"
#include "../include/health.h"

Game::~Game() {
    platforms.clear();
    if (b2World_IsValid(world)) {
        b2DestroyWorld(world);
    }
}

void Game::RestartLevel() {
    player.Reset({Conversions::ScreenToPhysics(200.f),
                  Conversions::ScreenToPhysics(200.f)});
}

void Game::AddPlatform(sf::Vector2f screenPos, sf::Vector2f screenSize) {
    auto& plat = platforms.emplace_back(std::make_unique<Platform>());


    plat->shape.setSize(screenSize);
    plat->shape.setOrigin({screenSize.x / 2.f, screenSize.y / 2.f});
    plat->shape.setPosition(screenPos);
    plat->shape.setTexture(&groundTexture);
    plat->shape.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(screenSize.x), 40}));


    b2Vec2 physicsPos = {
        Conversions::ScreenToPhysics(screenPos.x),
        Conversions::ScreenToPhysics(screenPos.y)
    };
    b2Vec2 halfSize = {
        Conversions::ScreenToPhysics(screenSize.x / 2.f),
        Conversions::ScreenToPhysics(screenSize.y / 2.f)
    };

    plat->physics.Setup(world, b2_staticBody, physicsPos, halfSize);
}

void Game::Initialize() {



    //Set the window and frame rate ---------------------------------------------------
    window.create(sf::VideoMode({960, 775}),"Platformer");
    window.setFramerateLimit(144);

    //Set menu----------------------------------------------------
    menu.Initialize();
    health.Initialize();
    gameOver.Initialize();

    // Initialisation Box2D
    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, 40.f}; // Gravité vers le bas en m/s²
    world = b2CreateWorld(&def);

    player.SetupPhysics(world, {Conversions::ScreenToPhysics(200.f),
        Conversions::ScreenToPhysics(200.f)});

    // enemy.SetupPhysicsM(world, {Conversions::ScreenToPhysics(400.f),
    //     Conversions::ScreenToPhysics(675.f)});

    if (!groundTexture.loadFromFile("../../Starter/ressources/terrain_grass_block_top.png")) {
        std::println("erreur pas de sol pour toi");
    }

    groundTexture.setRepeated(true);

    AddPlatform({580.f, 675.f}, {960.f, 64.f});
    AddPlatform({650.f, 580.f}, {200.f, 40.f});
    AddPlatform({950.f, 460.f}, {200.f, 40.f});



}




void Game::Run() {

    sf::View camera(sf::FloatRect({0.f, 0.f}, {960.f, 775.f}));
    constexpr float scrollSpeed = 50.f;


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
                if (state == GameState::GameOver) {
                    GameOverAction action = gameOver.HandleInput(*key);
                    if (action == GameOverAction::Retry) {
                        RestartLevel();
                        camera.resetPosition();
                        state = GameState::Playing;
                    }else if (action == GameOverAction::MainMenu) {
                        state = GameState::Menu;
                    }else if (action == GameOverAction::Quit) {
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
        camera.move({scrollSpeed * dt, 0.f});
        //enemy.UpdateSaw(dt);
        window.clear(sf::Color::Black);


        if (state == GameState::Menu) {
            menu.DrawMenu(window);
        }
        else if (state == GameState::GameOver) {
            gameOver.DrawMenu(window);
        }
        else if (state == GameState::Playing) {

            for (const auto& plat : platforms) {
                window.draw(plat->shape);
            }

            player.Draw(window);
            window.setView(sf::View(camera));
            //enemy.Draw(window);

            // sf::Vector2f diff = player.GetScreenPosition() - enemy.GetScreenPosition();
            // if (std::hypot(diff.x, diff.y) < 100.f) {
            //     player.TakeDamage(1);
            // }
            if (player.GetScreenPosition().y > 800.f) {
                player.TakeDamage(3);

            }

            if (player.GetCurrentHearts() <= 0) {
                state = GameState::GameOver;

            }

            health.DrawHealth(window);

            if (player.GetScreenPosition().y > 800.f) {
                player.TakeDamage(3);
            }
        }
        window.display();
    }
}
