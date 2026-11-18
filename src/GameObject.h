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
	std::unique_ptr<sf::Texture> texture;
	bool isActive = true;
};
