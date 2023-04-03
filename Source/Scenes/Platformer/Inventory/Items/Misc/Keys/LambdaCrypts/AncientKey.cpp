#include "AncientKey.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AncientKey::SaveKey = "ancient-key";

AncientKey* AncientKey::create()
{
	AncientKey* instance = new AncientKey();

	instance->autorelease();

	return instance;
}

AncientKey::AncientKey() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

AncientKey::~AncientKey()
{
}

Item* AncientKey::clone()
{
	return AncientKey::create();
}

LocalizedString* AncientKey::getString()
{
	return Strings::Items_Misc_Keys_AncientKey::create();
}

const std::string& AncientKey::getIconResource()
{
	return ItemResources::Keys_AncientKey;
}

const std::string& AncientKey::getIdentifier()
{
	return AncientKey::SaveKey;
}

