#include "WizardsHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHat::SaveKey = "wizards-hat";

WizardsHat* WizardsHat::create()
{
	WizardsHat* instance = new WizardsHat();

	instance->autorelease();

	return instance;
}

WizardsHat::WizardsHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WizardsHat::~WizardsHat()
{
}

Item* WizardsHat::clone()
{
	return WizardsHat::create();
}

const std::string& WizardsHat::getItemName()
{
	return WizardsHat::SaveKey;
}

LocalizedString* WizardsHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHat::create();
}

const std::string& WizardsHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHat;
}

const std::string& WizardsHat::getSerializationKey()
{
	return WizardsHat::SaveKey;
}

Vec2 WizardsHat::getDisplayOffset()
{
	return Vec2(-22.0f, -8.0f);
}
