#include "FangBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FangBlade::SaveKeyFangBlade = "fang-blade";

FangBlade* FangBlade::create()
{
	FangBlade* instance = new FangBlade();

	instance->autorelease();

	return instance;
}

FangBlade::FangBlade() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

FangBlade::~FangBlade()
{
}

Item* FangBlade::clone()
{
	return FangBlade::create();
}

std::string FangBlade::getItemName()
{
	return FangBlade::SaveKeyFangBlade;
}

LocalizedString* FangBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_FangBlade::create();
}

std::string FangBlade::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_FangBlade;
}

std::string FangBlade::getSerializationKey()
{
	return FangBlade::SaveKeyFangBlade;
}
