#pragma once

#include "Engine/Inventory/Item.h"

class Currency : public Item
{
public:

protected:
	Currency();
	virtual ~Currency();

private:
	typedef Item super;
};
