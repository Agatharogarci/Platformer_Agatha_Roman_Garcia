//
// Created by Agatha on 04.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
    std::optional<sf::Sprite> character;
    sf::Texture texture;

    bool moving = false;

    sf::SoundBuffer buffer;
    std::optional<sf::Sound> sound;

    sf::Window window;
public:

    void Play();
    void Update();
    void Draw(sf::RenderWindow&);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
