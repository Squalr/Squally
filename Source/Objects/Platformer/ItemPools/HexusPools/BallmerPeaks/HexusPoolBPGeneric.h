#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolBPGeneric : public MinMaxPool
{
public:
	static HexusPoolBPGeneric* create();

protected:
	HexusPoolBPGeneric();
	virtual ~HexusPoolBPGeneric();

private:
	typedef MinMaxPool super;
};
