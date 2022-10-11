#include "Medieval.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Medieval::TrackKey = "medieval";

Medieval* Medieval::create(cocos2d::ValueMap& properties)
{
	Medieval* instance = new Medieval(properties);

	instance->autorelease();

	return instance;
}

Medieval::Medieval(cocos2d::ValueMap& properties) : super(properties, MusicResources::Hexus1, Strings::Menus_Music_Blacksmith_Medieval::create(), Strings::Menus_Music_Blacksmith_Blacksmith::create())
{
}

Medieval::~Medieval()
{
}
