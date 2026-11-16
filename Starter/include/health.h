//
// Created by Agatha on 16.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_HEALTH_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_HEALTH_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Health {
  sf::Font font_h;
  std::optional<sf::Text> life;

  std::optional<sf::Sprite> health;
  sf::Texture heart;
  sf::Texture mid_heart;



  public:
  Health();
  void Initialize();
  void DrawHealth(sf::RenderWindow& window);


};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_HEALTH_H
