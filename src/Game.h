
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseButtonPressed(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  sf::RenderWindow& window;
  std::unique_ptr<sf::Sprite> test = std::make_unique<sf::Sprite>();
  sf::Sprite draggable;
};

#endif // PLATFORMER_GAME_H
