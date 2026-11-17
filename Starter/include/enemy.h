//
// Created by Agatha on 10.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_ENEMY_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_ENEMY_H
#include <SFML/Graphics.hpp>
#include "physical_object.h"
#include "sensor.h"
class Enemy {
    std::optional<sf::Sprite> enemy;
    sf::Texture saw_a;
    sf::Texture saw_b;

    PhysicalObject physics;
    Sensor hitSensor;

    float speed = 5.0f;
    float animation_timer = 0.f;
    bool current_frame = false;

    public:


    Enemy();
    bool isTouchingPlayer() const {return hitSensor.HasTouched;}
    void SetupPhysicsM(b2WorldId world, b2Vec2 startPos);
    sf::Vector2f GetScreenPosition() const { return enemy->getPosition(); }
    void UpdateSaw(float dt);
    void Draw(sf::RenderWindow& window);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_ENEMY_H
