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

CrystalSword::CrystalSword() : super(3, 6)
{
}

CrystalSword::~CrystalSword()
{
}

Item* CrystalSword::clone()
{
	return CrystalSword::create();
}

LocalizedString* CrystalSword::getString()
{
	return nullptr;
}

std::string CrystalSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_CrystalSword;
}

std::string CrystalSword::getSerializationKey()
{
	return CrystalSword::SaveKeyCrystalSword;
}
