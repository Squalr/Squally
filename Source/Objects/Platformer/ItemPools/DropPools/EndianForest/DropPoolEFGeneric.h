#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class DropPoolEFGeneric : public MinMaxPool
{
public:
	static DropPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolEFGeneric(cocos2d::ValueMap& properties);
	~DropPoolEFGeneric();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
