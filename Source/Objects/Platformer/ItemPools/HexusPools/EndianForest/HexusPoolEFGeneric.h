#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolEFGeneric : public MinMaxPool
{
public:
	static HexusPoolEFGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolEFGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolEFGeneric();

private:
	typedef MinMaxPool super;
};
