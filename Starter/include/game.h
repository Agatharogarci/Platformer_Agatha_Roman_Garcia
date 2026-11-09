//
// Created by Agatha on 29.10.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <optional>
#include "player.h"

class Game {
    sf::RenderWindow window;
    std::optional<sf::Sprite> sprite;
    sf::Texture texture;

    Player player;

    b2WorldId world;
    float accumulator = 0.0f;
    static constexpr float kTimeStep = 1.0f / 60.0f;
    static constexpr float kSubSteps = 4.f;


    public:
    Game() = default;
    ~Game();
    void Initialize();
    void Run();

};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
