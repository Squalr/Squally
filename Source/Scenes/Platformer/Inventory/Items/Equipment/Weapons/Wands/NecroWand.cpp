#include "NecroWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string NecroWand::SaveKeyNecroWand = "necro-wand";

NecroWand* NecroWand::create()
{
	NecroWand* instance = new NecroWand();

	instance->autorelease();

	return instance;
}

NecroWand::NecroWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

NecroWand::~NecroWand()
{
}

Item* NecroWand::clone()
{
	return NecroWand::create();
}

std::string NecroWand::getItemName()
{
	return NecroWand::SaveKeyNecroWand;
}

LocalizedString* NecroWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_NecroWand::create();
}

std::string NecroWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_NecroWand;
}

std::string NecroWand::getSerializationKey()
{
	return NecroWand::SaveKeyNecroWand;
}

Vec2 NecroWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
