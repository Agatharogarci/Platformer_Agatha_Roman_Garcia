//
// Created by Agatha on 17.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_OVER_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_OVER_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>



enum class GameOverAction {
    Retry,
    MainMenu,
    Quit,
    None
};
class GameOver {
    sf::Font font;
    std::optional<sf::Text> retryText;
    std::optional<sf::Text> mainMenuText;
    std::optional<sf::Text> quitText;

    int selectedIndex = 0;

    void UpdateTextColors();

public:
    GameOver() = default;
    bool Initialize();
    GameOverAction HandleInput(const sf::Event::KeyPressed& key);
    void Draw(sf::RenderWindow& window);

};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_GAME_OVER_H
