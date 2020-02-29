#include "WizardsHatEarth.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatEarth::SaveKeyWizardsHatEarth = "wizards-hat-earth";

WizardsHatEarth* WizardsHatEarth::create()
{
	WizardsHatEarth* instance = new WizardsHatEarth();

	instance->autorelease();

	return instance;
}

WizardsHatEarth::WizardsHatEarth() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WizardsHatEarth::~WizardsHatEarth()
{
}

Item* WizardsHatEarth::clone()
{
	return WizardsHatEarth::create();
}

std::string WizardsHatEarth::getItemName()
{
	return WizardsHatEarth::SaveKeyWizardsHatEarth;
}

LocalizedString* WizardsHatEarth::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatEarth::create();
}

std::string WizardsHatEarth::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WizardsHatEarth;
}

std::string WizardsHatEarth::getSerializationKey()
{
	return WizardsHatEarth::SaveKeyWizardsHatEarth;
}

Vec2 WizardsHatEarth::getDisplayOffset()
{
	return Vec2(-18.0f, -8.0f);
}
