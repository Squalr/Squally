#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolURGeneric : public MinMaxPool
{
public:
	static HexusPoolURGeneric* create();

protected:
	HexusPoolURGeneric();
	virtual ~HexusPoolURGeneric();

private:
	typedef MinMaxPool super;
};
