//
// Created by Agatha on 11.11.2026.
//
#include <print>
#include "../include/menu.h"

bool Menu::Initialize() {

    if (!font.openFromFile("../../Starter/ressources/BAUHS93.TTF")) {
        std::println("failed to load font");
        return false;
    }
    titleText.emplace(font, "PLATFORMER", 75);
    titleText->setFillColor(sf::Color::Yellow);
    titleText->setPosition({275.f, 180.f});

    playText.emplace(font, "Play", 50);
    playText->setPosition({440.f, 360.f});

    quitText.emplace(font, "Quit", 40);
    quitText->setPosition({440.f, 440.f});

    return true;
}

void Menu::UpdateTextColors() {
    if (playText && quitText) {
        playText->setFillColor(selectedIndex == 0 ? sf::Color::Green : sf::Color::White);
        quitText->setFillColor(selectedIndex == 1 ? sf::Color::Green : sf::Color::White);
    }
}


MenuAction Menu::HandleInput(const sf::Event::KeyPressed& key) {
    if (key.scancode == sf::Keyboard::Scan::Up || key.scancode == sf::Keyboard::Scan::Down) {
        selectedIndex = 1 - selectedIndex;
        UpdateTextColors();
    }
    else if (key.scancode == sf::Keyboard::Scan::Enter || key.scancode == sf::Keyboard::Scan::Space) {
        return (selectedIndex == 0) ? MenuAction::Play : MenuAction::Quit;
    }

    return MenuAction::None;
}


void Menu::Draw(sf::RenderWindow& window) {
    if (titleText) {
        window.draw(*titleText);
    }else {
        std::println("titleText is empty");
    }
    if (playText){ window.draw(*playText);}
    if (quitText) { window.draw(*quitText);}
}