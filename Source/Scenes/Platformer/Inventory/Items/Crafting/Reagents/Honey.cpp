#include "Honey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Honey::SaveKey = "honey";

Honey* Honey::create()
{
	Honey* instance = new Honey();

	instance->autorelease();

	return instance;
}

Honey::Honey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(20000))
{
}

Honey::~Honey()
{
}

Item* Honey::clone()
{
	return Honey::create();
}

const std::string& Honey::getItemName()
{
	return Honey::SaveKey;
}

LocalizedString* Honey::getString()
{
	return Strings::Items_Crafting_Reagents_Honey::create();
}

const std::string& Honey::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Reagents_Honey;
}

const std::string& Honey::getSerializationKey()
{
	return Honey::SaveKey;
}
