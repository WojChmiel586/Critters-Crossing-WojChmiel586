
#include "Game.h"
#include <iostream>
#include <math.h>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete dragged;
}

bool Game::init()
{
	character = std::make_unique<GameObject>();
	passport = std::make_unique<GameObject>();




	//Construct Texture and load data from file
	texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile("../Data/Critter Crossing Customs/elephant passport.png"))
	{
		//Texture failed to load
	}
	//Construct Sprite using the Texture as parameter
	sprite = std::make_unique<sf::Sprite>(*texture);

	//Construct SoundBuffer and load data from file
	soundBuffer = std::make_unique<sf::SoundBuffer>();
	if (!soundBuffer->loadFromFile("../Data/Audio/SFX/metalClick.ogg"))
	{
		//One-shot failed to load
	}
	//Construct Sound using the Sound buffer as parameter
	sound = std::make_unique<sf::Sound>(*soundBuffer);

	music = std::make_unique<sf::Music>();
	if (!music->openFromFile("../Data/Audio/Path to Lake Land.ogg"))
	{
		//Music failed to load
	}

	if(!ninjaTex.loadFromFile("../Data/Images/ninja-walk-side.png"))
	{
		std::cout << "failed to load ninja texture";
	}

	ninja = std::make_unique<AnimatedSprite>(ninjaTex, sf::Vector2u{224, 224});

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

	background_tex = std::make_unique<sf::Texture>();
	if (!background_tex->loadFromFile("../Data/Critter Crossing Customs/background.png"))
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	background = std::make_unique<sf::Sprite>(*background_tex);


  return true;
}

void Game::update(float dt)
{
	if (dragged != nullptr)
	{
		dragSprite(*dragged);
	}

	ninja->Update(dt);
}

void Game::render()
{
	window.draw(*background);
	window.draw(character->GetSprite());
	window.draw(passport->GetSprite());

	ninja->Render(window);
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	std::cout << "Mouse Button Pressed" << std::endl;
	if (event->button == sf::Mouse::Button::Left)
	{
		//We play the one click sound when left mouse button is pressed
		sound->play();

		sf::Vector2i click = event->position;
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);
		dragged = nullptr;
		if (passport->GetSprite().getGlobalBounds().contains(clickf))
		{
			dragged = &passport->GetSprite();
		}
		if (ninja->GetSprite().getGlobalBounds().contains(clickf))
		{
			dragged = &ninja->GetSprite();
		}

		if (dragged != nullptr)
		{
			drag_offset = dragged->getPosition() - clickf;
		}

	}
}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	std::cout << "Mouse Button Released" << std::endl;
	dragged = nullptr;
}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	if (event->scancode == sf::Keyboard::Scancode::Up)
	{
		ninja->_playbackRate = std::clamp<int>(ninja->_playbackRate + 1, 0, 165);
	}
	if (event->scancode == sf::Keyboard::Scancode::Down)
	{
		ninja->_playbackRate = std::clamp<int>(ninja->_playbackRate - 1, 0, 165);
	}
	if (event->scancode == sf::Keyboard::Scancode::P)
	{
		//ninja->IsPlaying() ? ninja->Pause() : ninja->Resume();
		music->play();
	}
	if (event->scancode == sf::Keyboard::Scancode::S)
	{
		//ninja->IsPlaying() ? ninja->Pause() : ninja->Resume();
		music->stop();
	}

	if (event->scancode == sf::Keyboard::Scancode::T)
	{
		ninja->IsPlaying() ? ninja->Stop() : ninja->Play();
	}


}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}

void Game::dragSprite(sf::Sprite& sprite)
{
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

	sf::Vector2f drag_position = mouse_positionf + drag_offset;
	sprite.setPosition({ drag_position.x, drag_position.y });
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
	character->GetSprite().setScale({ 1.8f, 1.8f });
	character->GetSprite().setPosition({ window.getSize().x / 12.0f, window.getSize().y / 12.0f });

	passport->GetSprite().setTexture(*passports[passport_index], true);
	passport->GetSprite().setScale({ 0.6, 0.6 });
	passport->GetSprite().setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
}


