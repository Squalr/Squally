#pragma once

#include "Engine/GlobalNode.h"

namespace sf
{
	class Sound;
	class SoundBuffer;
}

class SoundPool : GlobalNode
{
public:
	static void RegisterGlobalNode();
	static SoundPool* getInstance();

	sf::Sound* allocSound(const std::string& soundResource);

protected:
	SoundPool();
	virtual ~SoundPool();

	static SoundPool* Instance;

private:
	bool allocSoundInternal(const std::string& soundResource, int index);

	std::vector<sf::SoundBuffer*> buffers;
	std::vector<sf::Sound*> sounds;
	std::map<sf::Sound*, int> soundIds;

	static const int MaxConcurrentSounds;
};
