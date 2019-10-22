#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolTownGuard : public MinMaxPool
{
public:
	static PocketPoolTownGuard* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolTownGuard(cocos2d::ValueMap& properties);
	~PocketPoolTownGuard();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
