#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class DropPoolError : public MinMaxPool
{
public:
	static DropPoolError* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolError(cocos2d::ValueMap& properties);
	~DropPoolError();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;
};
