#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolBPHexus : public CurrencyPool
{
public:
	static CurrencyPoolBPHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolBPHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolBPHexus();

private:
	typedef CurrencyPool super;
};
