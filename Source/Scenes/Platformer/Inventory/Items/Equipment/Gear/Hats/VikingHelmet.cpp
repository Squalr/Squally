#include "VikingHelmet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VikingHelmet::SaveKeyVikingHelmet = "viking-helmet";

VikingHelmet* VikingHelmet::create()
{
	VikingHelmet* instance = new VikingHelmet();

	instance->autorelease();

	return instance;
}

VikingHelmet::VikingHelmet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

VikingHelmet::~VikingHelmet()
{
}

Item* VikingHelmet::clone()
{
	return VikingHelmet::create();
}

std::string VikingHelmet::getItemName()
{
	return VikingHelmet::SaveKeyVikingHelmet;
}

LocalizedString* VikingHelmet::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string VikingHelmet::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_VikingHelmet;
}

std::string VikingHelmet::getSerializationKey()
{
	return VikingHelmet::SaveKeyVikingHelmet;
}

Vec2 VikingHelmet::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
