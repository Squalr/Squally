#include "WizardsHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHat::SaveKeyWizardsHat = "wizards-hat";

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

std::string WizardsHat::getItemName()
{
	return WizardsHat::SaveKeyWizardsHat;
}

LocalizedString* WizardsHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHat::create();
}

std::string WizardsHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHat;
}

std::string WizardsHat::getSerializationKey()
{
	return WizardsHat::SaveKeyWizardsHat;
}

Vec2 WizardsHat::getDisplayOffset()
{
	return Vec2(-22.0f, -8.0f);
}
