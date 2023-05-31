#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolEFHexus : public CurrencyPool
{
public:
	static CurrencyPoolEFHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolEFHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolEFHexus();

private:
	typedef CurrencyPool super;
};
