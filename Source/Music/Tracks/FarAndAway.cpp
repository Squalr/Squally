#include "FarAndAway.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FarAndAway::TrackKey = "far-and-away";

FarAndAway* FarAndAway::create(cocos2d::ValueMap& properties)
{
	FarAndAway* instance = new FarAndAway(properties);

	instance->autorelease();

	return instance;
}

FarAndAway::FarAndAway(cocos2d::ValueMap& properties) : super(properties, MusicResources::Far_and_Away, Strings::Menus_Music_PhilipWesley_FarAndAway::create(), Strings::Menus_Music_PhilipWesley_PhilipWesley::create())
{
}

FarAndAway::~FarAndAway()
{
}
