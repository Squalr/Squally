#include "DemonHeart.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonHeart::SaveKey = "demon-heart";

DemonHeart* DemonHeart::create()
{
	DemonHeart* instance = new DemonHeart();

	instance->autorelease();

	return instance;
}

DemonHeart::DemonHeart() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

DemonHeart::~DemonHeart()
{
}

Item* DemonHeart::clone()
{
	return DemonHeart::create();
}

LocalizedString* DemonHeart::getString()
{
	return Strings::Items_Misc_Keys_DemonHeart::create();
}

const std::string& DemonHeart::getIconResource()
{
	return ItemResources::Keys_DemonHeart;
}

const std::string& DemonHeart::getIdentifier()
{
	return DemonHeart::SaveKey;
}

