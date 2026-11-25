#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class AnimatedSprite

{

public:

	AnimatedSprite(std::string filename, sf::Vector2u frame_size, int padding = 0);
	AnimatedSprite(sf::Texture& texture, sf::Vector2u frame_size, int padding = 0);

	sf::Sprite& GetSprite()						{ return _sprite; };
	void SetFrameSize(const sf::Vector2u& size) { _frameSize = size; };
	const sf::Vector2u& GetFrameSize()			{ return _frameSize; };
	const bool& IsPlaying()						{ return _isPlaying; };

	void Update(const float& dt);
	void Render(sf::RenderWindow& window);

	void Play();
	void Stop();
	void Pause();
	void Resume();

	//public variables
	int _playbackRate = 12;

private:

	//private functions
	void MoveSpriteFrame();
	std::vector<sf::IntRect> CalculateFrames();

	//Texture and Sprite
	sf::Texture _texture;
	sf::Sprite _sprite;

	unsigned int _frameIt = 0;
	unsigned int _frameCount = 0;
	unsigned int _padding = 0;
	sf::Vector2u _frameSize;
	std::vector<sf::IntRect> _frames;

	bool _isPlaying = true;
	float _playbackTimer = 0.0f;


};
