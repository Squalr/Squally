#include "WizardsHatWater.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatWater::SaveKey = "wizards-hat-water";

WizardsHatWater* WizardsHatWater::create()
{
	WizardsHatWater* instance = new WizardsHatWater();

	instance->autorelease();

	return instance;
}

WizardsHatWater::WizardsHatWater() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WizardsHatWater::~WizardsHatWater()
{
}

Item* WizardsHatWater::clone()
{
	return WizardsHatWater::create();
}

const std::string& WizardsHatWater::getItemName()
{
	return WizardsHatWater::SaveKey;
}

LocalizedString* WizardsHatWater::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatWater::create();
}

const std::string& WizardsHatWater::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHatWater;
}

const std::string& WizardsHatWater::getIdentifier()
{
	return WizardsHatWater::SaveKey;
}

Vec2 WizardsHatWater::getDisplayOffset()
{
	return Vec2(-20.0f, -8.0f);
}
