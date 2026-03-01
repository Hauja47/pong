#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Ball {
private:
  sf::Vector2f m_position;
  sf::RectangleShape m_shape;

  float m_speed = 300.0f;
  float m_directionX = 1.0f;
  float m_directionY = 1.0f;

public:
  Ball(float startX, float startY);
  sf::FloatRect getPosition();
  sf::RectangleShape getShape();
  float getXVelocity();
  void reboundSides();
  void reboundBatOrTop();
  void reboundBottom();
  void update(sf::Time dt);
};