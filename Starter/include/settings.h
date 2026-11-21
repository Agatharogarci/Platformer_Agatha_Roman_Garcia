//
// Created by Agatha on 19.11.2026.
//

#pragma once
#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_SETTINGS_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_SETTINGS_H
#include <SFML/System/Vector2.hpp>

namespace Platformer {
    inline constexpr float GRAVITY = 50.f;

    inline constexpr float JUMP_VELOCITY = -30.f;
    inline constexpr float RUNNINGSPEED = 25.f;

    inline constexpr float SCROLLSPEED = 300.f;

    inline constexpr sf::Vector2u WINDOW_SIZE = {960, 775};
    inline constexpr sf::Vector2f CHECK_POINT_POS = {960, 775};
}



#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_SETTINGS_H
