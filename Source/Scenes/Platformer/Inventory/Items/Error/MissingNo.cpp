#include "MissingNo.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/ThrowRestorePotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MissingNo::SaveKeyMissingNo = "missing-no";

MissingNo* MissingNo::create()
{
	MissingNo* instance = new MissingNo();

	instance->autorelease();

	return instance;
}

MissingNo::MissingNo() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}))
{
}

MissingNo::~MissingNo()
{
}

Item* MissingNo::clone()
{
	return MissingNo::create();
}

std::string MissingNo::getItemName()
{
	return MissingNo::SaveKeyMissingNo;
}

LocalizedString* MissingNo::getString()
{
	return Strings::Items_Error_MissingNo::create();
}

std::string MissingNo::getIconResource()
{
	return ObjectResources::Items_Error_MissingNo;
}

std::string MissingNo::getSerializationKey()
{
	return MissingNo::SaveKeyMissingNo;
}

PlatformerAttack* MissingNo::createAssociatedAttack()
{
	return nullptr;
}
