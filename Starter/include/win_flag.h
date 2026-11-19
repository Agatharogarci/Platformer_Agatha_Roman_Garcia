//
// Created by Agatha on 19.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_WIN_FLAG_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_WIN_FLAG_H

#include <SFML/Graphics.hpp>
#include "physical_object.h"
#include "sensor.h"

class WinFlag {
    std::optional<sf::Sprite> win_flag;
    sf::Texture flag_a;
    sf::Texture flag_b;

    PhysicalObject physics;
    Sensor hitSensor;

    float animation_timer = 0.f;
    bool current_frame = false;

    public:

    WinFlag();
    bool isTouchingPlayer() const {return hitSensor.HasTouched;};
    void SetupPhysics(b2WorldId world, b2Vec2 startPos);
    sf::Vector2f GetScreenPosition() const {return win_flag->getPosition();};
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_WIN_FLAG_H
