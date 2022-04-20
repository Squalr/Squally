#include "SoundPool.h"

#include <SFML/Audio.hpp>

#include "cocos/platform/CCFileUtils.h"

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalDirector.h"

using namespace cocos2d;

const int SoundPool::MaxConcurrentSounds = 16;
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

sf::Sound* SoundPool::allocSound(const std::string& soundResource)
{
	static int CachedSearchIndex = 0;
	int startIndex = CachedSearchIndex;

	// First search for a reusable slot with an already loaded buffer
	for (int index = startIndex; index < MaxConcurrentSounds; index++)
	{
		if (this->allocSoundInternal(soundResource, index))
		{
			CachedSearchIndex = index;
			return this->sounds[index];
		}
	}

	for (int index = 0; index < CachedSearchIndex; index++)
	{
		if (this->allocSoundInternal(soundResource, index))
		{
			CachedSearchIndex = index;
			return this->sounds[index];
		}
	}

	return nullptr;
}

bool SoundPool::allocSoundInternal(const std::string& soundResource, int index)
{
	switch (this->sounds[index]->getStatus())
	{
		case sf::SoundSource::Status::Stopped:
		{
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename(soundResource);

			if (this->buffers[index]->loadFromFile(fullPath))
			{
				SoundEvents::TriggerInvalidateSoundRef(SoundEvents::InvalidateSoundRefArgs(this->sounds[index]));
			}
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
