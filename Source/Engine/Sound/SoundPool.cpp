#include "SoundPool.h"

#include <SFML/Audio.hpp>

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Sound/SoundBase.h"

using namespace cocos2d;

const int SoundPool::MaxConcurrentSounds = 64;
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
	this->buffers = std::vector<sf::SoundBuffer*>();
	this->sounds = std::vector<sf::Sound*>();

	for (int index = 0; index < MaxConcurrentSounds; index++)
	{
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		sf::Sound* sound = new sf::Sound();

		sound->setBuffer(*buffer);
		
		this->buffers.push_back(buffer);
		this->sounds.push_back(sound);
	}
}

SoundPool::~SoundPool()
{
	for (int index = 0; index < MaxConcurrentSounds; index++)
	{
		delete(this->buffers[index]);
		delete(this->sounds[index]);
	}
}

int SoundPool::validateSoundId(int soundId, sf::Sound*& outSound)
{
	if (assignedSoundIds.find(outSound) != assignedSoundIds.end() && assignedSoundIds[outSound] == soundId)
	{
		return soundId;
	}

	outSound = nullptr;
	return -1;
}

int SoundPool::allocSound(const std::string& soundResource, sf::Sound*& outSound)
{
	static int SoundId = 1;
	static int CachedSearchIndex = 0;
	
	for (int index = 0; index < MaxConcurrentSounds; index++)
	{
		// Map the index from [0 .. max) to [[previous + 1 .. max) [0 .. previous)]
		// This allows us to start iterating from our previously allocated sound index as a heuristic
		int searchIndex = MathUtils::wrappingNormalize(CachedSearchIndex + index + 1, 0, MaxConcurrentSounds - 1);

		if (this->allocSoundInternal(soundResource, searchIndex))
		{
			CachedSearchIndex = searchIndex;
			outSound = this->sounds[searchIndex];
			this->assignedSoundIds[outSound] = SoundId++;
			return this->assignedSoundIds[outSound];
		}
	}

	outSound = nullptr;
	this->assignedSoundIds[outSound] = SoundBase::InvalidSoundId;
	return SoundBase::InvalidSoundId;
}

bool SoundPool::allocSoundInternal(const std::string& soundResource, int index)
{
	switch (this->sounds[index]->getStatus())
	{
		case sf::SoundSource::Status::Stopped:
		{
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename(soundResource);
			this->buffers[index]->loadFromFile(fullPath);
			this->sounds[index]->setBuffer(*this->buffers[index]);
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
