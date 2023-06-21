#include "TheGift.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheGift::TrackKey = "the-gift";

TheGift* TheGift::create(cocos2d::ValueMap& properties)
{
	TheGift* instance = new TheGift(properties);

	instance->autorelease();

	return instance;
}

TheGift::TheGift(cocos2d::ValueMap& properties) : super(properties, MusicResources::The_Gift__Melody_, Strings::Menus_Music_GavinLuke_TheGift::create(), Strings::Menus_Music_GavinLuke_GavinLuke::create())
{
}

TheGift::~TheGift()
{
}
