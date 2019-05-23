#pragma once

#include "Engine/Inventory/CurrencyInventory.h"

class PlayerCurrencyInventory : public CurrencyInventory
{
public:
	static PlayerCurrencyInventory* getInstance();

protected:
	PlayerCurrencyInventory();
	virtual ~PlayerCurrencyInventory();
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef CurrencyInventory super;

	static PlayerCurrencyInventory* instance;
};
