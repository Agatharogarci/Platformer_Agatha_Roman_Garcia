//
// Created by Agatha on 19.11.2026.
//
#include <print>
#include "../../Starter/include/win.h"


bool Win::Initialize() {

    if (!font.openFromFile("../../Starter/ressources/BAUHS93.TTF")) {
        std::println("failed to load font");
        return false;
    }
    quitText.emplace(font, "Quit", 75);
    quitText->setPosition({275.f, 180.f});

    mainMenuText.emplace(font, "Main Menu", 50);
    mainMenuText->setPosition({440.f, 360.f});


    return true;
}

void Win::UpdateTextColors() {
    if (quitText && mainMenuText) {
        quitText->setFillColor(selectedIndex == 0 ? sf::Color::Green : sf::Color::White);
        mainMenuText->setFillColor(selectedIndex == 1 ? sf::Color::Green : sf::Color::White);
    }
}


MenuActionWin Win::HandleInput(const sf::Event::KeyPressed& key) {
    if (key.scancode == sf::Keyboard::Scan::Up || key.scancode == sf::Keyboard::Scan::Down) {
        selectedIndex = 1 - selectedIndex;
        UpdateTextColors();
    }
    else if (key.scancode == sf::Keyboard::Scan::Enter || key.scancode == sf::Keyboard::Scan::Space) {
        return (selectedIndex == 0) ? MenuActionWin::Quit : MenuActionWin::MainMenu;
    }

    return MenuActionWin::None;
}


void Win::Draw(sf::RenderWindow& window) {
    if (quitText) {
        window.draw(*quitText);
    }else {
        std::println("titleText is empty");
    }
    if (quitText){ window.draw(*quitText);}
    if (mainMenuText) { window.draw(*mainMenuText);}
}