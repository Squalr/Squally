#include "WizardsHatWater.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatWater::SaveKeyWizardsHatWater = "wizards-hat-water";

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

std::string WizardsHatWater::getItemName()
{
	return WizardsHatWater::SaveKeyWizardsHatWater;
}

LocalizedString* WizardsHatWater::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string WizardsHatWater::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WizardsHatWater;
}

std::string WizardsHatWater::getSerializationKey()
{
	return WizardsHatWater::SaveKeyWizardsHatWater;
}

Vec2 WizardsHatWater::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
