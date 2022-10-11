#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolCVGeneric : public MinMaxPool
{
public:
	static HexusPoolCVGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolCVGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolCVGeneric();

private:
	typedef MinMaxPool super;
};
