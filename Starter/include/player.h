//
// Created by Agatha on 04.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "physical_object.h"
#include "sensor.h"

class Player {
    std::optional<sf::Sprite> character;
    sf::Texture purple_front;
    sf::Texture purple_jump;
    sf::Texture purple_walk_a;
    sf::Texture purple_walk_b;

    bool moving = false;

    float animation_timer = 0.0f;
    const float frame_duration = 0.15f;
    static constexpr float Y_VELOCITY = -25.f;
    bool current_walk_frame = false;

    sf::SoundBuffer buffer;
    std::optional<sf::Sound> sound;

    PhysicalObject physics;
    Sensor grounded;

public:

    Player();
    void SetupPhysics(b2WorldId world, b2Vec2 startPos);
    void Jump();
    void Update(float dt);


    void Draw(sf::RenderWindow&);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
