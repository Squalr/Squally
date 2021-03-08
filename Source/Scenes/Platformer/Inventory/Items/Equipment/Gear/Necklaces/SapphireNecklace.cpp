#include "SapphireNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireNecklace::SaveKey = "sapphire-necklace";

SapphireNecklace* SapphireNecklace::create()
{
	SapphireNecklace* instance = new SapphireNecklace();

	instance->autorelease();

	return instance;
}

SapphireNecklace::SapphireNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	2,
	// Mana
	2,
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

SapphireNecklace::~SapphireNecklace()
{
}

Item* SapphireNecklace::clone()
{
	return SapphireNecklace::create();
}

const std::string& SapphireNecklace::getItemName()
{
	return SapphireNecklace::SaveKey;
}

LocalizedString* SapphireNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_SapphireNecklace::create();
}

const std::string& SapphireNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_SapphireNecklace;
}

const std::string& SapphireNecklace::getIdentifier()
{
	return SapphireNecklace::SaveKey;
}
