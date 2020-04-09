#include "Forgotten.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Forgotten::TrackKey = "forgotten";

Forgotten* Forgotten::create()
{
	Forgotten* instance = new Forgotten();

	instance->autorelease();

	return instance;
}

Forgotten::Forgotten() : super(MusicResources::Forgotten, Strings::Menus_Music_JakobLindhagen_Forgotten::create(), Strings::Menus_Music_JakobLindhagen_JakobLindhagen::create())
{
}

Forgotten::~Forgotten()
{
}
