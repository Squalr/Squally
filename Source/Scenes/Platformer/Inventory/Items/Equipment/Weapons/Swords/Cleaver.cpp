#include "Cleaver.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/Cleaver.h"

using namespace cocos2d;

const std::string Cleaver::SaveKeyCleaver = "cleaver";

Cleaver* Cleaver::create()
{
	Cleaver* instance = new Cleaver();

	instance->autorelease();

	return instance;
}

Cleaver::Cleaver() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

Cleaver::~Cleaver()
{
}

Item* Cleaver::clone()
{
	return Cleaver::create();
}

std::string Cleaver::getItemName()
{
	return Cleaver::SaveKeyCleaver;
}

LocalizedString* Cleaver::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Cleaver::create();
}

std::string Cleaver::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Cleaver;
}

std::string Cleaver::getSerializationKey()
{
	return Cleaver::SaveKeyCleaver;
}
