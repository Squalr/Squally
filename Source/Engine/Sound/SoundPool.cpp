#include "SoundPool.h"

#include <SFML/Audio.hpp>

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Utils/LogUtils.h"
#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Sound/SoundBase.h"

using namespace cocos2d;

// Not necessarily simultaneously playing, but amount of data loaded at once
const int SoundPool::MaxConcurrentSounds = 64;
const int SoundPool::MaxConcurrentMusic = 3;
SoundPool* SoundPool::Instance = nullptr;

void SoundPool::RegisterGlobalNode()
{
	if (SoundPool::Instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->RegisterGlobalNode(SoundPool::getInstance());
	}
}

SoundPool* SoundPool::getInstance()
{
	if (SoundPool::Instance == nullptr)
	{
		SoundPool::Instance = new SoundPool();

		SoundPool::Instance->autorelease();
	}

	return SoundPool::Instance;
}


SoundPool::SoundPool()
{
	this->initializeChannel(SoundChannel::Sound, SoundPool::MaxConcurrentSounds);
	this->initializeChannel(SoundChannel::Music, SoundPool::MaxConcurrentMusic);
}

SoundPool::~SoundPool()
{
	this->destroyChannels();
}

int SoundPool::validateSoundId(SoundChannel soundChannel, int soundId, sf::Sound*& outSound)
{
	SoundChannelData* soundChannelData = this->getChannelData(soundChannel);

	if (soundChannelData->assignedSoundIds.find(outSound) != soundChannelData->assignedSoundIds.end()
		&& soundChannelData->assignedSoundIds[outSound] == soundId)
	{
		return soundId;
	}

	outSound = nullptr;
	return SoundBase::InvalidSoundId;
}

int SoundPool::allocSound(SoundChannel soundChannel, const std::string& soundResource, sf::Sound*& outSound)
{
	static int SoundId = 1;

	SoundChannelData* soundChannelData = this->getChannelData(soundChannel);
	
	for (int index = 0; index < soundChannelData->maxConcurrentSounds; index++)
	{
		// Map the index from [0 .. max) to [[previous + 1 .. max) [0 .. previous)]
		// This allows us to start iterating from our previously allocated sound index as a heuristic
		int searchIndex = MathUtils::wrappingNormalize(soundChannelData->cachedSearchIndex + index + 1, 0, soundChannelData->maxConcurrentSounds - 1);

		if (this->allocSoundInternal(soundChannel, soundResource, searchIndex))
		{
			soundChannelData->cachedSearchIndex = searchIndex;
			outSound = soundChannelData->sounds[searchIndex];
			soundChannelData->assignedSoundIds[outSound] = SoundId++;
			return soundChannelData->assignedSoundIds[outSound];
		}
	}

	outSound = nullptr;
	soundChannelData->assignedSoundIds[outSound] = SoundBase::InvalidSoundId;
	return SoundBase::InvalidSoundId;
}

bool SoundPool::allocSoundInternal(SoundChannel soundChannel, const std::string& soundResource, int index)
{
	SoundChannelData* soundChannelData = this->getChannelData(soundChannel);

	switch (soundChannelData->sounds[index]->getStatus())
	{
		case sf::SoundSource::Status::Stopped:
		{
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename(soundResource);

			if (!soundChannelData->buffers[index]->loadFromFile(fullPath))
			{
				LogUtils::logError("Failed to load sound: " + fullPath);
			}

			soundChannelData->sounds[index]->setBuffer(*soundChannelData->buffers[index]);
			return true;
		}
		default:
		case sf::SoundSource::Status::Paused:
		case sf::SoundSource::Status::Playing:
		{
			return false;
		}
	}
}

SoundChannelData* SoundPool::getChannelData(SoundChannel soundChannel)
{
	return soundChannelData[soundChannel];
}

void SoundPool::initializeChannel(SoundChannel soundChannel, int capacity)
{
	SoundChannelData* channelData = new SoundChannelData(capacity);

	for (int index = 0; index < channelData->maxConcurrentSounds; index++)
	{
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		sf::Sound* sound = new sf::Sound();

		sound->setBuffer(*buffer);
		
		channelData->buffers.push_back(buffer);
		channelData->sounds.push_back(sound);
	}

	soundChannelData.insert({ soundChannel, channelData });
}

void SoundPool::destroyChannels()
{
	for (const auto& next : this->soundChannelData)
	{
		SoundChannelData* channelData = next.second;

		for (int index = 0; index < int(channelData->buffers.size()); index++)
		{
			delete(channelData->buffers[index]);
		}
		
		for (int index = 0; index < int(channelData->sounds.size()); index++)
		{
			delete(channelData->sounds[index]);
		}

		delete(channelData);
	}
}
