#include "MithrilSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilSword::SaveKey = "mithril-sword";

MithrilSword* MithrilSword::create()
{
	MithrilSword* instance = new MithrilSword();

	instance->autorelease();

	return instance;
}

MithrilSword::MithrilSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 24, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

MithrilSword::~MithrilSword()
{
}

Item* MithrilSword::clone()
{
	return MithrilSword::create();
}

std::string MithrilSword::getItemName()
{
	return MithrilSword::SaveKey;
}

LocalizedString* MithrilSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MithrilSword::create();
}

std::string MithrilSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_MithrilSword;
}

std::string MithrilSword::getSerializationKey()
{
	return MithrilSword::SaveKey;
}
