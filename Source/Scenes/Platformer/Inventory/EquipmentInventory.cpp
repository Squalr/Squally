#include "EquipmentInventory.h"

using namespace cocos2d;

EquipmentInventory* EquipmentInventory::create()
{
	EquipmentInventory* instance = new EquipmentInventory();

	instance->autorelease();

	return instance;
}

EquipmentInventory::EquipmentInventory() : super()
{
}

EquipmentInventory::~EquipmentInventory()
{
}

void EquipmentInventory::onEnter()
{
	super::onEnter();
}

void EquipmentInventory::initializeListeners()
{
	super::initializeListeners();
}

int EquipmentInventory::getTotalMinAttack()
{
	// TODO: Iterate items, try cast weapon, sum min attack
	return 3;
}

int EquipmentInventory::getTotalMaxAttack()
{
	// TODO: Iterate items, try cast weapon, sum max attack
	return 6;
}

int EquipmentInventory::getTotalDefense()
{
	// TODO: Iterate items, try cast weapon, sum defense
	return 3;
}
