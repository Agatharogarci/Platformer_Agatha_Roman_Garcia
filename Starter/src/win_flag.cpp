//
// Created by Agatha on 19.11.2026.
//
#include <print>
#include <SFML/Graphics.hpp>
#include "../../Starter\include\constants.h"
#include "../../Starter\include\win_flag.h"

WinFlag::WinFlag() :
flag_a("../../Starter/ressources/flag_yellow_a.png"),
flag_b("../../Starter/ressources/flag_yellow_b.png")
{
    win_flag.emplace(flag_a);
    if (win_flag) {
        win_flag->setOrigin({flag_a.getSize().x / 2.f, flag_a.getSize().y / 2.f});
    }

}

void WinFlag::SetupPhysics(b2WorldId world, b2Vec2 startPos) {
    sf::Vector2u size = flag_a.getSize();
    b2Vec2 halfSize = {
        Conversions::ScreenToPhysics(size.x / 2.f),
        Conversions::ScreenToPhysics(size.y / 2.f)
    };

    physics.Setup(world, b2_staticBody, startPos, halfSize);

    hitSensor.Setup(physics.GetBodyId(), {halfSize.x + 0.05f, halfSize.y + 0.05f});
}

void WinFlag::Update(float dt) {
    b2Vec2 physicPos = physics.GetPosition();
    float screenX = Conversions::PhysicsToScreen(physicPos.x);

    animation_timer += dt;

    if (animation_timer >= 0.08) {
        animation_timer -= 0.08f;
        current_frame = !current_frame;
        win_flag->setTexture(current_frame ? flag_a : flag_b, false);
    }
}

void WinFlag::Draw(sf::RenderWindow& window) {

    if (win_flag.has_value()) {
        window.draw(win_flag.value());
    }
}


