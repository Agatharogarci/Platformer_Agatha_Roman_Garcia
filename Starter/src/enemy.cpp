//
// Created by Agatha on 10.11.2026.
//
#include <print>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "..\..\Starter\include\constants.h"
#include "../include/enemy.h"

void Enemy::SetupPhysicsM(b2WorldId world, b2Vec2 startPos) {
    sf::Vector2u size = saw_a.getSize();
    b2Vec2 halfSize = {
        Conversions::ScreenToPhysics(size.x / 2.f),
        Conversions::ScreenToPhysics(size.y / 2.f)
    };

    physics.Setup(world, b2_kinematicBody, startPos, halfSize);

}
