#include "ChieftainsWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChieftainsWand::SaveKeyChieftainsWand = "chieftains-wand";

ChieftainsWand* ChieftainsWand::create()
{
	ChieftainsWand* instance = new ChieftainsWand();

	instance->autorelease();

	return instance;
}

ChieftainsWand::ChieftainsWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

ChieftainsWand::~ChieftainsWand()
{
}

Item* ChieftainsWand::clone()
{
	return ChieftainsWand::create();
}

std::string ChieftainsWand::getItemName()
{
	return ChieftainsWand::SaveKeyChieftainsWand;
}

LocalizedString* ChieftainsWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ChieftainsWand::create();
}

std::string ChieftainsWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_ChieftainsWand;
}

std::string ChieftainsWand::getSerializationKey()
{
	return ChieftainsWand::SaveKeyChieftainsWand;
}

Vec2 ChieftainsWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
