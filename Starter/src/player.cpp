//
// Created by Agatha on 04.11.2026.
//
#include <print>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "C:\Users\Utilisateur\Projets_SAE_C++\sfml\Starter\include\player.h"



void Player::Play() {
    //SPRITE and SOUND
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