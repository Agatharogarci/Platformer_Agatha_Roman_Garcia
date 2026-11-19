//
// Created by Agatha on 29.10.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "menu.h"
#include "game_over.h"
#include "player.h"
#include "enemy.h"
#include "health.h"
#include "win.h"
#include "win_flag.h"

struct Platform {
    sf::RectangleShape shape;
    PhysicalObject physics;
};

enum class GameState {
    Menu,
    Playing,
    GameOver,
    Win
};
class Game {

    sf::RenderWindow window;
    sf::View camera;
    sf::View healthV;
    std::optional<sf::Sprite> sprite;
    sf::Texture texture;

    Player player;
    Enemy enemy;
    Health health;


    sf::Texture groundTexture;
    std::vector<std::unique_ptr<Platform>> platforms;
    void AddPlatform(sf::Vector2f screenPos, sf::Vector2f screenSize);


    b2WorldId world = b2_nullWorldId;
    float accumulator = 0.0f;
    static constexpr float kTimeStep = 1.0f / 60.0f;
    static constexpr int kSubSteps = 4;

    GameState state = GameState::Menu;
    Menu menu;
    GameOver gameOver;
    Win win;
    WinFlag winFlag;


    public:
    Game() = default;
    ~Game();
    void RestartLevel();
    void Initialize();
    void Run();

};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
