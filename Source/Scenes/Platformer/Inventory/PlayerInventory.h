#pragma once

#include "Engine/Inventory/Inventory.h"

class PlayerInventory : public Inventory
{
public:
	PlayerInventory();
	virtual ~PlayerInventory();

protected:
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
};
