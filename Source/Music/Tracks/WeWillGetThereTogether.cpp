#include "WeWillGetThereTogether.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WeWillGetThereTogether::TrackKey = "wwgtt";

WeWillGetThereTogether* WeWillGetThereTogether::create()
{
	WeWillGetThereTogether* instance = new WeWillGetThereTogether();

	instance->autorelease();

	return instance;
}

WeWillGetThereTogether::WeWillGetThereTogether() : super(MusicResources::WeWillGetThereTogether)
{
}

WeWillGetThereTogether::~WeWillGetThereTogether()
{
}
