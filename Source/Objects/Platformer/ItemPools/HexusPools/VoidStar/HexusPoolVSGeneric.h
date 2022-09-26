#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolVSGeneric : public MinMaxPool
{
public:
	static HexusPoolVSGeneric* create();

protected:
	HexusPoolVSGeneric();
	virtual ~HexusPoolVSGeneric();

private:
	typedef MinMaxPool super;
};
