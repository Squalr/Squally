#include "MayanGemRed.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MayanGemRed* MayanGemRed::create()
{
	MayanGemRed* instance = new MayanGemRed();

	instance->autorelease();

	return instance;
}

MayanGemRed::MayanGemRed() : super(ObjectResources::Doors_Mayan_RedGem, ObjectResources::Doors_Mayan_RedGemDisabled)
{
}

MayanGemRed::~MayanGemRed()
{
}
