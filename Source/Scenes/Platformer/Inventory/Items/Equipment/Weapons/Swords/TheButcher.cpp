#include "TheButcher.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheButcher::SaveKey = "the-butcher";

TheButcher* TheButcher::create()
{
	TheButcher* instance = new TheButcher();

	instance->autorelease();

	return instance;
}

TheButcher::TheButcher() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
))
{
}

TheButcher::~TheButcher()
{
}

Item* TheButcher::clone()
{
	return TheButcher::create();
}

std::string TheButcher::getItemName()
{
	return TheButcher::SaveKey;
}

LocalizedString* TheButcher::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_TheButcher::create();
}

std::string TheButcher::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_TheButcher;
}

std::string TheButcher::getSerializationKey()
{
	return TheButcher::SaveKey;
}
