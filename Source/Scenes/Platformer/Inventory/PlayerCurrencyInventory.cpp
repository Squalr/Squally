#include "PlayerCurrencyInventory.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

PlayerCurrencyInventory* PlayerCurrencyInventory::instance = nullptr;

PlayerCurrencyInventory* PlayerCurrencyInventory::getInstance()
{
	if (PlayerCurrencyInventory::instance == nullptr)
	{
		PlayerCurrencyInventory::instance = new PlayerCurrencyInventory();
	}

	return instance;
}

PlayerCurrencyInventory::PlayerCurrencyInventory() : super(SaveKeys::SaveKeySquallyCurrencyInventory)
{
}

PlayerCurrencyInventory::~PlayerCurrencyInventory()
{
}

void PlayerCurrencyInventory::onEnter()
{
	super::onEnter();
}

void PlayerCurrencyInventory::initializeListeners()
{
	super::initializeListeners();
}
