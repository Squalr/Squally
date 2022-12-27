#include "Artrium.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Artrium::TrackKey = "artrium";

Artrium* Artrium::create(cocos2d::ValueMap& properties)
{
	Artrium* instance = new Artrium(properties);

	instance->autorelease();

	return instance;
}

Artrium::Artrium(cocos2d::ValueMap& properties) : super(properties, MusicResources::Artrium, Strings::TODO::create(), Strings::TODO::create())
{
}

Artrium::~Artrium()
{
}
