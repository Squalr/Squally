#include "FrostBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Bows/FrostBow.h"

using namespace cocos2d;

const std::string FrostBow::SaveKeyFrostBow = "frost-bow";

FrostBow* FrostBow::create()
{
	FrostBow* instance = new FrostBow();

	instance->autorelease();

	return instance;
}

FrostBow::FrostBow() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

FrostBow::~FrostBow()
{
}

Item* FrostBow::clone()
{
	return FrostBow::create();
}

std::string FrostBow::getItemName()
{
	return FrostBow::SaveKeyFrostBow;
}

LocalizedString* FrostBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_FrostBow::create();
}

std::string FrostBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_FrostBow;
}

std::string FrostBow::getSerializationKey()
{
	return FrostBow::SaveKeyFrostBow;
}

Vec2 FrostBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
