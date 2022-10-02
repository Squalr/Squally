#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolLCGeneric : public MinMaxPool
{
public:
	static HexusPoolLCGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolLCGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolLCGeneric();

private:
	typedef MinMaxPool super;
};
