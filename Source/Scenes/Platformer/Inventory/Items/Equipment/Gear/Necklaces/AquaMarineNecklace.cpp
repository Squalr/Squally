#include "AquaMarineNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AquaMarineNecklace::SaveKey = "aquamarine-necklace";

AquaMarineNecklace* AquaMarineNecklace::create()
{
	AquaMarineNecklace* instance = new AquaMarineNecklace();

	instance->autorelease();

	return instance;
}

AquaMarineNecklace::AquaMarineNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 63 }}), ItemStats(
	// Health
	3,
	// Mana
	3,
	// Attack
	1,
	// Magic Attack
	1,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

AquaMarineNecklace::~AquaMarineNecklace()
{
}

Item* AquaMarineNecklace::clone()
{
	return AquaMarineNecklace::create();
}

LocalizedString* AquaMarineNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_AquaMarineNecklace::create();
}

const std::string& AquaMarineNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_AquaMarineNecklace;
}

const std::string& AquaMarineNecklace::getIdentifier()
{
	return AquaMarineNecklace::SaveKey;
}
