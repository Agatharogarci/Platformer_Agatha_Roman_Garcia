//
// Created by Agatha on 10.11.2026.
//
#include <print>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "..\..\Starter\include\constants.h"
#include "../include/enemy.h"

Enemy::Enemy() :
    saw_a("../../Starter/ressources/saw_a.png"),
    saw_b("../../Starter/ressources/saw_b.png")
{
    enemy.emplace(saw_a);
    if (enemy) {
        enemy->setOrigin({saw_a.getSize().x / 2.f, saw_a.getSize().y / 2.f});
        enemy->setPosition({400, 675});
    }
}


void Enemy::SetupPhysicsM(b2WorldId world, b2Vec2 startPos) {
    sf::Vector2u size = saw_a.getSize();
    b2Vec2 halfSize = {
        Conversions::ScreenToPhysics(size.x / 2.f),
        Conversions::ScreenToPhysics(size.y / 2.f)
    };

    physics.SetupCircle(world, b2_kinematicBody, startPos, halfSize);

}

void Enemy::UpdateSaw(float dt) {
    //Movement logic
    b2Vec2 physicPos = physics.GetPosition();
    float screenX = Conversions::PhysicsToScreen(physicPos.x);

    if (screenX >= 760.f) {
        speed = -std::abs(speed);
    }
    else if (screenX <= 200.f) {
        speed = std::abs(speed);
    }
    physics.SetVelocity({speed, 0.f});

    //Sync animation and Box2d
    if (enemy.has_value()) {
        enemy->setPosition({Conversions::PhysicsToScreen(physicPos.x),
            Conversions::PhysicsToScreen(physicPos.y)});
    }

    //Animation logic--------------------

    animation_timer += dt;

    if (animation_timer >= 0.08f) {
        animation_timer -= 0.08f;
        current_frame = !current_frame;
        enemy->setTexture(current_frame ? saw_a : saw_b, false);
    }
}

void Enemy::Draw(sf::RenderWindow &window) {

    if (enemy.has_value()) {
        window.draw(enemy.value());
    }
}
