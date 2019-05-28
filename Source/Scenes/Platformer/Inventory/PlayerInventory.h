#pragma once

#include "Engine/Inventory/Inventory.h"

class PlayerInventory : public Inventory
{
public:
	static PlayerInventory* getInstance();

protected:
	PlayerInventory();
	virtual ~PlayerInventory();
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef Inventory super;

	static PlayerInventory* instance;
};
