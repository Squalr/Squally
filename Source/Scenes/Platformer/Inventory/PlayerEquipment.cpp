#include "PlayerEquipment.h"

#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

PlayerEquipment* PlayerEquipment::instance = nullptr;

PlayerEquipment* PlayerEquipment::getInstance()
{
	if (PlayerEquipment::instance == nullptr)
	{
		PlayerEquipment::instance = new PlayerEquipment();
	}

	return instance;
}

PlayerEquipment::PlayerEquipment() : super(SaveKeys::SaveKeySquallyEquipment)
{
}

PlayerEquipment::~PlayerEquipment()
{
}

void PlayerEquipment::onEnter()
{
	super::onEnter();
}

void PlayerEquipment::initializeListeners()
{
	super::initializeListeners();
}
