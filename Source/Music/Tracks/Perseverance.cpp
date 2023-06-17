#include "Perseverance.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Perseverance::TrackKey = "perseverance";

Perseverance* Perseverance::create(cocos2d::ValueMap& properties)
{
	Perseverance* instance = new Perseverance(properties);

	instance->autorelease();

	return instance;
}

Perseverance::Perseverance(cocos2d::ValueMap& properties) : super(properties, MusicResources::TrickOrTreat, Strings::Menus_Music_MicheleMcLaughlin_Perseverance::create(), Strings::Menus_Music_MicheleMcLaughlin_MicheleMcLaughlin::create())
{
}

Perseverance::~Perseverance()
{
}
