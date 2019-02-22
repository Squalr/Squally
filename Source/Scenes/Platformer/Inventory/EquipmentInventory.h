#pragma once

#include "Engine/Inventory/Inventory.h"

// Generic inventory for any set of equipment with convenience methods
class EquipmentInventory : public Inventory
{
public:
	static EquipmentInventory* create();

	int getTotalMinAttack();
	int getTotalMaxAttack();
	int getTotalDefense();

protected:
	EquipmentInventory();
	virtual ~EquipmentInventory();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef Inventory super;
};
