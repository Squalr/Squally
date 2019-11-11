#include "MagesGuildPrisonKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Misc/Keys/MagesGuildPrisonKey.h"

using namespace cocos2d;

const std::string MagesGuildPrisonKey::SaveKeyMagesGuildPrisonKey = "mages-guild-prison-key";

MagesGuildPrisonKey* MagesGuildPrisonKey::create()
{
	MagesGuildPrisonKey* instance = new MagesGuildPrisonKey();

	instance->autorelease();

	return instance;
}

MagesGuildPrisonKey::MagesGuildPrisonKey() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
	return ObjectResources::Items_Misc_KEY_2;
}

std::string MagesGuildPrisonKey::getSerializationKey()
{
	return MagesGuildPrisonKey::SaveKeyMagesGuildPrisonKey;
}

