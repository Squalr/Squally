#include "LetterForThePrincess.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LetterForThePrincess::SaveKey = "letter-for-the-princess";

LetterForThePrincess* LetterForThePrincess::create()
{
	LetterForThePrincess* instance = new LetterForThePrincess();

	instance->autorelease();

	return instance;
}

LetterForThePrincess::LetterForThePrincess() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

LetterForThePrincess::~LetterForThePrincess()
{
}

Item* LetterForThePrincess::clone()
{
	return LetterForThePrincess::create();
}

LocalizedString* LetterForThePrincess::getString()
{
	return Strings::Items_Misc_Keys_LetterForThePrincess::create();
}

const std::string& LetterForThePrincess::getIconResource()
{
	return ItemResources::Misc_ExpScrollA;
}

const std::string& LetterForThePrincess::getIdentifier()
{
	return LetterForThePrincess::SaveKey;
}

