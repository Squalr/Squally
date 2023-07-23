#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolFFGeneric : public MinMaxPool
{
public:
	static HexusPoolFFGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolFFGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolFFGeneric();

private:
	typedef MinMaxPool super;
};
