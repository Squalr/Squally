#include "BoneAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneAxePlans::SaveKeyBoneAxePlans = "bone-axe-plans";

BoneAxePlans* BoneAxePlans::create()
{
	BoneAxePlans* instance = new BoneAxePlans();

	instance->autorelease();

	return instance;
}

BoneAxePlans::BoneAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BoneAxePlans::~BoneAxePlans()
{
}

Item* BoneAxePlans::craft()
{
	return BoneAxe::create();
}

std::vector<std::tuple<Item*, int>> BoneAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* BoneAxePlans::clone()
{
	return BoneAxePlans::create();
}

std::string BoneAxePlans::getItemName()
{
	return BoneAxePlans::SaveKeyBoneAxePlans;
}

LocalizedString* BoneAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BoneAxe::create();
}

std::string BoneAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BoneAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_BoneAxe;
}

std::string BoneAxePlans::getSerializationKey()
{
	return BoneAxePlans::SaveKeyBoneAxePlans;
}
