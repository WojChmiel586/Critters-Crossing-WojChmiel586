#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject
{
public:
	GameObject();
	~GameObject() = default;

	sf::Sprite& GetSprite();



private:
	std::unique_ptr<sf::Sprite> sprite;
	bool isActive = true;
};
