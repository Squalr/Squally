#include "Lacrimosa.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Lacrimosa::TrackKey = "lacrimosa";

Lacrimosa* Lacrimosa::create(cocos2d::ValueMap& properties)
{
	Lacrimosa* instance = new Lacrimosa(properties);

	instance->autorelease();

	return instance;
}

Lacrimosa::Lacrimosa(cocos2d::ValueMap& properties) : super(properties, MusicResources::Lacrimosa, Strings::Menus_Music_Flutist_Lacrimosa::create(), Strings::Menus_Music_Flutist_Flutist::create())
{
}

Lacrimosa::~Lacrimosa()
{
}
