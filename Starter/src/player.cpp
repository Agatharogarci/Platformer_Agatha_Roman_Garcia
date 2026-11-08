//
// Created by Agatha on 04.11.2026.
//
#include <print>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "..\..\Starter\include\player.h"


Player::Player()
:
    purple_front("../../Starter/ressources/character_purple_front.png"),
    purple_jump("../../Starter/ressources/character_purple_jump.png"),
    purple_walk_a("../../Starter/ressources/character_purple_walk_a.png"),
    purple_walk_b("../../Starter/ressources/character_purple_walk_b.png")

{

    //SPRITE and SOUND --------------------------------------------------------------------


    buffer.loadFromFile("../../Starter/sounds/footstep_grass_000.ogg");

    sound = sf::Sound(buffer);

    character.emplace(purple_front);
    if (character) {

        character->setOrigin({purple_front.getSize().x / 2.f, purple_front.getSize().y / 2.f});
        character->setPosition({200, 200});
    }

}



void Player::Update(float dt) {
    std::println("dt : {}",dt);

    //Movement logic ----------------------------------------------------

    moving = false;
    float Speed = 200.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        moving = true;
        character->move({-Speed * dt, 0.f});
        // character->setTexture(purple_walk_a, true);
        //
        // character->setTexture(purple_walk_b, true);
        character->setScale({-1, 1});
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        moving = true;
        character->move({Speed * dt, 0});
    }


    //Movement logic with controller -------------------------------------------------------

    const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
    if (std::abs(y) > 20.f) {
        character->move({0, y / 100 * 5});
    }

    const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
    if (std::abs(x) > 20.f) {
        character->move({x / 100 * 5, 0});
    }

    //Sound logic-----------------------------------------------------------------

    // if (moving) {
    //     if (sound->getStatus() != sf::SoundSource::Status::Playing) {
    //         sound->setPitch(0.90f);
    //         sound->play();
    //     }
    // }
    // else {
    //     if (sound->getStatus() == sf::SoundSource::Status::Playing) {
    //         sound->stop();
    //     }
    // }

}
// Character draw in screen-----------------------------------------------------------

void Player::Draw(sf::RenderWindow& window) {

    if (character.has_value()) {
        window.draw(character.value());
    }
}

