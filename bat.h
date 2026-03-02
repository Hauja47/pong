#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Bat {
private:
  sf::Vector2f m_position;
  sf::RectangleShape m_shape;
  float m_speed = 1000.0f;
  bool m_movingLeft = false;
  bool m_movingRight = false;

public:
  Bat(float startX, float startY);
  sf::FloatRect getGlobalBounds();
  sf::RectangleShape getShape();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  void moveLeft();
  void moveRight();
  void stopLeft();
  void stopRight();
  void update(sf::Time dt);
};