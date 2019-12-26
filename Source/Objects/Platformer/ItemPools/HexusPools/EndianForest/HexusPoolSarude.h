#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolSarude : public MinMaxPool
{
public:
	static HexusPoolSarude* create();

protected:
	HexusPoolSarude();
	~HexusPoolSarude();

private:
	typedef MinMaxPool super;
};
