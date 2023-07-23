#include "RacingAgainstTheSunset.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RacingAgainstTheSunset::TrackKey = "racing-against-the-sunset";

RacingAgainstTheSunset* RacingAgainstTheSunset::create(cocos2d::ValueMap& properties)
{
	RacingAgainstTheSunset* instance = new RacingAgainstTheSunset(properties);

	instance->autorelease();

	return instance;
}

RacingAgainstTheSunset::RacingAgainstTheSunset(cocos2d::ValueMap& properties) : super(properties, MusicResources::Racing_Against_the_Sunset, Strings::Menus_Music_PhilipWesley_RacingAgainstTheSunset::create(), Strings::Menus_Music_PhilipWesley_PhilipWesley::create())
{
}

RacingAgainstTheSunset::~RacingAgainstTheSunset()
{
}
