#include "HeartOfShadow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeartOfShadow::SaveKey = "heart-of-shadow";

HeartOfShadow* HeartOfShadow::create()
{
	HeartOfShadow* instance = new HeartOfShadow();

	instance->autorelease();

	return instance;
}

HeartOfShadow::HeartOfShadow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

HeartOfShadow::~HeartOfShadow()
{
}

Item* HeartOfShadow::clone()
{
	return HeartOfShadow::create();
}

LocalizedString* HeartOfShadow::getString()
{
	return Strings::Items_Crafting_Special_HeartOfShadow::create();
}

const std::string& HeartOfShadow::getIconResource()
{
	return ItemResources::Crafting_Smithing_HeartOfShadow;
}

const std::string& HeartOfShadow::getIdentifier()
{
	return HeartOfShadow::SaveKey;
}
