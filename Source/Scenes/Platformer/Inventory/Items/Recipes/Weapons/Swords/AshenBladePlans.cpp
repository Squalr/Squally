#include "AshenBladePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AshenBladePlans::SaveKeyAshenBladePlans = "ashen-blade-plans";

AshenBladePlans* AshenBladePlans::create()
{
	AshenBladePlans* instance = new AshenBladePlans();

	instance->autorelease();

	return instance;
}

AshenBladePlans::AshenBladePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

AshenBladePlans::~AshenBladePlans()
{
}

Item* AshenBladePlans::craft()
{
	return AshenBlade::create();
}

std::map<Item*, int> AshenBladePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* AshenBladePlans::clone()
{
	return AshenBladePlans::create();
}

std::string AshenBladePlans::getItemName()
{
	return AshenBladePlans::SaveKeyAshenBladePlans;
}

LocalizedString* AshenBladePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_AshenBlade::create();
}

std::string AshenBladePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string AshenBladePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_AshenBlade;
}

std::string AshenBladePlans::getSerializationKey()
{
	return AshenBladePlans::SaveKeyAshenBladePlans;
}
