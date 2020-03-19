#include "VoidSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidSwordPlans::SaveKey = "void-sword-plans";

VoidSwordPlans* VoidSwordPlans::create()
{
	VoidSwordPlans* instance = new VoidSwordPlans();

	instance->autorelease();

	return instance;
}

VoidSwordPlans::VoidSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

VoidSwordPlans::~VoidSwordPlans()
{
}

Item* VoidSwordPlans::craft()
{
	return VoidSword::create();
}

std::vector<std::tuple<Item*, int>> VoidSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* VoidSwordPlans::clone()
{
	return VoidSwordPlans::create();
}

std::string VoidSwordPlans::getItemName()
{
	return VoidSwordPlans::SaveKey;
}

LocalizedString* VoidSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_VoidSword::create();
}

std::string VoidSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string VoidSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_VoidSword;
}

std::string VoidSwordPlans::getSerializationKey()
{
	return VoidSwordPlans::SaveKey;
}
