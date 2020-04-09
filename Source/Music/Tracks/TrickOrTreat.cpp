#include "TrickOrTreat.h"

#include "Resources/MusicResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TrickOrTreat::TrackKey = "trick-or-treat";

TrickOrTreat* TrickOrTreat::create()
{
	TrickOrTreat* instance = new TrickOrTreat();

	instance->autorelease();

	return instance;
}

TrickOrTreat::TrickOrTreat() : super(MusicResources::TrickOrTreat, Strings::Menus_Music_Nosbertus_TrickOrTreat::create(), Strings::Menus_Music_Nosbertus_Nosbertus::create())
{
}

TrickOrTreat::~TrickOrTreat()
{
}
