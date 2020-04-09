#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolEFGeneric : public MinMaxPool
{
public:
	static HexusPoolEFGeneric* create();

protected:
	HexusPoolEFGeneric();
	virtual ~HexusPoolEFGeneric();

private:
	typedef MinMaxPool super;
};
