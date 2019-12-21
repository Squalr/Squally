#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolMarcel : public MinMaxPool
{
public:
	static HexusPoolMarcel* create();

protected:
	HexusPoolMarcel();
	~HexusPoolMarcel();

private:
	typedef MinMaxPool super;
};
