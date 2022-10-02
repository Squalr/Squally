#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolVSGeneric : public MinMaxPool
{
public:
	static HexusPoolVSGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolVSGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolVSGeneric();

private:
	typedef MinMaxPool super;
};
