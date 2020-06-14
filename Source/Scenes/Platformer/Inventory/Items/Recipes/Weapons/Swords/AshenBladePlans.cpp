#include "AshenBladePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AshenBladePlans::SaveKey = "ashen-blade-plans";

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

std::vector<std::tuple<Item*, int>> AshenBladePlans::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 4 },
		{ Sulfur::create(), 2 },
		{ Diamond::create(), 2 },
	};
}

Item* AshenBladePlans::clone()
{
	return AshenBladePlans::create();
}

std::string AshenBladePlans::getItemName()
{
	return AshenBladePlans::SaveKey;
}

LocalizedString* AshenBladePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_AshenBlade::create();
}

std::string AshenBladePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string AshenBladePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_AshenBlade;
}

std::string AshenBladePlans::getSerializationKey()
{
	return AshenBladePlans::SaveKey;
}
