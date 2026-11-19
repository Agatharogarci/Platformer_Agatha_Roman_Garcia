//
// Created by Agatha on 19.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_WIN_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_WIN_H
#include <optional>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

enum class MenuActionWin {
    None,
    Quit,
    MainMenu
  };

class Win {
    sf::Font font;
    std::optional<sf::Text> winText;
    std::optional<sf::Text> quitText;
    std::optional<sf::Text> mainMenuText;

    int selectedIndex = 0;

    void UpdateTextColors();

public:
    Win() = default;
    bool Initialize();
    MenuActionWin HandleInput(const sf::Event::KeyPressed& key);
    void Draw(sf::RenderWindow& window);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_WIN_H
