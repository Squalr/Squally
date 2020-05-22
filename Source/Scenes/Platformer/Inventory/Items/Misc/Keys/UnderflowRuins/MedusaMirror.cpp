#include "MedusaMirror.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MedusaMirror::SaveKey = "medusa-mirror";

MedusaMirror* MedusaMirror::create()
{
	MedusaMirror* instance = new MedusaMirror();

	instance->autorelease();

	return instance;
}

MedusaMirror::MedusaMirror() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}))
{
}

MedusaMirror::~MedusaMirror()
{
}

Item* MedusaMirror::clone()
{
	return MedusaMirror::create();
}

std::string MedusaMirror::getItemName()
{
	return MedusaMirror::SaveKey;
}

LocalizedString* MedusaMirror::getString()
{
	return Strings::Items_Misc_Keys_MedusasMirror::create();
}

std::string MedusaMirror::getIconResource()
{
	return ItemResources::Keys_MedusaMirror;
}

std::string MedusaMirror::getSerializationKey()
{
	return MedusaMirror::SaveKey;
}

