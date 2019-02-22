#pragma once

#include "Engine/Inventory/Inventory.h"

class Gear;
class Weapon;

// Generic inventory for any set of equipment with convenience methods
class EquipmentInventory : public Inventory
{
public:
	Weapon* getWeapon();
	std::vector<Gear*> getGear();

	int getTotalMinAttack();
	int getTotalMaxAttack();
	int getTotalDefense();

protected:
	EquipmentInventory(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);
	virtual ~EquipmentInventory();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef Inventory super;
};
