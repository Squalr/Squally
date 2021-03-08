#include "VikingHelmet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VikingHelmet::SaveKey = "viking-helmet";

VikingHelmet* VikingHelmet::create()
{
	VikingHelmet* instance = new VikingHelmet();

	instance->autorelease();

	return instance;
}

VikingHelmet::VikingHelmet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 17 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	3,
	// Speed
	0.05f
))
{
}

VikingHelmet::~VikingHelmet()
{
}

Item* VikingHelmet::clone()
{
	return VikingHelmet::create();
}

LocalizedString* VikingHelmet::getString()
{
	return Strings::Items_Equipment_Gear_Hats_VikingHelmet::create();
}

const std::string& VikingHelmet::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_VikingHelmet;
}

const std::string& VikingHelmet::getIdentifier()
{
	return VikingHelmet::SaveKey;
}

Vec2 VikingHelmet::getDisplayOffset()
{
	return Vec2(-2.0f, -16.0f);
}
