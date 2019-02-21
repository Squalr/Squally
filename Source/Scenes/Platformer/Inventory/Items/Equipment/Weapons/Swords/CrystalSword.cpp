#include "CrystalSword.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

CrystalSword* CrystalSword::create()
{
	CrystalSword* instance = new CrystalSword();

	instance->autorelease();

	return instance;
}

CrystalSword::CrystalSword() : Item(nullptr, ObjectResources::Items_Weapons_Swords_CrystalSword)
{
}

CrystalSword::~CrystalSword()
{
}
