#include "PlayerInventory.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

PlayerInventory* PlayerInventory::instance = nullptr;

PlayerInventory* PlayerInventory::getInstance()
{
	if (PlayerInventory::instance == nullptr)
	{
		PlayerInventory::instance = new PlayerInventory();
	}

	return instance;
}

PlayerInventory::PlayerInventory() : super(SaveKeys::SaveKeySquallyInventory)
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
