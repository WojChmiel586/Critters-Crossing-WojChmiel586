#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class AnimatedSprite

{

public:
	// \brief Constructs animated sprite from filename string, need to provide size of single frame
	AnimatedSprite(std::string filename, sf::Vector2u frame_size, int padding = 0);

	// \brief Constructs animated sprite from texture reference, need to provide size of single frame
	AnimatedSprite(sf::Texture& texture, sf::Vector2u frame_size, int padding = 0);

	//Access getters/setters
	sf::Sprite& GetSprite()						{ return _sprite; };
	const bool& IsPlaying()						{ return _isPlaying; };
	const sf::Vector2u& GetFrameSize()			{ return _frameSize; };
	void SetFrameSize(const sf::Vector2u& size) { _frameSize = size; };

	//Call in update and render appropriately
	void Update(const float& dt);
	void Render(sf::RenderWindow& window);

	//Playback Control
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

	//Counter variables
	unsigned int _frameIt = 0;
	unsigned int _frameCount = 0;
	unsigned int _padding = 0;
	sf::Vector2u _frameSize;

	//Stores unique frame positions
	std::vector<sf::IntRect> _frames;

	bool _isPlaying = true;
	float _playbackTimer = 0.0f;


};
