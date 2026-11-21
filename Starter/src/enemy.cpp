//
// Created by Agatha on 10.11.2026.
//
#include <print>
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
    }
}


void Enemy::SetupPhysics(b2WorldId world, b2Vec2 startPos) {
    sf::Vector2u size = saw_a.getSize();
    b2Vec2 halfSize = {
        Conversions::ScreenToPhysics(size.x / 2.f),
        Conversions::ScreenToPhysics(size.y / 2.f)
    };

    physics.SetupCircle(world, b2_kinematicBody, startPos, halfSize);

    hitSensor.Setup(physics.GetBodyId(), {halfSize.x + 0.05f, halfSize.y + 0.05f});

}

void Enemy::Update(float dt, float cameraCenterX) {
    //Movement logic
    b2Vec2 physicPos = physics.GetPosition();
    float screenX = Conversions::PhysicsToScreen(physicPos.x);
    float screenY = Conversions::PhysicsToScreen(physicPos.y);

    float leftEdge  = cameraCenterX - 440.f;
    float rightEdge = cameraCenterX + 440.f;


    if (screenX >= rightEdge) {
        speed = -std::abs(speed);
    }
    else if (screenX <= leftEdge) {
        speed = std::abs(speed);
    }

    
    if (screenY >= 680.f) {
        speedY = -std::abs(speedY);
    }
    else if (screenY <= 150.f) {
        speedY = std::abs(speedY);
    }

    physics.SetVelocity({speed, speedY});

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
