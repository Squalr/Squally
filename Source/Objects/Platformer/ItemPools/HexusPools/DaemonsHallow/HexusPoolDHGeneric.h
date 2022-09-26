#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolDHGeneric : public MinMaxPool
{
public:
	static HexusPoolDHGeneric* create();

protected:
	HexusPoolDHGeneric();
	virtual ~HexusPoolDHGeneric();

private:
	typedef MinMaxPool super;
};
