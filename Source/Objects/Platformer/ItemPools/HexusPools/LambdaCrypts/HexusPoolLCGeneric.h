#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolLCGeneric : public MinMaxPool
{
public:
	static HexusPoolLCGeneric* create();

protected:
	HexusPoolLCGeneric();
	virtual ~HexusPoolLCGeneric();

private:
	typedef MinMaxPool super;
};
