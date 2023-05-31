#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolLCHexus : public CurrencyPool
{
public:
	static CurrencyPoolLCHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolLCHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolLCHexus();

private:
	typedef CurrencyPool super;
};
