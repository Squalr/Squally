#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolCVHexus : public CurrencyPool
{
public:
	static CurrencyPoolCVHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolCVHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolCVHexus();

private:
	typedef CurrencyPool super;
};
