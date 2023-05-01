#include "LittleFootsteps.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LittleFootsteps::TrackKey = "little-footsteps";

LittleFootsteps* LittleFootsteps::create(cocos2d::ValueMap& properties)
{
	LittleFootsteps* instance = new LittleFootsteps(properties);

	instance->autorelease();

	return instance;
}

LittleFootsteps::LittleFootsteps(cocos2d::ValueMap& properties) : super(properties, MusicResources::Little_Footsteps, Strings::Menus_Music_Alkis_LittleFootsteps::create(), Strings::Menus_Music_Alkis_Alkis::create())
{
}

LittleFootsteps::~LittleFootsteps()
{
}
