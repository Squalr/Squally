#include "SpikedClub.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/SpikedClub.h"

using namespace cocos2d;

const std::string SpikedClub::SaveKeySpikedClub = "spiked-club";

SpikedClub* SpikedClub::create()
{
	SpikedClub* instance = new SpikedClub();

	instance->autorelease();

	return instance;
}

SpikedClub::SpikedClub() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

SpikedClub::~SpikedClub()
{
}

Item* SpikedClub::clone()
{
	return SpikedClub::create();
}

std::string SpikedClub::getItemName()
{
	return SpikedClub::SaveKeySpikedClub;
}

LocalizedString* SpikedClub::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SpikedClub::create();
}

std::string SpikedClub::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_SpikedClub;
}

std::string SpikedClub::getSerializationKey()
{
	return SpikedClub::SaveKeySpikedClub;
}

Vec2 SpikedClub::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
