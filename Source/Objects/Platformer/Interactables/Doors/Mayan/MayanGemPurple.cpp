#include "MayanGemPurple.h"

#include "Resources/ItemResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

MayanGemPurple* MayanGemPurple::create()
{
	MayanGemPurple* instance = new MayanGemPurple();

	instance->autorelease();

	return instance;
}

MayanGemPurple::MayanGemPurple() : super(ItemResources::Keys_PurpleGem, ObjectResources::Doors_Mayan_PurpleGemDisabled)
{
}

MayanGemPurple::~MayanGemPurple()
{
}

Color4B MayanGemPurple::getGemFontColor()
{
	return Color4B::MAGENTA;
}
