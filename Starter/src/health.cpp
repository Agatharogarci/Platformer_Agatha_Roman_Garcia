//
// Created by Agatha on 16.11.2026.
//
#include <print>
#include "../../Starter/include/health.h"
#include "../../Starter/include/player.h"


Health::Health()
:
heart("../../Starter/ressources/hud_heart.png"),
mid_heart("../../Starter/ressources/hud_heart_half.png")
{
    health.emplace(heart);
    health->setOrigin({heart.getSize().x / 2.f, heart.getSize().y / 2.f});
    health->setPosition({10, 5});

}


void Health::Initialize() {
    if (!font_h.openFromFile("../../Starter/ressources/BAUHS93.TTF")) {
        std::println("Erreur pas de points de vie!");
    }
    life.emplace(font_h, "3", 75);
    life->setFillColor(sf::Color::Red);
    life->setPosition({20.f, 10.f});
}

void Health::DrawHealth(sf::RenderWindow &window) {

    if (health.has_value()) {
        window.draw(health.value());
    }
    if (life) {
        window.draw(*life);
    }
    else {
        std::println("error no life draw");
    }

}

