
#include "ball.h"
#include "bat.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <sstream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1024

using namespace sf;

int main() {
  VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
  RenderWindow window(vm, "Pong", Style::Default);

  int score = 0;
  int lives = 3;

  Bat bat(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);

  Ball ball(SCREEN_WIDTH / 2, 0);

  Text hud;

  Font font;
  font.loadFromFile("assets/fonts/DepartureMono-Regular.otf");

  hud.setFont(font);
  hud.setCharacterSize(75);
  hud.setFillColor(Color::White);
  hud.setPosition(20, 20);

  Clock clock;

  while (window.isOpen()) {
    /*
    Handle the player input
    ****************************
    ****************************
    ****************************
    */
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::A)) {
      bat.moveLeft();
    } else {
      bat.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::D)) {
      bat.moveRight();
    } else {
      bat.stopRight();
    }

    /*
    Update the bat, the ball and the HUD
    *****************************
    *****************************
    *****************************
    */
    Time dt = clock.restart();

    bat.update(dt);
    ball.update(dt);

    std::stringstream ss;
    ss << "Score: " << score << " | Live: " << lives;
    hud.setString(ss.str());

    if (ball.getPosition().top > window.getSize().y) {
      ball.reboundBottom();

      lives--;

      if (lives < 1) {
        score = 0;
        lives = 3;
      }
    }

    if (ball.getPosition().top < 0) {
      ball.reboundBatOrTop();
    }

    if (ball.getPosition().left < 0 ||
        ball.getPosition().left + ball.getPosition().width >
            window.getSize().x) {
      ball.reboundSides();
    }

    if (ball.getPosition().intersects(bat.getPosition())) {
      score++;
      ball.reboundBatOrTop();
    }

    /*
    Draw the bat, the ball and the HUD
    *****************************
    *****************************
    *****************************
    */
    window.clear();
    window.draw(hud);
    window.draw(bat.getShape());
    window.draw(ball.getShape());
    window.display();
  }

  return 0;
}
