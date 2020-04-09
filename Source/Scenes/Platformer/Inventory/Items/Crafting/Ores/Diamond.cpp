#include "Diamond.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Diamond::SaveKey = "diamond";

Diamond* Diamond::create()
{
	Diamond* instance = new Diamond();

	instance->autorelease();

	return instance;
}

Diamond::Diamond() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 91 }}), ItemMeta(20000))
{
}

Diamond::~Diamond()
{
}

Item* Diamond::clone()
{
	return Diamond::create();
}

std::string Diamond::getItemName()
{
	return Diamond::SaveKey;
}

LocalizedString* Diamond::getString()
{
	return Strings::Items_Crafting_Ore_Diamond::create();
}

std::string Diamond::getIconResource()
{
	return ItemResources::Crafting_Smithing_Diamond;
}

std::string Diamond::getSerializationKey()
{
	return Diamond::SaveKey;
}
