#include "ball.h"

Ball::Ball(float startX, float startY) {
  this->m_position.x = startX;
  this->m_position.y = startY;

  this->m_shape.setSize(sf::Vector2f(10, 10));
  this->m_shape.setPosition(this->m_position);
}

sf::FloatRect Ball::getGlobalBounds() {
  return this->m_shape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape() { return this->m_shape; }

sf::Vector2f Ball::getPosition() { return this->m_shape.getPosition(); }

sf::Vector2f Ball::getSize() { return this->m_shape.getSize(); }

float Ball::getXVelocity() { return this->m_directionX; }
void Ball::reboundSides() { this->m_directionX = -this->m_directionX; }
void Ball::reboundBatOrTop() { this->m_directionY = -this->m_directionY; }
void Ball::reboundBottom() {
  this->m_position.y = 0;
  this->m_position.x = 500;
  this->m_directionY = -this->m_directionY;
}

void Ball::update(sf::Time dt) {
  this->m_position.y += this->m_directionY * m_speed * dt.asSeconds();
  this->m_position.x += this->m_directionX * m_speed * dt.asSeconds();

  this->m_shape.setPosition(m_position);
}