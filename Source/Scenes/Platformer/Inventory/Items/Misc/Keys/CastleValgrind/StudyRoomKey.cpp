#include "StudyRoomKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string StudyRoomKey::SaveKey = "study-room-key";

StudyRoomKey* StudyRoomKey::create()
{
	StudyRoomKey* instance = new StudyRoomKey();

	instance->autorelease();

	return instance;
}

StudyRoomKey::StudyRoomKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

StudyRoomKey::~StudyRoomKey()
{
}

Item* StudyRoomKey::clone()
{
	return StudyRoomKey::create();
}

LocalizedString* StudyRoomKey::getString()
{
	return Strings::Items_Misc_Keys_StudyRoomKey::create();
}

const std::string& StudyRoomKey::getIconResource()
{
	return ItemResources::Keys_StudyRoomKey;
}

const std::string& StudyRoomKey::getIdentifier()
{
	return StudyRoomKey::SaveKey;
}

