#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolBPGeneric : public MinMaxPool
{
public:
	static HexusPoolBPGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolBPGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolBPGeneric();

private:
	typedef MinMaxPool super;
};
