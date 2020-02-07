#include "WeWillGetThereTogether.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WeWillGetThereTogether::TrackKey = "wwgtt";

WeWillGetThereTogether* WeWillGetThereTogether::create(SmartNode* owner)
{
	WeWillGetThereTogether* instance = new WeWillGetThereTogether(owner);

	instance->autorelease();

	return instance;
}

WeWillGetThereTogether::WeWillGetThereTogether(SmartNode* owner) : super(MusicResources::WeWillGetThereTogether, owner)
{
}

WeWillGetThereTogether::~WeWillGetThereTogether()
{
}
