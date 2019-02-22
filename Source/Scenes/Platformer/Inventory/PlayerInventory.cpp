#include "PlayerInventory.h"

using namespace cocos2d;

const std::string PlayerInventory::SaveKeyPlayerInventory = "player_inventory";
PlayerInventory* PlayerInventory::instance = nullptr;

PlayerInventory* PlayerInventory::getInstance()
{
	if (PlayerInventory::instance == nullptr)
	{
		PlayerInventory::instance = new PlayerInventory();
	}

	return instance;
}

PlayerInventory::PlayerInventory() : super()
{
}

PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::onEnter()
{
	super::onEnter();
}

void PlayerInventory::initializeListeners()
{
	super::initializeListeners();
}
