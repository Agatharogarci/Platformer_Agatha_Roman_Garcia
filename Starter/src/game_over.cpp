//
// Created by Agatha on 17.11.2026.
//
#include <print>
#include "../../Starter/include/game_over.h"



bool GameOver::Initialize() {
    if (!font.openFromFile("../../Starter/ressources/BAUHS93.TTF")) {
        std::println("failed to load font");
        return false;
    }
    GameOverText.emplace(font, "Game Over", 75);
    GameOverText->setFillColor(sf::Color::Yellow);
    GameOverText->setPosition({300.f, 60});

    retryText.emplace(font, "Retry", 50);
    retryText->setPosition({375.f, 260.f});

    mainMenuText.emplace(font, "Main Menu", 50);
    mainMenuText->setPosition({375.f, 360.f});

    quitText.emplace(font, "Quit", 40);
    quitText->setPosition({375.f, 440.f});

    return true;
}


void GameOver::UpdateTextColors() {
    if (retryText && quitText && mainMenuText) {
        retryText->setFillColor(selectedIndex == 0 ? sf::Color::Green : sf::Color::White);
        mainMenuText->setFillColor(selectedIndex == 1 ? sf::Color::Green : sf::Color::White);
        quitText->setFillColor(selectedIndex == 2 ? sf::Color::Green : sf::Color::White);
    }
}

GameOverAction GameOver::HandleInput(const sf::Event::KeyPressed &key) {
    if (key.scancode == sf::Keyboard::Scan::Up) {
        selectedIndex = (selectedIndex - 1 + 3) % 3;
        UpdateTextColors();
    }
    else if (key.scancode == sf::Keyboard::Scan::Down) {
        selectedIndex = (selectedIndex + 1) % 3;
        UpdateTextColors();
    }
    else if (key.scancode == sf::Keyboard::Scan::Enter || key.scancode == sf::Keyboard::Scan::Space) {
        if (selectedIndex == 0) return GameOverAction::Retry;
        if (selectedIndex == 1) return GameOverAction::MainMenu;
        return GameOverAction::Quit;
    }

    return GameOverAction::None;
}

void GameOver::Draw(sf::RenderWindow &window) {
    if (retryText) {
        window.draw(*retryText);
    }else {
        std::println("retrytext is empty");
    }
    if (GameOverText) {window.draw(*GameOverText);}
    if (retryText){ window.draw(*retryText);}
    if (mainMenuText) {window.draw(*mainMenuText);}
    if (quitText) { window.draw(*quitText);}
}

