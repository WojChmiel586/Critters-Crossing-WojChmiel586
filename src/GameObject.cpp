#include "GameObject.h"

GameObject::GameObject()
{
	sprite = std::make_unique<sf::Sprite>();
}

sf::Sprite& GameObject::GetSprite()
{
	return *sprite;
}
