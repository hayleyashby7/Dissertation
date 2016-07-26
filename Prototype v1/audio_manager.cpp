#include <SFML\Audio.hpp>
#include <string>
#include <map>

#include "audio_manager.hpp"

void AudioManager::loadSoundBuffer(const std::string& name, const std::string& filename) {
	//Load SoundBuffer
	sf::SoundBuffer buf;
	buf.loadFromFile(filename);

	//Add to list of SoundBuffers
	this->soundbuffs[name] = buf;

	return;
}

sf::SoundBuffer& AudioManager::getRef(const std::string& soundbuffer) {
	return this->soundbuffs.at(soundbuffer);
}