#include "MagesGuildPrisonKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesGuildPrisonKey::SaveKeyMagesGuildPrisonKey = "mages-guild-prison-key";

MagesGuildPrisonKey* MagesGuildPrisonKey::create()
{
	MagesGuildPrisonKey* instance = new MagesGuildPrisonKey();

	instance->autorelease();

	return instance;
}

MagesGuildPrisonKey::MagesGuildPrisonKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}))
{
}

MagesGuildPrisonKey::~MagesGuildPrisonKey()
{
}

Item* MagesGuildPrisonKey::clone()
{
	return MagesGuildPrisonKey::create();
}

std::string MagesGuildPrisonKey::getItemName()
{
	return MagesGuildPrisonKey::SaveKeyMagesGuildPrisonKey;
}

LocalizedString* MagesGuildPrisonKey::getString()
{
	return Strings::Items_Misc_Keys_MagesGuildPrisonKey::create();
}

std::string MagesGuildPrisonKey::getIconResource()
{
	return ItemResources::Keys_KEY_2;
}

std::string MagesGuildPrisonKey::getSerializationKey()
{
	return MagesGuildPrisonKey::SaveKeyMagesGuildPrisonKey;
}

