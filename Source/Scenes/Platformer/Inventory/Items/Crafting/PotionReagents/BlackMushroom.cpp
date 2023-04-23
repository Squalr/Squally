#include "BlackMushroom.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BlackMushroom::SaveKey = "black-mushroom";

BlackMushroom* BlackMushroom::create()
{
	BlackMushroom* instance = new BlackMushroom();

	instance->autorelease();

	return instance;
}

BlackMushroom::BlackMushroom() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 6 }}), ItemMeta(20000))
{
}

BlackMushroom::~BlackMushroom()
{
}

Item* BlackMushroom::clone()
{
	return BlackMushroom::create();
}

LocalizedString* BlackMushroom::getString()
{
	return Strings::Items_Crafting_PotionReagents_BlackMushroom::create();
}

const std::string& BlackMushroom::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Potions_T5_BlackMushroom;
}

const std::string& BlackMushroom::getIdentifier()
{
	return BlackMushroom::SaveKey;
}
