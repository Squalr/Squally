#include "WizardsHatShadow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatShadow::SaveKey = "wizards-hat-shadow";

WizardsHatShadow* WizardsHatShadow::create()
{
	WizardsHatShadow* instance = new WizardsHatShadow();

	instance->autorelease();

	return instance;
}

WizardsHatShadow::WizardsHatShadow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WizardsHatShadow::~WizardsHatShadow()
{
}

Item* WizardsHatShadow::clone()
{
	return WizardsHatShadow::create();
}

const std::string& WizardsHatShadow::getItemName()
{
	return WizardsHatShadow::SaveKey;
}

LocalizedString* WizardsHatShadow::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatShadow::create();
}

const std::string& WizardsHatShadow::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHatShadow;
}

const std::string& WizardsHatShadow::getSerializationKey()
{
	return WizardsHatShadow::SaveKey;
}

Vec2 WizardsHatShadow::getDisplayOffset()
{
	return Vec2(-22.0f, -10.0f);
}
