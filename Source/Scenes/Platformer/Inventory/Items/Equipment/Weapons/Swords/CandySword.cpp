#include "CandySword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

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

CandySword::CandySword() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7)
{
}

CandySword::~CandySword()
{
}

Item* CandySword::clone()
{
	return CandySword::create();
}

std::string CandySword::getItemName()
{
	return CandySword::SaveKeyCandySword;
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
