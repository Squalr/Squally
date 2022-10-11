#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolDMGeneric : public MinMaxPool
{
public:
	static PocketPoolDMGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolDMGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolDMGeneric();

private:
	typedef MinMaxPool super;
};
