//
// Created by Agatha on 11.11.2026.
//
#pragma once

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_MENU_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_MENU_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>

enum class MenuAction {
  None,
  Play,
  Quit
};

class Menu {
  sf::Font font;
  std::optional<sf::Text> titleText;
  std::optional<sf::Text> playText;
  std::optional<sf::Text> quitText;

  int selectedIndex = 0;

  void UpdateTextColors();

public:
  Menu() = default;
  bool Initialize();
  MenuAction HandleInput(const sf::Event::KeyPressed& key);
  void Draw(sf::RenderWindow& window);
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_MENU_H
