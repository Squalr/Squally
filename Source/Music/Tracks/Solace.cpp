#include "Solace.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Solace::TrackKey = "solace";

Solace* Solace::create(cocos2d::ValueMap& properties)
{
	Solace* instance = new Solace(properties);

	instance->autorelease();

	return instance;
}

Solace::Solace(cocos2d::ValueMap& properties) : super(properties, MusicResources::Solace, Strings::Menus_Music_GavinLuke_Solace::create(), Strings::Menus_Music_GavinLuke_GavinLuke::create())
{
}

Solace::~Solace()
{
}
