#include "WeWillGetThereTogether.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WeWillGetThereTogether::TrackKey = "wwgtt";

WeWillGetThereTogether* WeWillGetThereTogether::create(cocos2d::ValueMap& properties)
{
	WeWillGetThereTogether* instance = new WeWillGetThereTogether(properties);

	instance->autorelease();

	return instance;
}

WeWillGetThereTogether::WeWillGetThereTogether(cocos2d::ValueMap& properties) : super(properties, MusicResources::WeWillGetThereTogether, Strings::Menus_Music_Lemmonias_WWGTT::create(), Strings::Menus_Music_Lemmonias_Lemmonias::create())
{
}

WeWillGetThereTogether::~WeWillGetThereTogether()
{
}
