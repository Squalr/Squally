#include "PlayerCurrencyInventory.h"

using namespace cocos2d;

const std::string PlayerCurrencyInventory::SaveKeyPlayerCurrencyInventory = "player_currency_inventory";
PlayerCurrencyInventory* PlayerCurrencyInventory::instance = nullptr;

PlayerCurrencyInventory* PlayerCurrencyInventory::getInstance()
{
	if (PlayerCurrencyInventory::instance == nullptr)
	{
		PlayerCurrencyInventory::instance = new PlayerCurrencyInventory();
	}

	return instance;
}

PlayerCurrencyInventory::PlayerCurrencyInventory() : super(PlayerCurrencyInventory::SaveKeyPlayerCurrencyInventory)
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
