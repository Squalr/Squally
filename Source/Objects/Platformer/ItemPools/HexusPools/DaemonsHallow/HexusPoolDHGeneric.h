#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolDHGeneric : public MinMaxPool
{
public:
	static HexusPoolDHGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolDHGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolDHGeneric();

private:
	typedef MinMaxPool super;
};
