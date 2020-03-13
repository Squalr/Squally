#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolTownGuard : public MinMaxPool
{
public:
	static PocketPoolTownGuard* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolTownGuard(cocos2d::ValueMap& properties);
	virtual ~PocketPoolTownGuard();

private:
	typedef MinMaxPool super;
};
