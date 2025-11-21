
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	character = std::make_unique<GameObject>();
	passport = std::make_unique<GameObject>();

	animals.reserve(6);
	passports.reserve(6);

	//elefant; moose; penguin
	passports.emplace_back(std::make_unique<sf::Texture>());
	if (!passports.back()->loadFromFile("../Data/Critter Crossing Customs/elephant passport.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	passports.emplace_back(std::make_unique<sf::Texture>());
	if (!passports.back()->loadFromFile("../Data/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	passports.emplace_back(std::make_unique<sf::Texture>());
	if (!passports.back()->loadFromFile("../Data/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	animals.emplace_back(std::make_unique<sf::Texture>());
	if (!animals.back()->loadFromFile("../Data/Critter Crossing Customs/elephant.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	animals.emplace_back(std::make_unique<sf::Texture>());
	if (!animals.back()->loadFromFile("../Data/Critter Crossing Customs/moose.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	animals.emplace_back(std::make_unique<sf::Texture>());
	if (!animals.back()->loadFromFile("../Data/Critter Crossing Customs/penguin.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	newAnimal();
  return true;
}

void Game::update(float dt)
{
	if (dragging)
	{
		dragSprite(passport->GetSprite());
	}
}

void Game::render()
{
	window.draw(character->GetSprite());
	window.draw(passport->GetSprite());
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::mouseButtonPressed(sf::Event event)
{
	std::cout << "Mouse Button Pressed" << std::endl;
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		dragging = passport->GetSprite().getGlobalBounds().contains(clickf);

	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	std::cout << "Mouse Button Released" << std::endl;
	dragging = false;
}

void Game::keyPressed(sf::Event event)
{

}

void Game::dragSprite(sf::Sprite& sprite)
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

	sf::Vector2f drag_position = mouse_positionf;
	sprite.setPosition(drag_position.x, drag_position.y);
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->GetSprite().setTexture(*animals[animal_index], true);
	character->GetSprite().setScale(1.8, 1.8);
	character->GetSprite().setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->GetSprite().setTexture(*passports[passport_index], true);
	passport->GetSprite().setScale(0.6, 0.6);
	passport->GetSprite().setPosition(window.getSize().x / 2, window.getSize().y / 2);
}


