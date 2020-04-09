#include "MayanGemRed.h"

#include "Resources/ItemResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

MayanGemRed* MayanGemRed::create()
{
	MayanGemRed* instance = new MayanGemRed();

	instance->autorelease();

	return instance;
}

MayanGemRed::MayanGemRed() : super(ItemResources::Keys_RedGem, ObjectResources::Doors_Mayan_RedGemDisabled)
{
}

MayanGemRed::~MayanGemRed()
{
}

Color4B MayanGemRed::getGemFontColor()
{
	return Color4B::RED;
}
