#include "Medieval2.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Medieval2::TrackKey = "medieval-2";

Medieval2* Medieval2::create(cocos2d::ValueMap& properties)
{
	Medieval2* instance = new Medieval2(properties);

	instance->autorelease();

	return instance;
}

Medieval2::Medieval2(cocos2d::ValueMap& properties) : super(properties, MusicResources::Hexus2, Strings::Menus_Music_Blacksmith_Medieval2::create(), Strings::Menus_Music_Blacksmith_Blacksmith::create())
{
}

Medieval2::~Medieval2()
{
}
