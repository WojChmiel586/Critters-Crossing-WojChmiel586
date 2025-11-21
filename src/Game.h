
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

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
  void mouseButtonReleased(sf::Event event);
  void keyPressed(sf::Event event);
  void dragSprite(sf::Sprite& sprite);

  void newAnimal();

 private:
  sf::RenderWindow& window;
  sf::Sprite draggable;

  std::unique_ptr<GameObject> character;
  std::unique_ptr<GameObject> passport;

  std::vector<std::unique_ptr<sf::Texture>> animals;
  std::vector<std::unique_ptr<sf::Texture>> passports;

  //sf::Sprite dragged;

  bool dragging = false;
  bool passport_accepted = false;
  bool passport_rejected = false;
  bool should_accept = false;

  sf::Vector2f drag_offset;
};

#endif // PLATFORMER_GAME_H
