#include "JoustingHelmet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string JoustingHelmet::SaveKey = "jousting-helmet";

JoustingHelmet* JoustingHelmet::create()
{
	JoustingHelmet* instance = new JoustingHelmet();

	instance->autorelease();

	return instance;
}

JoustingHelmet::JoustingHelmet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

JoustingHelmet::~JoustingHelmet()
{
}

Item* JoustingHelmet::clone()
{
	return JoustingHelmet::create();
}

LocalizedString* JoustingHelmet::getString()
{
	return Strings::Items_Equipment_Gear_Hats_JoustingHelmet::create();
}

const std::string& JoustingHelmet::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_JoustingHelmet;
}

const std::string& JoustingHelmet::getIdentifier()
{
	return JoustingHelmet::SaveKey;
}

Vec2 JoustingHelmet::getDisplayOffset()
{
	return Vec2(-40.0f, 34.0f);
}
