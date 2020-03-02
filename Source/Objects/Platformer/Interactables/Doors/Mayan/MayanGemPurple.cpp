#include "MayanGemPurple.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MayanGemPurple* MayanGemPurple::create()
{
	MayanGemPurple* instance = new MayanGemPurple();

	instance->autorelease();

	return instance;
}

MayanGemPurple::MayanGemPurple() : super(ObjectResources::Doors_Mayan_PurpleGem, ObjectResources::Doors_Mayan_PurpleGemDisabled)
{
}

MayanGemPurple::~MayanGemPurple()
{
}

Color4B MayanGemPurple::getGemFontColor()
{
	return Color4B::MAGENTA;
}
