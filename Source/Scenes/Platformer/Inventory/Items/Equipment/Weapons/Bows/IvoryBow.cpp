#include "IvoryBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Bows/IvoryBow.h"

using namespace cocos2d;

const std::string IvoryBow::SaveKeyIvoryBow = "ivory-bow";

IvoryBow* IvoryBow::create()
{
	IvoryBow* instance = new IvoryBow();

	instance->autorelease();

	return instance;
}

IvoryBow::IvoryBow() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

IvoryBow::~IvoryBow()
{
}

Item* IvoryBow::clone()
{
	return IvoryBow::create();
}

std::string IvoryBow::getItemName()
{
	return IvoryBow::SaveKeyIvoryBow;
}

LocalizedString* IvoryBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_IvoryBow::create();
}

std::string IvoryBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_IvoryBow;
}

std::string IvoryBow::getSerializationKey()
{
	return IvoryBow::SaveKeyIvoryBow;
}

Vec2 IvoryBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
