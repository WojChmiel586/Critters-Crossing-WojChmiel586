#include "SoundManager.h"

SoundManager::SoundManager()
{
    //We use empty buffer to initialise the vector of sf::Sound
    //At runtime we will replace it with proper sound buffers
    sound_pool.reserve(SOUND_POOL_SIZE);
    for (int i = 0; i < SOUND_POOL_SIZE; ++i)
    {
        sound_pool.emplace_back(empty_buffer);
    }
}
//Loads oneshot into a dedicated sound buffer
bool SoundManager::loadSound(const std::string& key, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename))
    {
        std::cout << "SoundManager Failed to load sound: " << filename << "\n";
        return false;
    }
    sound_buffers[key] = std::move(buffer);
    return true;
}

void SoundManager::playSound(const std::string& key, bool isLoop, float volume, float pitch, sf::Vector2f position)
{
    //search through buffers map to find iterator pointing to the key value
    auto iterator = sound_buffers.find(key);
    //If sound missing iterator points to end of vector
    if (iterator == sound_buffers.end())
    {
        std::cout << "Sound key not found: " << key << "\n";
        return;
    }
    //otherwise iterator holds the sound_buffer map

    //Loop through the sound pool to find unused one
    int attempts = 0;
    while (sound_pool[pool_index].getStatus() == sf::Sound::Status::Playing
           && attempts < SOUND_POOL_SIZE)
    {
        //make sure that global pool always goes through all 16 elements using modulo division
        pool_index = (pool_index + 1) % SOUND_POOL_SIZE;
        ++attempts;
    }
    //if no free sound objects are available we use the oldest one
    sf::Sound& sound = sound_pool[pool_index];

    //set the sound object to the buffer inside the iterator
    sound.setBuffer(iterator->second);
    sound.setVolume(volume * (global_sound_volume / 100.f));
    sound.setPitch(pitch);
    sound.setLooping(isLoop);
    sound.setPosition({ position.x,0.0f,position.y });
    sound.play();

    pool_index = (pool_index + 1) % SOUND_POOL_SIZE;
}

//Assigns file to open for the larger music tracks
//Since audio files are streamed in sections we use openFromFile rather than loadFromFile
bool SoundManager::loadMusic(const std::string& filename)
{
    if (!music.openFromFile(filename))
    {
        std::cout << "Failed to load music: " << filename << "\n";
        return false;
    }
    music.setVolume(global_music_volume);
    return true;
}

void SoundManager::playMusic(bool loop)
{
    music.setLooping(loop);
    music.play();
}

void SoundManager::stopMusic()
{
    music.stop();
}

void SoundManager::pauseMusic()
{
    music.pause();
}

void SoundManager::resumeMusic()
{
    if (music.getStatus() == sf::Music::Status::Paused)
        music.play();
}

void SoundManager::setMusicVolume(float volume)
{
    global_music_volume = std::clamp(volume, 0.f, 100.f);
    music.setVolume(global_music_volume);
}

void SoundManager::setSoundVolume(float volume)
{
    global_sound_volume = std::clamp(volume, 0.f, 100.f);
}

float SoundManager::getMusicVolume() const  
{
    return global_music_volume; 
}
float SoundManager::getSoundVolume() const  
{
    return global_sound_volume;
}

bool SoundManager::isMusicPlaying() const
{
    return music.getStatus() == sf::Music::Status::Playing;
}
