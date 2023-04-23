#include "Meteorite.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Meteorite::SaveKey = "meteorite";

Meteorite* Meteorite::create()
{
	Meteorite* instance = new Meteorite();

	instance->autorelease();

	return instance;
}

Meteorite::Meteorite() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20000))
{
}

Meteorite::~Meteorite()
{
}

Item* Meteorite::clone()
{
	return Meteorite::create();
}

LocalizedString* Meteorite::getString()
{
	return Strings::Items_Crafting_BombReagents_Meteorite::create();
}

const std::string& Meteorite::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T7_Meteorite;
}

const std::string& Meteorite::getIdentifier()
{
	return Meteorite::SaveKey;
}
