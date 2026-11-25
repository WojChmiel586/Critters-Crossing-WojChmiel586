#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string filename, sf::Vector2u frame_size, int padding) : _sprite(_texture), _frameSize(frame_size), _padding(padding)
{
	_texture.loadFromFile(filename);
	_sprite.setTexture(_texture, true);
	_frames = std::move(CalculateFrames());

};
AnimatedSprite::AnimatedSprite(sf::Texture& texture, sf::Vector2u frame_size, int padding) : _texture(texture), _sprite(_texture), _frameSize(frame_size), _padding(padding)
{
	_frames = std::move(CalculateFrames());
}

void AnimatedSprite::Render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}
void AnimatedSprite::Play()
{
	_frameIt = 0;
	_playbackTimer = 0.0f;
	_isPlaying = true;
}

void AnimatedSprite::Stop()
{
	_frameIt = 0;
	_playbackTimer = 0.0f;
	_isPlaying = false;
}

void AnimatedSprite::Pause()
{
	_isPlaying = false;
}

void AnimatedSprite::Resume()
{
	_isPlaying = true;
}




void AnimatedSprite::Update(const float& dt)
{
	if (_isPlaying)
	{
		bool is_swap_ready = false;
		_playbackTimer += dt;
		if (_playbackTimer >= 1.0f / _playbackRate)
		{
			_playbackTimer = 0.0f;
			is_swap_ready = true;
			_frameIt++;

			if (_frameIt >= _frameCount)
			{
				_frameIt = 0;
			}

		}

		if (is_swap_ready)
		{
			MoveSpriteFrame();
			is_swap_ready = false;
		}
	}
}

void AnimatedSprite::MoveSpriteFrame()
{
	_sprite.setTextureRect(_frames[_frameIt]);
}
std::vector<sf::IntRect> AnimatedSprite::CalculateFrames()
{
	int row_count = _texture.getSize().y / _frameSize.y;
	int column_count = _texture.getSize().x / _frameSize.x;
	_frameCount = row_count <= 1 ? column_count : row_count * column_count;

	std::vector<sf::IntRect> vector;
	vector.reserve(column_count * 2);

	for (int i = 0; i < _frameCount; i++)
	{
		int xpos, ypos;
		xpos = _frameSize.x * (i % column_count);
		ypos = _frameSize.y * (i / row_count);
		sf::Vector2i rpos, rsize;
		rpos = { xpos + (int)_padding, ypos + (int)_padding };
		rsize = {(int)_frameSize.x,(int)_frameSize.y };
		sf::IntRect rect = sf::IntRect(rpos, rsize);

		vector.emplace_back(rect);
	}

	return vector;
}
;
