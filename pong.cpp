#include "pong.h"

using namespace sf;

int main() {
  VideoMode vm({SCREEN_WIDTH, SCREEN_HEIGHT});
  RenderWindow window(vm, "Pong", Style::Default);

  int score = 0;
  int lives = 3;

  bool isCollide = false;

  Bat bat(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);

  Ball ball(SCREEN_WIDTH / 2, 0);

  Font font("assets/fonts/DepartureMono-Regular.otf");

  Text hud(font, "");
  hud.setCharacterSize(static_cast<int>(SCREEN_HEIGHT * 0.08));
  hud.setFillColor(Color::White);
  hud.setPosition({20, 20});

  Clock clock;

  while (window.isOpen()) {
    /*
    Handle the player input
    ****************************
    ****************************
    ****************************
    */
    while (const std::optional event = window.pollEvent()) {
      if (event->is<Event::Closed>()) {
        window.close();
      } else if (const auto *keyPressed = event->getIf<Event::KeyPressed>()) {
        if (keyPressed->scancode == Keyboard::Scancode::Escape)
          window.close();
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Scancode::A) ||
        Keyboard::isKeyPressed(Keyboard::Scancode::Left)) {
      if (bat.getGlobalBounds().position.x > 0)
        bat.moveLeft();
    } else {
      bat.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::Scancode::D) ||
        Keyboard::isKeyPressed(Keyboard::Scancode::Right)) {
      if (bat.getGlobalBounds().position.x + bat.getGlobalBounds().size.x <
          static_cast<float>(window.getSize().x))
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

    if (ball.getGlobalBounds().position.y >
        static_cast<float>(window.getSize().y)) {
      ball.reboundBottom();

      lives--;

      if (lives < 1) {
        score = 0;
        lives = 3;
      }
    }

    if (ball.getGlobalBounds().position.y < 0) {
      ball.reboundBatOrTop();
    }

    if (ball.getGlobalBounds().position.x < 0 ||
        ball.getGlobalBounds().position.x + ball.getGlobalBounds().size.x >
            static_cast<float>(window.getSize().x)) {
      ball.reboundSides();
    }

    if (const std::optional intersection =
            ball.getGlobalBounds().findIntersection(bat.getGlobalBounds())) {
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
