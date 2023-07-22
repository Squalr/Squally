#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolURMedusa : public MinMaxPool
{
public:
	static ChestPoolURMedusa* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolURMedusa(cocos2d::ValueMap& properties);
	virtual ~ChestPoolURMedusa();

private:
	typedef MinMaxPool super;
};
