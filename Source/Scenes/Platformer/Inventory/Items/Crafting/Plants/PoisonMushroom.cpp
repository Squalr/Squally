#include "PoisonMushroom.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PoisonMushroom::SaveKey = "poison-mushroom";

PoisonMushroom* PoisonMushroom::create()
{
	PoisonMushroom* instance = new PoisonMushroom();

	instance->autorelease();

	return instance;
}

PoisonMushroom::PoisonMushroom() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 24 }}), ItemMeta(20000))
{
}

PoisonMushroom::~PoisonMushroom()
{
}

Item* PoisonMushroom::clone()
{
	return PoisonMushroom::create();
}

const std::string& PoisonMushroom::getItemName()
{
	return PoisonMushroom::SaveKey;
}

LocalizedString* PoisonMushroom::getString()
{
	return Strings::Items_Crafting_Plants_PoisonMushroom::create();
}

const std::string& PoisonMushroom::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Plants_PoisonMushroom;
}

const std::string& PoisonMushroom::getIdentifier()
{
	return PoisonMushroom::SaveKey;
}
