#pragma once

#include "Engine/Inventory/CurrencyPool.h"

class CurrencyPoolDMHexus : public CurrencyPool
{
public:
	static CurrencyPoolDMHexus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	CurrencyPoolDMHexus(cocos2d::ValueMap& properties);
	virtual ~CurrencyPoolDMHexus();

private:
	typedef CurrencyPool super;
};
