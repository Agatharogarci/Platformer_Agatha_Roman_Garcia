//
// Created by Agatha on 29.10.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
#include <SFML/Graphics.hpp>
#include <optional>

class Game {
    sf::RenderWindow window;
    std::optional<sf::Sprite> sprite;
    sf::Texture texture;

    public:
    void Initialize();
    void Run();

};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_H
