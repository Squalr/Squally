#include "MithrilMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilMace::SaveKey = "mithril-mace";

MithrilMace* MithrilMace::create()
{
	MithrilMace* instance = new MithrilMace();

	instance->autorelease();

	return instance;
}

MithrilMace::MithrilMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 8, 14, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

MithrilMace::~MithrilMace()
{
}

Item* MithrilMace::clone()
{
	return MithrilMace::create();
}

std::string MithrilMace::getItemName()
{
	return MithrilMace::SaveKey;
}

LocalizedString* MithrilMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_MithrilMace::create();
}

std::string MithrilMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_MithrilMace;
}

std::string MithrilMace::getSerializationKey()
{
	return MithrilMace::SaveKey;
}

Vec2 MithrilMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
