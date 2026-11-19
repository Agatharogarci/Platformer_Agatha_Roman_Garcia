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
    // Sprites for character----------------------------------------------------------
    std::optional<sf::Sprite> character;
    sf::Texture purple_front;
    sf::Texture purple_jump;
    sf::Texture purple_walk_a;
    sf::Texture purple_walk_b;

    // Character logic-----------------------------------------------------------------
     bool moving = false;
    int hearts = 3;
    int currentHearts = 3;
    float invincibilityDuration = 1.5f;
    float invincibilityTimer = 0.f;
    bool isInvincible = false;

    //Character Animations-----------------------------------------------------------
    float animation_timer = 0.0f;
    const float frame_duration = 0.15f;
    static constexpr float Y_VELOCITY = -25.f;
    bool current_walk_frame = false;

    //Character sounds--------------------------------------------------------------
    sf::SoundBuffer buffer;
    std::optional<sf::Sound> sound;

    //Character physics-------------------------------------------------------------
    PhysicalObject physics;
    Sensor grounded;

public:

    Player();
    void SetupPhysics(b2WorldId world, b2Vec2 startPos);
    void Jump();
    void TakeDamage(int amount);
    sf::Vector2f GetScreenPosition() const;
    void Update(float dt);
    int GetCurrentHearts() const { return currentHearts; }
    void Reset(b2Vec2 startPos);
    void Draw(sf::RenderWindow&);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_PLAYER_H
