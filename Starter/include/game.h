//
// Created by Agatha on 29.10.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <optional>

#include "menu.h"
#include "game_over.h"
#include "player.h"
#include "enemy.h"
#include "health.h"

enum class GameState {
    Menu,
    Playing,
    GameOver
};
class Game {

    sf::RenderWindow window;
    std::optional<sf::Sprite> sprite;
    sf::Texture texture;

    Player player;
    Enemy enemy;
    Health health;

    PhysicalObject groundPhysics;
    sf::Texture groundTexture;
    sf::RectangleShape groundShape;

    b2WorldId world = b2_nullWorldId;
    float accumulator = 0.0f;
    static constexpr float kTimeStep = 1.0f / 60.0f;
    static constexpr int kSubSteps = 4;

    GameState state = GameState::Menu;
    Menu menu;
    GameOver gameOver;


    public:
    Game() = default;
    ~Game();
    void RestartLevel();
    void Initialize();
    void Run();

};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
