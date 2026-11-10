//
// Created by Agatha on 10.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_ENEMY_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_ENEMY_H
#include <SFML/Graphics.hpp>
#include "physical_object.h"
class Enemy {
    std::optional<sf::Sprite> enemy;
    sf::Texture saw_a;
    sf::Texture saw_b;

    PhysicalObject physics;
    public:
    void SetupPhysicsM(b2WorldId world, b2Vec2 startPos);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_ENEMY_H
