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

void Game::RestartLevel(bool fullReset ) {
    if (fullReset) {
        checkpointActivated = false;
        currentSpawnScreenPos = {200.f, 425.f};
        checkpointShape.setFillColor(sf::Color::Red);
        levelTimer = 0.0f;
    }

    player.Reset({
        Conversions::ScreenToPhysics(currentSpawnScreenPos.x),
        Conversions::ScreenToPhysics(currentSpawnScreenPos.y)
    });

    float camX = checkpointActivated ? currentSpawnScreenPos.x + 50.f : 400.f;
    camera.setCenter({camX, 387.5f});

    if (!checkpointActivated) {
        levelTimer = 0.0f;
    }
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
    camera.setCenter({400.f, 387.5f});
    healthV = sf::View(sf::FloatRect({0.f, 0.f}, {960.f, 775.f}));

    if (!font.openFromFile("../../Starter/ressources/BAUHS93.TTF")) {
        std::println("erreur dans le game initialisation");
    }
        timerText.emplace(font, "0.00s", 35);
        timerText->setFillColor(sf::Color::White);
        timerText->setPosition({20.f, 5.f});



    //Set menu----------------------------------------------------
    menu.Initialize();
    health.Initialize();
    gameOver.Initialize();
    win.Initialize();

    // Initialisation Box2D
    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, Platformer::GRAVITY}; // Gravité vers le bas en m/s²
    world = b2CreateWorld(&def);

    player.SetupPhysics(world, {
                            Conversions::ScreenToPhysics(200.f),
                            Conversions::ScreenToPhysics(425.f)
                        });

    enemy.SetupPhysics(world, {
                            Conversions::ScreenToPhysics(800.f),
                            Conversions::ScreenToPhysics(520.f)
                        });
    winFlag.SetupPhysics(world, {
                            Conversions::ScreenToPhysics(5060.f),
                            Conversions::ScreenToPhysics(400.f)});

    // Checkpoint setup-----------------------------------------------------------------
    checkpointShape.setSize({30.f, 60.f});
    checkpointShape.setOrigin({15.f, 30.f});
    checkpointShape.setFillColor(sf::Color::Red);
    checkpointShape.setPosition(checkpointScreenPos);

    if (!groundTexture.loadFromFile("../../Starter/ressources/terrain_grass_block_top.png")) {
        std::println("erreur pas de sol pour toi");
    }

    groundTexture.setRepeated(true);

    //sol----------------------------

    AddPlatform({350.f, 720.f}, {700.f, 64.f});

    AddPlatform({910.f, 700.f}, {220.f, 40.f});

    AddPlatform({1290.f, 620.f}, {320.f, 40.f});

    AddPlatform({1840.f, 600.f}, {360.f, 40.f});

    AddPlatform({2220.f, 525.f}, {160.f, 40.f});

    AddPlatform({2560.f, 450.f}, {180.f, 40.f});

    AddPlatform({2830.f, 440.f}, {170.f, 40.f});

    AddPlatform({3080.f, 360.f}, {160.f, 40.f});

    AddPlatform({3320.f, 270.f}, {160.f, 40.f});

    AddPlatform({3560.f, 380.f}, {170.f, 40.f});

    AddPlatform({3790.f, 300.f}, {180.f, 40.f});

    AddPlatform({4120.f, 300.f}, {280.f, 40.f});

    AddPlatform({4460.f, 260.f}, {170.f, 40.f});

    AddPlatform({4760.f, 510.f}, {170.f, 40.f});

    AddPlatform({5040.f, 480.f}, {220.f, 40.f});
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
                        RestartLevel(true);
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
                        RestartLevel(true);
                        state = GameState::Menu;
                    }
                }
            } else if (const auto *resize = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resize->size));
                window.setView(sf::View(visibleArea));
            }
        }

        // ============================================================================================================================



        if (state == GameState::Playing) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                RestartLevel();
            }
            accumulator += dt;
            levelTimer += dt;
            if (timerText) {
                timerText->setString(std::format("{:.2f}", levelTimer));
            }
            while (accumulator >= kTimeStep) {
                b2World_Step(world, kTimeStep, kSubSteps);
                SensorContact(world);
                accumulator -= kTimeStep;
            }

            //Update-------------------------------------------------------------------------------------------------
            player.Update(dt);
            enemy.Update(dt, camera.getCenter().x);
            winFlag.Update(dt);
            //TakeDamage---------------------------------------------------------------------------------------------
            sf::Vector2f diff = player.GetScreenPosition() - enemy.GetScreenPosition();
            if (std::hypot(diff.x, diff.y) < 95.f) {
                player.TakeDamage(3);
            }

            if (player.GetScreenPosition().y > 800.f) {
                player.TakeDamage(1);
            }

            if (player.GetCurrentHearts() <= 0) {
                window.setView(window.getDefaultView());
                state = GameState::GameOver;
            }

            if (player.GetScreenPosition().y > 800.f) {
                player.TakeDamage(1);
            }

            sf::Vector2f dif = player.GetScreenPosition() - winFlag.GetScreenPosition();

            if (std::hypot(dif.x, dif.y) < 100.f) {
                state = GameState::Win;
            }

            sf::Vector2f diffCheck = player.GetScreenPosition() - checkpointScreenPos;
            if (!checkpointActivated && std::hypot(diffCheck.x, diffCheck.y) < 80.f) {
                checkpointActivated = true;
                currentSpawnScreenPos = checkpointScreenPos;
                checkpointShape.setFillColor(sf::Color::Green);
            }

            camera.move({Platformer::SCROLLSPEED * dt, 0.f});
        }


        // ========================================================================================================================================

        window.clear(sf::Color::Black);


        if (state == GameState::GameOver) {
            gameOver.Draw(window);
        }
        if (state == GameState::Win) {
            window.setView(window.getDefaultView());
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
            window.draw(checkpointShape);

            window.setView(sf::View(healthV));
            // health.DrawHealth(window);
            if (timerText) {
                window.draw(*timerText);
            }
            window.setView(sf::View(camera));
            player.Draw(window);
            enemy.Draw(window);


        }


        window.display();
    }
}
