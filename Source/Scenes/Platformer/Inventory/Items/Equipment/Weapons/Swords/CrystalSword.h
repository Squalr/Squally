#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class CrystalSword : public Item
{
public:
	CrystalSword* create();

protected:
	CrystalSword();
	virtual ~CrystalSword();

private:
	typedef Item super;
};
