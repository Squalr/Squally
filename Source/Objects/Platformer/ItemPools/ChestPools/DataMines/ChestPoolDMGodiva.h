#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDMGodiva : public MinMaxPool
{
public:
	static ChestPoolDMGodiva* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDMGodiva(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDMGodiva();

private:
	typedef MinMaxPool super;
};
