//
// Created by Agatha on 04.11.2026.
//
#include <print>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "C:\Users\Utilisateur\Projets_SAE_C++\sfml\Starter\include\player.h"



void Player::Play() {

    //SPRITE and SOUND --------------------------------------------------------------------

    texture.loadFromFile("../../Starter/ressources/character_purple_front.png");
    buffer.loadFromFile("../../Starter/sounds/footstep_grass_000.ogg");

    sound = sf::Sound(buffer);

    character = sf::Sprite(texture);
    if (character) {
        character->setTexture(texture);
        character->setPosition({200, 200});
        character->setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});
    }

}



void Player::Update() {

    //Movement logic ----------------------------------------------------

    moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        moving = true;
        character->move({-2, 0});
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        moving = true;
        character->move({2, 0});
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
        moving = true;
        character->move({0, -2});
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
        moving = true;
        character->move({0, 2});
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

    if (moving) {
        if (sound->getStatus() != sf::SoundSource::Status::Playing) {
            sound->play();
        }
    }
    else {
        if (sound->getStatus() == sf::SoundSource::Status::Playing) {
            sound->stop();
        }
    }

}
// Character draw in screen-----------------------------------------------------------

void Player::Draw(sf::RenderWindow& window) {

    if (character.has_value()) {
        window.draw(character.value());
    }
}

