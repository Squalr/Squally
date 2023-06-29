#include "RaceAgainstTheSunset.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RaceAgainstTheSunset::TrackKey = "race-against-the-sunset";

RaceAgainstTheSunset* RaceAgainstTheSunset::create(cocos2d::ValueMap& properties)
{
	RaceAgainstTheSunset* instance = new RaceAgainstTheSunset(properties);

	instance->autorelease();

	return instance;
}

RaceAgainstTheSunset::RaceAgainstTheSunset(cocos2d::ValueMap& properties) : super(properties, MusicResources::Racing_Against_the_Sunset, Strings::Menus_Music_PhilipWesley_RaceAgainstTheSunset::create(), Strings::Menus_Music_PhilipWesley_PhilipWesley::create())
{
}

RaceAgainstTheSunset::~RaceAgainstTheSunset()
{
}
