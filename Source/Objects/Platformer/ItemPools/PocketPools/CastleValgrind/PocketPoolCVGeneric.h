#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolCVGeneric : public MinMaxPool
{
public:
	static PocketPoolCVGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolCVGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolCVGeneric();

private:
	typedef MinMaxPool super;
};
