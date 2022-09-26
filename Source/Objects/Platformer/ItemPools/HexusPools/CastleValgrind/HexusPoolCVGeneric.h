#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolCVGeneric : public MinMaxPool
{
public:
	static HexusPoolCVGeneric* create();

protected:
	HexusPoolCVGeneric();
	virtual ~HexusPoolCVGeneric();

private:
	typedef MinMaxPool super;
};
