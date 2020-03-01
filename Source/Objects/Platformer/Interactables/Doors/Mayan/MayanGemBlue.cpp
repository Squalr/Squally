#include "MayanGemBlue.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MayanGemBlue* MayanGemBlue::create()
{
	MayanGemBlue* instance = new MayanGemBlue();

	instance->autorelease();

	return instance;
}

MayanGemBlue::MayanGemBlue() : super(ObjectResources::Doors_Mayan_BlueGem, ObjectResources::Doors_Mayan_BlueGemDisabled)
{
}

MayanGemBlue::~MayanGemBlue()
{
}
