
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
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);
  void dragSprite(sf::Sprite& sprite);

  void newAnimal();

 private:
  sf::RenderWindow& window;
  std::unique_ptr<sf::Sprite> draggable;

  std::unique_ptr<GameObject> character;
  std::unique_ptr<GameObject> passport;


  std::unique_ptr<sf::Sprite> background;
  std::unique_ptr<sf::Texture> background_tex;

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
