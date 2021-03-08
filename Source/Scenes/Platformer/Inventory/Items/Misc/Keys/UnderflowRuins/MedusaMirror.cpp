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

MedusaMirror::MedusaMirror() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

MedusaMirror::~MedusaMirror()
{
}

Item* MedusaMirror::clone()
{
	return MedusaMirror::create();
}

const std::string& MedusaMirror::getItemName()
{
	return MedusaMirror::SaveKey;
}

LocalizedString* MedusaMirror::getString()
{
	return Strings::Items_Misc_Keys_MedusasMirror::create();
}

const std::string& MedusaMirror::getIconResource()
{
	return ItemResources::Keys_MedusaMirror;
}

const std::string& MedusaMirror::getSerializationKey()
{
	return MedusaMirror::SaveKey;
}

