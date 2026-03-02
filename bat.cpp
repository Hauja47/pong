#include "bat.h"

Bat::Bat(float startX, float startY) {
  this->m_position.x = startX;
  this->m_position.y = startY;

  this->m_shape.setSize(sf::Vector2f(50, 5));
  this->m_shape.setPosition(m_position);
}

sf::FloatRect Bat::getGlobalBounds() { return this->m_shape.getGlobalBounds(); }

sf::RectangleShape Bat::getShape() { return m_shape; }

void Bat::moveLeft() { this->m_movingLeft = true; }
void Bat::moveRight() { this->m_movingRight = true; }
void Bat::stopLeft() { this->m_movingLeft = false; }
void Bat::stopRight() { this->m_movingRight = false; }

void Bat::update(sf::Time dt) {
  if (m_movingLeft) {
    this->m_position.x -= m_speed * dt.asSeconds();
  }

  if (m_movingRight) {
    this->m_position.x += m_speed * dt.asSeconds();
  }

  this->m_shape.setPosition(this->m_position);
}