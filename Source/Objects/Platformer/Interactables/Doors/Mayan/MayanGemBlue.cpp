#include "MayanGemBlue.h"

#include "Resources/ItemResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

MayanGemBlue* MayanGemBlue::create()
{
	MayanGemBlue* instance = new MayanGemBlue();

	instance->autorelease();

	return instance;
}

MayanGemBlue::MayanGemBlue() : super(ItemResources::Keys_BlueGem, ObjectResources::Doors_Mayan_BlueGemDisabled)
{
}

MayanGemBlue::~MayanGemBlue()
{
}

Color4B MayanGemBlue::getGemFontColor()
{
	return Color4B::BLUE;
}
