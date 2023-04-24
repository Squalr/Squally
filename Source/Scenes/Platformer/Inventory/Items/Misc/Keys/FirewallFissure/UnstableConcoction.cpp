#include "UnstableConcoction.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string UnstableConcoction::SaveKey = "unstable-concoction";

UnstableConcoction* UnstableConcoction::create()
{
	UnstableConcoction* instance = new UnstableConcoction();

	instance->autorelease();

	return instance;
}

UnstableConcoction::UnstableConcoction() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

UnstableConcoction::~UnstableConcoction()
{
}

Item* UnstableConcoction::clone()
{
	return UnstableConcoction::create();
}

LocalizedString* UnstableConcoction::getString()
{
	return Strings::Items_Misc_Keys_UnstableConcoction::create();
}

const std::string& UnstableConcoction::getIconResource()
{
	return ItemResources::Misc_UnstableConcoction;
}

const std::string& UnstableConcoction::getIdentifier()
{
	return UnstableConcoction::SaveKey;
}

