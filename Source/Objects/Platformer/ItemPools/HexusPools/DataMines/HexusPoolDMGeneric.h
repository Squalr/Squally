#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolDMGeneric : public MinMaxPool
{
public:
	static HexusPoolDMGeneric* create();

protected:
	HexusPoolDMGeneric();
	virtual ~HexusPoolDMGeneric();

private:
	typedef MinMaxPool super;
};
