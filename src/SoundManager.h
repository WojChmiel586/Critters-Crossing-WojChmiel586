#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>


class SoundManager
{
public:
    SoundManager();
    ~SoundManager() = default;

    //SFX

    // Load a sound buffer from file and give it key.
    bool loadSound(const std::string& key, const std::string& filename);

    // Play a previously loaded sound effect once.
    void playSound(const std::string& key, bool isLoop, float volume = 100.f, float pitch = 1.f, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f));

    //BGM

    // Load music from file
    // Only one music track is active at a time.
    bool loadMusic(const std::string& filename);

    void playMusic(bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    void setMusicVolume(float volume);   // 0–100
    void setSoundVolume(float volume);   // 0–100

    float getMusicVolume() const;
    float getSoundVolume() const;

    bool isMusicPlaying() const;

private:
    //Map that matches string names to the appropriate sound buffers for ease of access
    std::unordered_map<std::string, sf::SoundBuffer> sound_buffers;

    // Pool of sf::Sound objects for concurrent one-shots.
    static const int SOUND_POOL_SIZE = 16;
    sf::SoundBuffer empty_buffer;
    std::vector<sf::Sound> sound_pool;
    //sf::Sound footsteps_sound;
    int pool_index = 0;

    sf::Music music;

    float global_sound_volume = 100.f;
    float global_music_volume  = 100.f;

   static std::unique_ptr<SoundManager> instance;
};
