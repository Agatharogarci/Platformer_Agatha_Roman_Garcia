//
// Created by Agatha on 04.11.2026.
//
#include <print>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "..\..\Starter\include\player.h"
#include "..\..\Starter\include\constants.h"


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

void Player::SetupPhysics(b2WorldId world, b2Vec2 startPos) {
    sf::Vector2u size = purple_front.getSize();
    b2Vec2 halfSize = {
        Conversions::ScreenToPhysics(size.x / 2.f),
        Conversions::ScreenToPhysics(size.y / 2.f)
    };

    physics.Setup(world, b2_dynamicBody, startPos, halfSize);
    grounded.Setup(physics.GetBodyId(), halfSize);
}

void Player::Jump() {
    if (grounded.HasTouched) {

        std::println("Jump");
        float xVelocity = physics.GetVelocity().x;
        physics.SetVelocity({xVelocity, Y_VELOCITY });
    }
}



void Player::Update(float dt) {


    //Movement logic ----------------------------------------------------

    moving = false;
    float targetVx = 0.0f;
    const float runSpeed = 12.0f;


if (!sf::Joystick::isConnected(0)) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        moving = true;
        targetVx = -runSpeed;
        character->setScale({-1, 1});
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        moving = true;
        targetVx = runSpeed;
        character->setScale({1, 1});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        Jump();
    }
}
    //Movement logic with controller -------------------------------------------------------

    const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
    if (std::abs(x) > 20.f) {
        moving = true;
        targetVx = (x / 100.f) * runSpeed;



        if (x < 0.f) {
            character->setScale({-1, 1});
        }else {
            character->setScale({1, 1});
        }
    }
    if (sf::Joystick::isButtonPressed(0,1)) {
        Jump();
    }

    b2Vec2 currentVelocity = physics.GetVelocity();


    if (currentVelocity.y > 0.1f) {
        physics.SetGravityScale(2.f);
    } else {
        physics.SetGravityScale(1.0f);
    }

    physics.SetVelocity({targetVx, currentVelocity.y});
    physics.SetVelocity({targetVx,currentVelocity.y});

    b2Vec2 physicPosition = physics.GetPosition();
    character->setPosition({
    Conversions::PhysicsToScreen(physicPosition.x),
    Conversions::PhysicsToScreen(physicPosition.y)});

    //Sound and Animation logic-----------------------------------------------------------------

    if (moving && grounded.HasTouched) {
        animation_timer += dt;

        if (animation_timer >= frame_duration) {
            animation_timer -= frame_duration;
            current_walk_frame = !current_walk_frame;
        }
        if (current_walk_frame) {
            character->setTexture(purple_walk_a, false);
        }else {
            character->setTexture(purple_walk_b, false);
        }
        if (sound.has_value() && sound->getStatus() != sf::SoundSource::Status::Playing && grounded.HasTouched) {
            sound->setPitch(0.90f);
            sound->play();
        }
    }
    else {
        character->setTexture(purple_front, true);
        if (sound->getStatus() == sf::SoundSource::Status::Playing) {
            sound->stop();

        }
        else if (!grounded.HasTouched) {
            character->setTexture(purple_jump, true);
        }
    }

}



// Character draw in screen-----------------------------------------------------------

void Player::Draw(sf::RenderWindow& window) {

    if (character.has_value()) {
        window.draw(character.value());
    }
}

