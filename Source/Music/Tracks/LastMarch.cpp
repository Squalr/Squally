#include "LastMarch.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LastMarch::TrackKey = "last-march";

LastMarch* LastMarch::create(cocos2d::ValueMap& properties)
{
	LastMarch* instance = new LastMarch(properties);

	instance->autorelease();

	return instance;
}

LastMarch::LastMarch(cocos2d::ValueMap& properties) : super(properties, MusicResources::LastMarch, Strings::Menus_TODO::create(), Strings::Menus_TODO::create())
{
}

LastMarch::~LastMarch()
{
}
