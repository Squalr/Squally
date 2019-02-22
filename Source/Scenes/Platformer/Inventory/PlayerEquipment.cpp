#include "PlayerEquipment.h"

using namespace cocos2d;

const std::string PlayerEquipment::SaveKeyPlayerEquipment = "player_equipment";
PlayerEquipment* PlayerEquipment::instance = nullptr;

PlayerEquipment* PlayerEquipment::getInstance()
{
	if (PlayerEquipment::instance == nullptr)
	{
		PlayerEquipment::instance = new PlayerEquipment();
	}

	return instance;
}

PlayerEquipment::PlayerEquipment() : super(PlayerEquipment::SaveKeyPlayerEquipment)
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
