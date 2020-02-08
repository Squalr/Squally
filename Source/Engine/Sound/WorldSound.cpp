#include "WorldSound.h"

#include "cocos/base/CCValue.h"

using namespace cocos2d;

const std::string WorldSound::MapKeyWorldSound = "world-sound";

WorldSound* WorldSound::create(std::string soundResource)
{
	ValueMap valueMap = ValueMap();

	return WorldSound::create(valueMap, soundResource);
}

WorldSound* WorldSound::create(ValueMap& properties, std::string soundResource)
{
	WorldSound* instance = new WorldSound(properties, soundResource);

	instance->autorelease();

	return instance;
}

WorldSound::WorldSound(ValueMap& properties, std::string soundResource) : super(properties, soundResource)
{
	this->toggleCameraDistanceFade(true);
}

WorldSound::~WorldSound()
{
}
