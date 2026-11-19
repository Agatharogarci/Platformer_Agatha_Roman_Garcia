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
#include "../include/settings.h"

Game::~Game() {
    platforms.clear();
    if (b2World_IsValid(world)) {
        b2DestroyWorld(world);
    }
}

void Game::RestartLevel() {
    player.Reset({
        Conversions::ScreenToPhysics(200.f),
        Conversions::ScreenToPhysics(200.f)
    });
    camera.setCenter({480.f, 387.5f});
}

void Game::AddPlatform(sf::Vector2f screenPos, sf::Vector2f screenSize) {
    auto &plat = platforms.emplace_back(std::make_unique<Platform>());


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
    window.create(sf::VideoMode(Platformer::WINDOW_SIZE), "Platformer");
    window.setFramerateLimit(144);
    camera = sf::View(sf::FloatRect({0.f, 0.f}, {960.f, 775.f}));
    healthV = sf::View(sf::FloatRect({0.f, 0.f}, {960.f, 775.f}));


    //Set menu----------------------------------------------------
    menu.Initialize();
    health.Initialize();
    gameOver.Initialize();

    // Initialisation Box2D
    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, Platformer::GRAVITY}; // Gravité vers le bas en m/s²
    world = b2CreateWorld(&def);

    player.SetupPhysics(world, {
                            Conversions::ScreenToPhysics(200.f),
                            Conversions::ScreenToPhysics(200.f)
                        });

    enemy.SetupPhysics(world, {
                            Conversions::ScreenToPhysics(1560.f),
                            Conversions::ScreenToPhysics(300.f)
                        });
    winFlag.SetupPhysics(world, {
                            Conversions::ScreenToPhysics(1950.f),
                            Conversions::ScreenToPhysics(300.f)});

    if (!groundTexture.loadFromFile("../../Starter/ressources/terrain_grass_block_top.png")) {
        std::println("erreur pas de sol pour toi");
    }

    groundTexture.setRepeated(true);

    //sol----------------------------
    AddPlatform({580.f, 735.f}, {960.f, 64.f});
    AddPlatform({650.f, 595.f}, {200.f, 40.f});
    AddPlatform({950.f, 480.f}, {200.f, 40.f});
    AddPlatform({1550.f, 380.f}, {1000.f, 40.f});
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
            } else if (const auto *key = event->getIf<sf::Event::KeyPressed>()) {
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
                        state = GameState::Playing;
                    } else if (action == GameOverAction::MainMenu) {
                        RestartLevel();
                        state = GameState::Menu;
                    } else if (action == GameOverAction::Quit) {
                        window.close();
                    }
                }
                if (state == GameState::Win) {
                    MenuActionWin action = win.HandleInput(*key);
                    if (action == MenuActionWin::Quit) {
                        window.close();
                    }
                    else if (action == MenuActionWin::MainMenu) {
                        state = GameState::Menu;
                    }
                }
            } else if (const auto *resize = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resize->size));
                window.setView(sf::View(visibleArea));
            }
        }

        // ============================================================================================================================

        // camera.move({scrollSpeed * dt, 0.f});

        if (state == GameState::Playing) {
            accumulator += dt;
            while (accumulator >= kTimeStep) {
                b2World_Step(world, kTimeStep, kSubSteps);
                SensorContact(world);
                accumulator -= kTimeStep;
            }

            //Update-------------------------------------------------------------------------------------------------
            player.Update(dt);
            enemy.Update(dt);
            winFlag.Update(dt);
            //TakeDamage---------------------------------------------------------------------------------------------
            sf::Vector2f diff = player.GetScreenPosition() - enemy.GetScreenPosition();
            if (std::hypot(diff.x, diff.y) < 100.f) {
                player.TakeDamage(3);
            }

            if (player.GetScreenPosition().y > 800.f) {
                player.TakeDamage(3);
            }

            if (player.GetCurrentHearts() <= 0) {
                window.setView(window.getDefaultView());
                state = GameState::GameOver;
            }

            if (player.GetScreenPosition().y > 800.f) {
                player.TakeDamage(3);
            }

            camera.move({Platformer::SCROLLSPEED * dt, 0.f});
        }


        // ========================================================================================================================================
        // enemy.UpdateSaw(dt);
        window.clear(sf::Color::Black);


        if (state == GameState::GameOver) {
            gameOver.Draw(window);
        }
        if (state == GameState::Win) {
            win.Draw(window);
        }

        if (state == GameState::Menu) {
            menu.Draw(window);
        }


        else if (state == GameState::Playing) {
            for (const auto &plat: platforms) {
                window.draw(plat->shape);
                winFlag.Draw(window);
            }

            window.setView(sf::View(healthV));
            health.DrawHealth(window);
            window.setView(sf::View(camera));
            player.Draw(window);
            enemy.Draw(window);


        }


        window.display();
    }
}
