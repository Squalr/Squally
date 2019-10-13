#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFGeneric : public MinMaxPool
{
public:
	static ChestPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFGeneric(cocos2d::ValueMap& properties);
	~ChestPoolEFGeneric();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
