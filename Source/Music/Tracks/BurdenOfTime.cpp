#include "BurdenOfTime.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BurdenOfTime::TrackKey = "burden-of-time";

BurdenOfTime* BurdenOfTime::create(cocos2d::ValueMap& properties)
{
	BurdenOfTime* instance = new BurdenOfTime(properties);

	instance->autorelease();

	return instance;
}

BurdenOfTime::BurdenOfTime(cocos2d::ValueMap& properties) : super(properties, MusicResources::BurdenOfTime, Strings::Menus_Music_AndreaBaroni_BurdenOfTime::create(), Strings::Menus_Music_AndreaBaroni_AndreaBaroni::create())
{
}

BurdenOfTime::~BurdenOfTime()
{
}
