#pragma once

#include "Engine/GlobalNode.h"

namespace sf
{
	class Sound;
	class SoundBuffer;
}

enum class SoundChannel
{
	Sound,
	Music,
};

struct SoundChannelData
{
	SoundChannelData(int maxConcurrentSounds) : maxConcurrentSounds(maxConcurrentSounds) { }

public:
	std::vector<sf::SoundBuffer*> buffers = std::vector<sf::SoundBuffer*>();
	std::vector<sf::Sound*> sounds = std::vector<sf::Sound*>();
	std::map<sf::Sound*, int> assignedSoundIds = std::map<sf::Sound*, int>();
	
	int maxConcurrentSounds = 0;
	int cachedSearchIndex = 0;
};

class SoundPool : GlobalNode
{
public:
	static void RegisterGlobalNode();
	static SoundPool* getInstance();

	int validateSoundId(SoundChannel soundChannel, int soundId, sf::Sound*& outSound);
	int allocSound(SoundChannel soundChannel, const std::string& soundResource, sf::Sound*& outSound);

protected:
	SoundPool();
	virtual ~SoundPool();

	static SoundPool* Instance;

private:
	bool allocSoundInternal(SoundChannel soundChannel, const std::string& soundResource, int index);
	SoundChannelData* getChannelData(SoundChannel soundChannel);
	void initializeChannel(SoundChannel soundChannel, int capacity);
	void destroyChannels();

	std::map<SoundChannel, SoundChannelData*> soundChannelData;

	static const int MaxConcurrentSounds;
	static const int MaxConcurrentMusic;
};
