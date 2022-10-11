#include "TrickOrTreat.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TrickOrTreat::TrackKey = "trick-or-treat";

TrickOrTreat* TrickOrTreat::create(cocos2d::ValueMap& properties)
{
	TrickOrTreat* instance = new TrickOrTreat(properties);

	instance->autorelease();

	return instance;
}

TrickOrTreat::TrickOrTreat(cocos2d::ValueMap& properties) : super(properties, MusicResources::TrickOrTreat, Strings::Menus_Music_Nosbertus_TrickOrTreat::create(), Strings::Menus_Music_Nosbertus_Nosbertus::create())
{
}

TrickOrTreat::~TrickOrTreat()
{
}
