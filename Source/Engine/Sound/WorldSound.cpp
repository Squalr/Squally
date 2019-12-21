#include "WorldSound.h"

WorldSound* WorldSound::create(std::string soundResource)
{
	WorldSound* instance = new WorldSound(soundResource);

	instance->autorelease();

	return instance;
}

WorldSound::WorldSound(std::string soundResource) : super(soundResource)
{
	this->toggleCameraDistanceFade(true);
}

WorldSound::~WorldSound()
{
}
