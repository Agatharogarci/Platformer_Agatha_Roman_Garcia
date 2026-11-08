//
// Created by Agatha on 04.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
    std::optional<sf::Sprite> character;
    sf::Texture purple_front;
    sf::Texture purple_jump;
    sf::Texture purple_walk_a;
    sf::Texture purple_walk_b;

    bool moving = false;

    sf::SoundBuffer buffer;
    std::optional<sf::Sound> sound;

    // sf::Window window;
public:

    Player();
    void Update(float dt);
    void Draw(sf::RenderWindow&);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
