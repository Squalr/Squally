#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class HexusPoolSarude : public MinMaxPool
{
public:
	static HexusPoolSarude* create(cocos2d::ValueMap& properties);

protected:
	HexusPoolSarude(cocos2d::ValueMap& properties);
	virtual ~HexusPoolSarude();

private:
	typedef MinMaxPool super;
};
