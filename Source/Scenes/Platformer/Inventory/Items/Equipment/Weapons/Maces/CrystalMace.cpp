#include "CrystalMace.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/CrystalMace.h"

using namespace cocos2d;

const std::string CrystalMace::SaveKeyCrystalMace = "crystal-mace";

CrystalMace* CrystalMace::create()
{
	CrystalMace* instance = new CrystalMace();

	instance->autorelease();

	return instance;
}

CrystalMace::CrystalMace() : super(3, 6)
{
}

CrystalMace::~CrystalMace()
{
}

Item* CrystalMace::clone()
{
	return CrystalMace::create();
}

LocalizedString* CrystalMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_CrystalMace::create();
}

std::string CrystalMace::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_CrystalMace;
}

std::string CrystalMace::getSerializationKey()
{
	return CrystalMace::SaveKeyCrystalMace;
}

Vec2 CrystalMace::getDisplayOffset()
{
	return Vec2(-24.0f, 0.0f);
}
