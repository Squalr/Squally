#pragma once

#include "Engine/Inventory/Inventory.h"

class EquipmentInventory : public Inventory
{
public:
	EquipmentInventory();
	virtual ~EquipmentInventory();

protected:
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
};
