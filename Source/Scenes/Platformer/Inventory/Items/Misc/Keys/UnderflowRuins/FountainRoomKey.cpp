#include "FountainRoomKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FountainRoomKey::SaveKey = "fountain-room-key";

FountainRoomKey* FountainRoomKey::create()
{
	FountainRoomKey* instance = new FountainRoomKey();

	instance->autorelease();

	return instance;
}

FountainRoomKey::FountainRoomKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}))
{
}

FountainRoomKey::~FountainRoomKey()
{
}

Item* FountainRoomKey::clone()
{
	return FountainRoomKey::create();
}

std::string FountainRoomKey::getItemName()
{
	return FountainRoomKey::SaveKey;
}

LocalizedString* FountainRoomKey::getString()
{
	return Strings::Items_Misc_Keys_FountainRoomKey::create();
}

std::string FountainRoomKey::getIconResource()
{
	return ItemResources::Keys_KEY_6;
}

std::string FountainRoomKey::getSerializationKey()
{
	return FountainRoomKey::SaveKey;
}

