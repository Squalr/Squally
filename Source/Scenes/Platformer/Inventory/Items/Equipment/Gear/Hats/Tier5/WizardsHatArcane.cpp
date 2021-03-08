#include "WizardsHatArcane.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatArcane::SaveKey = "wizards-hat-arcane";

WizardsHatArcane* WizardsHatArcane::create()
{
	WizardsHatArcane* instance = new WizardsHatArcane();

	instance->autorelease();

	return instance;
}

WizardsHatArcane::WizardsHatArcane() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WizardsHatArcane::~WizardsHatArcane()
{
}

Item* WizardsHatArcane::clone()
{
	return WizardsHatArcane::create();
}

const std::string& WizardsHatArcane::getItemName()
{
	return WizardsHatArcane::SaveKey;
}

LocalizedString* WizardsHatArcane::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatArcane::create();
}

const std::string& WizardsHatArcane::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHatArcane;
}

const std::string& WizardsHatArcane::getSerializationKey()
{
	return WizardsHatArcane::SaveKey;
}

Vec2 WizardsHatArcane::getDisplayOffset()
{
	return Vec2(-22.0f, -8.0f);
}
