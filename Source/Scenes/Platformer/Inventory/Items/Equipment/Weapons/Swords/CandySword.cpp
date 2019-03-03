#include "CandySword.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/CandySword.h"

using namespace cocos2d;

const std::string CandySword::SaveKeyCandySword = "candy-sword";

CandySword* CandySword::create()
{
	CandySword* instance = new CandySword();

	instance->autorelease();

	return instance;
}

CandySword::CandySword() : super(4, 7)
{
}

CandySword::~CandySword()
{
}

Item* CandySword::clone()
{
	return CandySword::create();
}

LocalizedString* CandySword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CandySword::create();
}

std::string CandySword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_CandySword;
}

std::string CandySword::getSerializationKey()
{
	return CandySword::SaveKeyCandySword;
}
