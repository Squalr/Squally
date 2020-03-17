#include "GuardsHelmet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GuardsHelmet::SaveKeyGuardsHelmet = "guards-helmet";

GuardsHelmet* GuardsHelmet::create()
{
	GuardsHelmet* instance = new GuardsHelmet();

	instance->autorelease();

	return instance;
}

GuardsHelmet::GuardsHelmet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

GuardsHelmet::~GuardsHelmet()
{
}

Item* GuardsHelmet::clone()
{
	return GuardsHelmet::create();
}

std::string GuardsHelmet::getItemName()
{
	return GuardsHelmet::SaveKeyGuardsHelmet;
}

LocalizedString* GuardsHelmet::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GuardsHelmet::create();
}

std::string GuardsHelmet::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GuardsHelmet;
}

std::string GuardsHelmet::getSerializationKey()
{
	return GuardsHelmet::SaveKeyGuardsHelmet;
}

Vec2 GuardsHelmet::getDisplayOffset()
{
	return Vec2(0.0f, 42.0f);
}
