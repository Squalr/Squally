#include "CrystalSword.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string CrystalSword::SaveKeyCrystalSword = "crystal-sword";

CrystalSword* CrystalSword::create()
{
	CrystalSword* instance = new CrystalSword();

	instance->autorelease();

	return instance;
}

CrystalSword::CrystalSword() : super(nullptr, ObjectResources::Items_Equipment_Weapons_Swords_CrystalSword, 3, 6)
{
}

CrystalSword::~CrystalSword()
{
}

std::string CrystalSword::getSerializationKey()
{
	return CrystalSword::SaveKeyCrystalSword;
}
