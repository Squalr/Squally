#include "AmbientPiano.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AmbientPiano::TrackKey = "ambient-piano";

AmbientPiano* AmbientPiano::create(cocos2d::ValueMap& properties)
{
	AmbientPiano* instance = new AmbientPiano(properties);

	instance->autorelease();

	return instance;
}

AmbientPiano::AmbientPiano(cocos2d::ValueMap& properties) : super(properties, MusicResources::Ambient_Piano, Strings::Menus_Music_VaanFomm_AmbientPiano::create(), Strings::Menus_Music_VaanFomm_VaanFomm::create())
{
}

AmbientPiano::~AmbientPiano()
{
}
