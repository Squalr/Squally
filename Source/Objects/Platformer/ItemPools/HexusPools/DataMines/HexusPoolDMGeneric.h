#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolDMGeneric : public MinMaxPool
{
public:
	static HexusPoolDMGeneric* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolDMGeneric(cocos2d::ValueMap& properties);
	virtual ~HexusPoolDMGeneric();

private:
	typedef MinMaxPool super;
};
