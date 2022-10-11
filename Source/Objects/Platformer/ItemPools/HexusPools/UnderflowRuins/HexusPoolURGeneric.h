#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolURGeneric : public MinMaxPool
{
public:
	static HexusPoolURGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolURGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolURGeneric();

private:
	typedef MinMaxPool super;
};
