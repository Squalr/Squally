#include "PlayerInventory.h"

using namespace cocos2d;

const std::string PlayerInventory::SaveKeyPlayerInventory = "player_inventory";

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
